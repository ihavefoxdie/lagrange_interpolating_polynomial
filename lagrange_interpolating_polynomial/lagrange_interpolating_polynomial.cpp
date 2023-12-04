#include <omp.h>
#include <iostream>
#include <math.h>
#include <string>
#define DEBUG = false

void print(double* array, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << array[i] << " \n";
	}
}

double lagrange(double* pointsX, double* pointsY, int size, double x)
{
	double interpolatedY = 0.0f;

	for (int i = 0; i < size; i++)
	{
		double u = 1.0f;

		for (int j = 0; j < size; j++)
		{
			if (i != j) 
			{
				u *= (x - pointsX[j])/(pointsX[i] - pointsX[j]);
			}
		}
		interpolatedY += u * pointsY[i];
	}

	return interpolatedY;
}

double function_of_x(double x)
{
	return pow(x, -(1.0f / 2.0f));
}

int main()
{
	int number_of_N = 100;
	int size = 20;
	double* pointsX = new double[size];
	double* pointsY = new double[size];
	double step = 0.1;
	double x = step;

	for (int i = 0; i < size; i++)
	{
		pointsX[i] = function_of_x(x);
		pointsX[i] = x;
		x += step;
	}
	
	x = step;
	for (int i = 0; i < number_of_N; i++)
	{
		lagrange(pointsX, pointsX, size, x);
		x += step;
	}

#ifdef DEBUG == true
	print(pointsX, size);
#endif // DEBUG


	return 0;
}
