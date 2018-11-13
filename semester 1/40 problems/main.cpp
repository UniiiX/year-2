#include <iostream>

using namespace std;

class Spline
{
private:
	// struct of coficients to build spline in every node of the web
    struct Coefficients
    {
        double a;
        double b;
        double c;
        double d;
    };
    double *x;
    Coefficients* cubicPolynomial;
	int N; // number of nodes

public:
	~Spline()
	{
        delete[] cubicPolynomial;
    }
	// function to build spline
	// x - nodes of the web, must be sorted in ascend order
	// y - values of the function in the nodes
	// N - number of nodes
	void buildSpline(double *x, double *y, int N);

	// calculate values in every point of interpolated function
	double f(double x);
};

void Spline::buildSpline(double *x, double *y, int N)
{
	this->N = N;
    this->x = x;

	// initialization of the array of splines
    cubicPolynomial = new Coefficients[N + 1];

	// solving the SLE using coefficiens from c[i] for tridiagonal matrix
	// Tridiagonal matrix algorithm - forward going
	double *delta = new double[N - 1];
	double *lambda = new double[N - 1];
	double dx, dx2, dy, dy2;
	dx = x[1] - x[0];
	dx2 = x[2] - x[1];
	dy = y[1] - y[0];
	dy2 = y[2] - y[1];
	delta[0] = -dx2 / (2 * (dx + dx2));
	lambda[0] = 3 * (dy2 - dy) / (2 * (dx + dx2));
	for (int k = 1; k < N - 1; k++)
    {
        double denominator;
        dx = x[k] - x[k - 1];
        dx2 = x[k + 1] - x[k];
        dy = y[k] - y[k - 1];
        dy2 = y[k + 1] - y[k];
        denominator = 2*dx + 2*dx2 + dx*delta[k - 1];
        delta[k] = -dx2 / denominator;
        lambda[k] = (3*dy2 - 3*dy - dx*lambda[k - 1]) / denominator;
    }

    // finding coefficients c
	cubicPolynomial[0].c = 0;
	cubicPolynomial[N].c = 0;
    for (int k = N - 1; k > 0; k--)
    {
        cubicPolynomial[k].c = delta[k - 1] * cubicPolynomial[k + 1].c + lambda[k - 1];
    }

    // finding coefficients a, b, d
	for (int k = 1; k < N + 1; k++)
    {
        dx = x[k] - x[k - 1];
        dy = y[k] - y[k - 1];
        cubicPolynomial[k].a = y[k - 1];
        cubicPolynomial[k].b = dy + dx * (2*cubicPolynomial[k].c + cubicPolynomial[k - 1].c) / 3;
        cubicPolynomial[k].d = (cubicPolynomial[k].c + cubicPolynomial[k - 1].c) / (3*dx);
    }
}

double Spline::f(double x)
{
	Coefficients *neededPolynomial;
	int neededIndex;
	if (x <= this->x[0]) // if x is less than the first element of the array use the first
		neededPolynomial = cubicPolynomial + 1;
	else if (x >= this->x[N - 1]) // use last element if x is greater than last element
		neededPolynomial = cubicPolynomial + N - 1;
	else // in other cases points is laying between the border values
	{
	    int left = 0;
	    int right = N - 1;
		while (left + 1 < right)
		{
			int k = (right + left) / 2;
			if (x <= this->x[k])
				right = k;
			else
				left = k;
		}
		neededIndex = right;
		neededPolynomial = cubicPolynomial + right + 1;
	}

	double dx = (x - this->x[neededIndex]);
	return neededPolynomial->a + (neededPolynomial->b + (neededPolynomial->c + neededPolynomial->d * dx) * dx) * dx; // calculate value of spline in the specific point
}

int main()
{
	Spline cubicSpline;
	const int N = 6;
	double x[6] = { -0.5, 1.5, 2, 3.5, 6, 9 };
	double y[6] = { 2.5, 6, -3.5, -7, -10, 2 };
	double xi = 2.5;
	cubicSpline.buildSpline(x, y, N);
	cout << "f(2.5) = " << cubicSpline.f(xi) << endl;
}
