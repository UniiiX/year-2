#include <iostream>
#include <vector>
#include <cmath>

#define  uInt32 long long int

using namespace std;

class BArithm {
private:
	vector<int> first;
	vector<int> second;

	vector<int> add(vector<int>, vector<int>);
	vector<int> substract(vector<int>, vector<int>);

	void manageSize(vector<int>&, vector<int>&);
	void shrinkVec(vector<int>&, vector<int>&);
	int compareTwoBinary(vector<int> a, vector<int> b); // return 0: a>b; 1: a<b; 2:a=b;

public:
	BArithm();
	~BArithm();

	BArithm(vector<int> nFirst, vector<int> nSecond);

	void manageSize();

	void setVectors(vector<int> nFirst, vector<int> nSecond);
	void printVector(vector<int> vec);
	void printVector();
	void convertToDecimals();
	uInt32 convertToDecimals(vector<int> number);
	void convertToVector(uInt32 nFirst, uInt32 nSecond);
	vector<int> add(bool);
	vector<int> substract(bool);
	vector<int> multiply();
	vector<int> divide();
};

//--------------------------------------------------------------------------------------------------------------------

BArithm::BArithm(){

}

BArithm::BArithm(vector<int> nFirst, vector<int> nSecond){
	first = nFirst;
	second = nSecond;
	this->manageSize();
}

BArithm::~BArithm(){

}

void BArithm::manageSize(){
	shrinkVec(this->first,this->second);

	bool zero = false;
	int difference = first.size() - second.size();
	if (difference != 0) {
		if (difference > 0) {
			if (second[second.size() - 1] == 1){
				second[second.size() - 1] = 0;
				zero = true;
			}

			for (int i(0); i < difference; i++)
				second.push_back(0);
			if (zero)
				second[second.size() - 1] = 1;
		}
		else {
			if (first[first.size() - 1] == 1) {
				first[first.size() - 1] = 0;
				zero = true;
			}
			for (int i(0); i < difference; i++)
				first.push_back(0);
			if (zero)
				first[first.size() - 1] = 1;
		}
	}
}

void BArithm::manageSize(vector<int>& newFirst, vector<int>& newSecond){
	shrinkVec(newFirst, newSecond);

	bool zero = false;
	int difference = newFirst.size() - newSecond.size();
	if (difference != 0) {
		if (difference > 0) {
			if (newSecond[newSecond.size() - 1] == 1){
				newSecond[newSecond.size() - 1] = 0;
				zero = true;
			}

			for (int i(0); i < difference; i++)
				newSecond.push_back(0);
			if (zero)
				newSecond[newSecond.size() - 1] = 1;
		}
		else {
			if (newFirst[newFirst.size() - 1] == 1) {
				newFirst[newFirst.size() - 1] = 0;
				zero = true;
			}
			for (int i(0); i < difference; i++)
				newFirst.push_back(0);
			if (zero)
				newFirst[newFirst.size() - 1] = 1;
		}
	}
}

void BArithm::shrinkVec(vector<int>& a, vector<int>& b) {
	vector<int> newA = a;
	vector<int> newB = b;
	newA.pop_back();
	newB.pop_back();
	int i = newA.size() - 1;
	while (i>0 && newA[i] != 1){
		newA.pop_back();
		i--;
	}

	i = newB.size() - 1;
	while (i>0 && newB[i] != 1) {
		i--;
		newB.pop_back();
	}

	newA.push_back(a[a.size() - 1]);
	newB.push_back(b[b.size() - 1]);
	a = newA;
	b = newB;
}

void BArithm::setVectors(vector<int> nFirst, vector<int> nSecond) {
	first = nFirst;
	second = nSecond;
}

void BArithm::printVector(vector<int> vec) {
	for (int i(vec.size()-1); i >= 0; i--)
		cout << vec[i] << " ";
	cout << endl;
}

void BArithm::printVector(){
	for (int i(first.size() - 1); i >= 0; i--)
		cout << first[i] << " ";
	cout << endl;

	for (int i(second.size() - 1); i >= 0; i--)
		cout << second[i] << " ";
	cout << endl;
}

void BArithm::convertToDecimals() {
	uInt32 num = 0;
	for (int i(0); i < first.size() - 1; i++) {
		if (first[i] != 0)
			num += pow(2, i);
	}
	if (first[first.size()-1] == 1)
		cout << "first: " << -num << endl;
	else
		cout << "first: " << num << endl;

	num = 0;
	for (int i(0); i < second.size() - 1; i++) {
		if (second[i] != 0)
			num += pow(2, i);
	}
	if (second[second.size() - 1] == 1)
		cout << "second: " << -num << endl;
	else
		cout << "second: " << num << endl;
}

