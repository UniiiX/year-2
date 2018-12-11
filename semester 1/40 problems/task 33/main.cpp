#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int gcd(vector<int> &nums);
int gcd(int first, int second);
int extended_euclid(int a, int b, int &xg, int &yg);


class equation {
	vector<int> parameters;
	int freeParam;
	vector<int> ans;

	int calculate(vector<int> parameters, int freeParam);

public:
	equation(string filename);


	void solve();
	void printSolutions();
};

//----------------------------------------------------------------------------------------

int gcd(int first, int second) {
	while (second != 0) {
		int temp = second;
		second = first % second;
		first = temp;
	}
	return first;
}
int gcd(vector<int> &nums) {
	int len = nums.size();
	int res = nums.at(0);

	for (int i = 1; i < len && res != 1; i++) {
		res = gcd(res, nums.at(i));
	}

	return res;
}

// Calculates gcd(a,b) and numbers <xg> and <yg>
// so that a * xg + b * yg = gcd(a,b);
int extended_euclid(int a, int b, int &xg, int &yg) {
	// if a = 0, then set xg to 0, yg to 1 and return b
	if (b == 0) {
		xg = 1; yg = 0;
		return a;
	}
	// Otherwise pass b as 'a' and a%b as 'b'
	int xg_n, yg_n;

	int g = extended_euclid(b, a%b, xg_n, yg_n);

	xg = yg_n;
	yg = xg_n - (a / b) * yg_n;
	return g;
}


equation::equation(string filename) {
	ifstream in(filename);
	int len; in >> len;
	int param;
	for (int i = 0; i < len; i++) {
		in >> param; parameters.push_back(param);
	}

	in >> freeParam;
}

int equation::calculate(vector<int> parameters, int freeParam) {
	int divisor = gcd(parameters);
	if (freeParam % divisor) {
		cout << "No solution!" << endl;
		cout << "";
		return 0;
	}

	// If we have only two variables,
	// use extended Euclid algorithm
	if (parameters.size() == 2) {
		int a = parameters.at(0);
		int b = parameters.at(1);

		int curX, nextX;
		int gcdiv = extended_euclid(a, b, curX, nextX);

		curX *= (freeParam / gcdiv);
		nextX *= (freeParam / gcdiv);

		ans.push_back(curX);
		ans.push_back(nextX);
		return 0;
	}

	// Otherwise we use extended Euclid to find 't' from equation
	// (ai * xi + 1 * t = c) where t = a(i+1) * x(i+1) + ... + an * xn
	// and create equation (t = c1);
	int xi, t, ai = parameters.at(0);
	int div = extended_euclid(ai, 1, xi, t);

	xi *= (freeParam / div);
	t *= (freeParam / div);

	// Save xi
	ans.push_back(xi);

	// Create equation (t = c1)
	vector<int> nparam;
	for (int i = 1; i < parameters.size(); i++) {
		nparam.push_back(parameters.at(i));
	}

	// Solve this new equation
	return calculate(nparam, t);
}
void equation::printSolutions() {
	for (int i = 0; i < ans.size(); i++) cout << ans.at(i) << " ";
	cout << endl;
}

void equation::solve() {
	int res = calculate(parameters, freeParam);
	if (!res) printSolutions();
}

//----------------------------------------------------------------------------------------

int main()
{
	equation my("input.txt");
	my.solve();

	return 0;
}

