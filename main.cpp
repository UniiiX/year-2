///Вычислить методом Монте-Карло 2-кратный интеграл f(x,y) = x*x + y*y
///Область интегрирования: 0.5 <= x <= 1, 0 <= y <= 2x-1

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

double Func (double x, double y)
{
	return x * x + y * y;
}

double GenerateRandomDoubleInInterval(double up, double down)
{
    double result = down + (up - down) * (double(rand()) / RAND_MAX);
    return result;
}

double DoubleIntegral (double upX, double lowX, double upY, double lowY, int precision, double (*integralFunc)(double x, double y))
{
    double x;
	double y;
	double sum = 0;
    double result;
    for (int i = 0; i < precision; i++)
    {
        x = GenerateRandomDoubleInInterval(upX, lowX);
		y = GenerateRandomDoubleInInterval(upY, lowY);
		double upperBoundY = 2 * x - 1;

		if ((y > lowY) && (y < upperBoundY))
        {
			sum += integralFunc(x, y);
        }
    }
    result = sum * (upX - lowX) * (upY - lowY) / precision;
    return result;
}

int InputPrecison()
{
    int precision;
	cout << "Enter precision (greater number for greater precision): ";
	cin >> precision;
	return precision;
}

int main()
{
	double upX = 1;
	double upY = 2 * upX - 1;
	double lowX = 0.5;
	double lowY = 0;

	srand(time(NULL));
	int precision = InputPrecison();
	double integral = DoubleIntegral(upX , lowX, upY, lowY, precision, Func);

	cout << "Integral: " << integral;
}