void BArithm::convertToVector(uInt32 nFirst, uInt32 nSecond){

	bool negative = false;
	if (nFirst < 0) {
		negative = true;
		nFirst = -nFirst;
	}
	while (nFirst > 0) {
		if (nFirst % 2 == 0) {
			first.push_back(0);
		}
		else
			first.push_back(1);
		nFirst /= 2;
	}

	if (!negative)
		first.push_back(0);
	else
		first.push_back(1);
	negative = false;

	if (nSecond < 0) {
		negative = true;
		nSecond = -nSecond;
	}

	while(nSecond > 0) {
		if (nSecond % 2 == 0)
			second.push_back(0);
		else
			second.push_back(1);
		nSecond /= 2;
	}


	if (!negative)
		second.push_back(0);
	else
		second.push_back(1);
}

uInt32 BArithm::convertToDecimals(vector<int> nfirst) {
	uInt32 num = 0;
	for (int i(0); i < nfirst.size() - 1; i++) {
		if (nfirst[i] != 0)
			num += pow(2, i);
	}
	if (nfirst[nfirst.size() - 1] == 1)
		return -num;
	else
		return num;
}

vector<int> BArithm::add(vector<int> a, vector<int> b) {
	vector<int> sum;
	vector<int> sum1;
	int var = 0;

	if (convertToDecimals(a) < convertToDecimals(b)) {
		sum = a;
		a = b;
		b = sum;
	}


	for (int i(0); i < a.size() - 1; i++) {
		if (a[i] != b[i]) {
			if (var == 1)
				sum.push_back(0);
			else
				sum.push_back(1);
		}
		else if (a[i] == 0) {
			if (var == 1) {
				sum.push_back(1);
				var = 0;
			}
			else
				sum.push_back(0);
		}
		else if (a[i] == 1) {
			if (var == 1)
				sum.push_back(1);
			else
				sum.push_back(0);

			var = 1;
		}
	}
	if (var == 1)
		sum.push_back(1);

	sum.push_back(0); // "+"
	return sum;
}

vector<int> BArithm::add(bool sub){
	vector<int> sum;
	vector<int> newFirst = first;
	vector<int> newSecond = second;
	if (convertToDecimals(first) < convertToDecimals(second)) {
		newFirst = second;
		newSecond = first;
	}
	int var = 0;
	if (!sub && (newFirst[newFirst.size()-1] != 0 || newSecond[newSecond.size()-1] != 0)) {
		sum = substract(true);
		return sum;
	}

	for (int i(0); i < newFirst.size() - 1; i++) {
			if (newFirst[i] != newSecond[i]) {
				if (var == 1)
					sum.push_back(0);
				else
					sum.push_back(1);
			}
			else if (newFirst[i] == 0) {
				if (var == 1) {
					sum.push_back(1);
					var = 0;
				}
				else
					sum.push_back(0);
			}
			else if (newFirst[i] == 1) {
				if (var == 1)
					sum.push_back(1);
				else
					sum.push_back(0);

				var = 1;
			}
		}
	if (var == 1) // if a result array is bigger tham the previous
		sum.push_back(1);

	if (!sub)
		sum.push_back(0); // "+"
	else
		sum.push_back(1); // "-"
	return sum;
}

int BArithm::compareTwoBinary(vector<int> a, vector<int> b) {
	if (a[a.size() - 1] == b[b.size() - 1]){
		if (a.size() - 1 > 0) {
			a.pop_back();
			b.pop_back();
			return compareTwoBinary(a, b);
		}
		else
			return 2;
	}
	else if (a[a.size() - 1] == 1 && b[b.size() - 1] == 0)
		return 0;
	else
		return 1;
}

vector<int> BArithm::substract(bool addition) {
	int var = 0;
	bool negative = false;
	bool borrowed = false;
	vector<int> newFirst = first;
	vector<int> newSecond = second;
	if (convertToDecimals(first) < convertToDecimals(second)) {
		newFirst = second;
		newSecond = first;
	}

	vector<int> sum;
	if (!addition && first[first.size() - 1] == 1 && second[second.size() - 1] == 0) { // -2 - 3
		return add(true);
	}
	else if (!addition && first[first.size() - 1] == 0 && second[second.size() - 1] == 1) { // 2 - (-2)
		newSecond[newSecond.size() - 1] = 0;
		return add(first,newSecond);
	}

	if (addition) {
		if (first[first.size() - 1] & second[second.size() - 1] == 1) // -2 + (-1)
			return add(true);
		else if (first[first.size() - 1] == 1) {
			newFirst = second;
			newSecond = first;
		}
	}
	else if (first[first.size() - 1] == 1) {
		newFirst = second;
		newSecond = first;
	}

	// CHECKING IF FIRST NUMBER IS BIGGER THAN SECOND
	vector<int> a = newFirst;
	vector<int> b = newSecond;
	a.pop_back();
	b.pop_back();
	newFirst.pop_back();
	newSecond.pop_back();
	if (compareTwoBinary(a, b) == 1) {  // b>a
		negative = true;
		newFirst = b;
		newSecond = a;
	}

	for (int i(0); i < newFirst.size(); i++) {
		if (newFirst[i] == 0 && newSecond[i] == 0) {
			if (borrowed) {
				sum.push_back(1);
			}
			else
				sum.push_back(0);
		}
		else if (newFirst[i] == 0 && newSecond[i] == 1){
			if (borrowed)
				sum.push_back(0);
			else
				sum.push_back(1);
			borrowed = true;
		}
		else if (newFirst[i] == 1 && newSecond[i] == 0) {
			if (borrowed) {
				borrowed = false;
				sum.push_back(0);
			}
			else
				sum.push_back(1);
		}
		else if (newFirst[i] == 1 && newSecond[i] == 1) {
			if (borrowed)
				sum.push_back(1);
			else
				sum.push_back(0);
		}

	}

	if (negative)
		sum.push_back(1);
	else
		sum.push_back(0);
	return sum;
}

