#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.1415926535897932;

double preciseCos(double angle, double precision);
double Cos(double angle, double precision);

int main()
{
	double result;
	double angle;
	double precision;
	cout << "Input precision: ";
	cin >> precision;
	cout << "Input angle: ";
	cin >> angle;
	cout << "Cos(" << angle << ") = " << Cos(angle, precision) << endl;
	cout << "Checking with cmath: cos = " << cos(angle) << endl;
}

double preciseCos(double angle, double precision)
{
	double previousSum = 0;
	double currentSum = 1;
	double term = -angle * angle / 2;
	const int firstValue = 4;
	for (int i(firstValue); abs(currentSum - previousSum) >= precision; i += 2)
    {
		previousSum = currentSum;
		currentSum += term;
		term *= -((angle * angle) / (i * (i - 1)));
	}
	return currentSum;
}

double Cos(double angle, double precision)
{
    double result;
    angle = fmod(angle, 2 * PI);
    int sign = 1;
    if (PI / 2 < angle && angle < 3 * PI / 2)
    {
        // converting angle to one with positive cos
        sign = -sign;
        angle = abs(PI - angle);
    }

    if ((PI / 4 < angle && angle < PI / 2) || (3 * PI / 2 < angle && angle <  3 * PI / 4))
    {
        // then cos(x) = sqrt(1 - cos^2(PI / 2 - x))
        double sin = preciseCos(abs(PI / 2 - angle), precision);
        result = sqrt(1 - sin * sin);
    }
    else
    {
        result = preciseCos(angle, precision);
    }
    result *= sign;
    return result;
}
