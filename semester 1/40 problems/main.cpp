#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>


using namespace std;

class Calculator {
private:
	string expression;
	vector <string> postfix;

	string IntoString(char C);
	// Function to verify whether a character is operator symbol or not.
	bool IsOperator(char C);
	bool IsOperator(string C);
	// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not.
	bool IsOperand(char C);
	// Function to get weight of an operator. An operator with higher weight will have higher precedence.
	int GetOperatorWeight(char op);
	// Function to decide which operators have higher precedence
	int HasHigherPrecedence(char op1, char op2);
	void InfixToPostfix();

public:
	Calculator() {

	}
	Calculator(string expression) {
		this->expression = expression;
	}
	~Calculator() {

	}
	void performOperations();
};

//-----------------------------------------------------------------------------------------------------------------------

string Calculator::IntoString(char C) {
	string s;
	s.push_back(C);
	return s;
}

// Function to evaluate Postfix expression and return output
void Calculator::InfixToPostfix()
{

	// stack to store operators
	stack <string> S;

	// Check for unary + and -
	if (expression[0] == '+') expression.erase(0, 1);
	if (expression[0] == '-') expression[0] = '#';
	for (int i = 0; i < expression.length(); i++)
	{
		string tmp;

		// Scanning each character from left.
		// If character is a delimiter, move on.
		if (expression[i] == ' ' || expression[i] == ',') continue;


		else if (IsOperator(expression[i]))
		{
			while (!S.empty() && (S.top() != "(" && HasHigherPrecedence(S.top()[0], expression[i])))
			{
				postfix.push_back(S.top());
				S.pop();
			}
			S.push(IntoString(expression[i]));
		}
		else if (IsOperand(expression[i]))
		{
			while (IsOperand(expression[i]))
			{
				tmp.push_back(expression[i]);
				i++;
			}
			i--;
			postfix.push_back(tmp);
		}
		else if (expression[i] == '(')
		{
			S.push(IntoString(expression[i]));
		}

		else if (expression[i] == ')')
		{
			while (!S.empty() && S.top() != "(") {
				postfix.push_back(S.top());
				S.pop();
			}
			S.pop();
		}
	}

	while (!S.empty()) {
		postfix.push_back(S.top());
		S.pop();
	}
}

// Calculate result
void Calculator::performOperations() {
	InfixToPostfix();
	for (int i(0); i < postfix.size(); i++)
		cout << postfix[i] << " ";
	cout << endl;

	double rval, lval, result;
	result = 0;
	stack<double> S;
	int k = 0;
	for (int i = 0; i < postfix.size(); i++)
	{
		while (!IsOperator(postfix[i]))
		{
			S.push(stod(postfix[i]));
			i++;
		}
		rval = S.top();
		S.pop();

		if (!S.empty())
		{
			lval = S.top();
			S.pop();
		}

		if (postfix[i] == "+")
		{
			result = lval + rval;
			S.push(result);
		}
		else if (postfix[i] == "-")
		{
			result = lval - rval;
			S.push(result);
		}
		else if (postfix[i] == "/")
		{
			if (rval == 0) { cout << "\nDivision by 0"; cin.get(); exit(0); }
			result = lval / rval;
			S.push(result);
		}
		else if (postfix[i] == "*") {
			result = lval*rval;
			S.push(result);
		}
		else if (postfix[i] == "#")
		{
			result = 0 - rval;
			S.push(result);
		}
		else if (postfix[i] == "^") {
			result = pow(lval, rval);
			S.push(result);
		}
	}
	cout << "Result: " << S.top();
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int Calculator::GetOperatorWeight(char op)
{
	int weight = -1;
	switch (op)
	{
	case '+':
	case '-':
		weight = 1; break;
	case '*':
	case '/':
		weight = 2; break;
	case '^':
		weight = 3; break;
	case '#':
		weight = 4; break;
	}
	return weight;
}

// Function to perform an operation and return output.
int Calculator::HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	return op1Weight >= op2Weight ? true : false;
}


// Function to verify whether a character is a number
bool Calculator::IsOperand(char C)
{
	if (C >= '0' && C <= '9') return true;
	return false;
}

// Function to verify whether a character is operator symbol or not.
bool Calculator::IsOperator(char C)
{
	char op[] = { '+', '-', '*', '^', '/', '#' };
				for (int i = 0; i < 6; i++)
				{
					if (op[i] == C)
						return true;
				}
				return false;
}

bool Calculator::IsOperator(string C)
{
	string op[] = { "+", "-", "*", "^", "/", "#" };
	for (int i = 0; i < 6; i++)
	{
		if (op[i] == C)
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------

int main()
{
	string expression = "((3+2)*5)+2/5";
	/*cout << "Enter the values: ";
	getline(cin, expression);*/
	Calculator myCalculator(expression);

	myCalculator.performOperations();
}