vector<int> BArithm::substract(vector<int> newFirst, vector<int> newSecond){
	bool borrowed = false;
	vector<int> sum;

	for (int i(0); i < newFirst.size(); i++) {
		if (newFirst[i] == 0 && newSecond[i] == 0) {
			if (borrowed) {
				sum.push_back(1);
			}
			else
				sum.push_back(0);
		}
		else if (newFirst[i] == 0 && newSecond[i] == 1){
			if (borrowed)
				sum.push_back(0);
			else
				sum.push_back(1);
			borrowed = true;
		}
		else if (newFirst[i] == 1 && newSecond[i] == 0) {
			if (borrowed) {
				borrowed = false;
				sum.push_back(0);
			}
			else
				sum.push_back(1);
		}
		else if (newFirst[i] == 1 && newSecond[i] == 1) {
			if (borrowed)
				sum.push_back(1);
			else
				sum.push_back(0);
		}
	}

	return sum;
}

vector<int> BArithm::multiply() {
	vector<int> newFirst = first;
	vector<int> newSecond = second;
	bool negative = false;
	if (first[first.size() - 1] != second[second.size() - 1]){
		negative = true;
	}

	newFirst[newFirst.size() - 1] = 0;
	newSecond[newFirst.size() - 1] = 0;

	uInt32 N = convertToDecimals(newSecond);
	newSecond = newFirst;
	for (auto i(0); i < N-1; i++) {
		manageSize(newFirst, newSecond);
		newFirst = add(newFirst, newSecond);
	}

	if (negative)
		newFirst[newFirst.size() - 1] = 1;
	return newFirst;

}

vector<int> BArithm::divide() {
	vector<int> newFirst = first;
	vector<int> newSecond = second;
	vector<int> result;
	vector<int> increment;
	increment.push_back(1);
	increment.push_back(0);
	result.push_back(0);
	result.push_back(0);

	bool negative = false;
	if (first[first.size() - 1] != second[second.size() - 1]){
		negative = true;
	}

	manageSize(newFirst, newSecond);
	newFirst.pop_back();
	newSecond.pop_back();

	while (compareTwoBinary(newSecond,newFirst) > 0) {
		newFirst = substract(newFirst, newSecond);
		manageSize(result, increment);
		result = add(result, increment);
	}

	if (negative)
		result[result.size() - 1] = 1;

	increment[1] = 1;
	result = substract(result, increment);

	return result;
}

//--------------------------------------------------------------------------------------------------------------------

int main() {
	int f[] = { 0, 0, 0, 1, 0, 1, 0 }; // -15
	int s[] = { 1, 0 }; // 3

	vector<int> fv;
	vector<int> sv;

	for (int i(0); i < sizeof(f) / sizeof(int); i++)
		fv.push_back(f[i]);

	for (int i(0); i < sizeof(s) / sizeof(int); i++)
		sv.push_back(s[i]);

	//int f1 = 180;
	//int f2 = 300;

	//BArithm result;
	/*result.convertToVector(f1, f2);
	result.printVector();
	result.manageSize();*/

	int n;
	BArithm result(fv, sv);
	cout << "First: ";
	result.printVector(fv); cout << endl;
	n = result.convertToDecimals(fv);
	cout << n << endl;
	cout << "Second: ";
	result.printVector(sv); cout << endl;
	n = result.convertToDecimals(sv);
	cout << n << endl;

	fv = result.add(false);
	int num = result.convertToDecimals(fv);
	result.printVector(fv);
	cout << "Sum: " << num << endl;

	fv = result.substract(false);
	num = result.convertToDecimals(fv);
	result.printVector(fv);
	cout << "Sub: " << num << endl;

	fv = result.multiply();
	num = result.convertToDecimals(fv);
	result.printVector(fv);
	cout << "Multiply: " << num << endl;

	fv = result.divide();
	num = result.convertToDecimals(fv);
	result.printVector(fv);
	cout << "Divide: " << num << endl;
}
