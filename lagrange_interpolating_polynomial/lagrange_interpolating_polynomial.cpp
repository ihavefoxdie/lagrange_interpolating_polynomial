#include <omp.h>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

#define DEBUG = false

void print(double* array, double* array2, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << array[i] << " " << array2[i] << " \n";
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

int main(int argc, char** argv)
{
	int size = std::stoi(argv[1]);
	double x0 = std::stod(argv[2]);
	double step = std::stod(argv[3]);
	int number_of_N = std::stoi(argv[4]);
	//int size = 20;
	//double x0 = 0.1f;
	//double step = 0.1f;
	//int number_of_N = 100;
	double* pointsX = new double[size];
	double* pointsY = new double[size];
	double* new_pointsX = new double[number_of_N];
	double* new_pointsY = new double[number_of_N];
	double x = x0;
	

	for (int i = 0; i < size; i++)
	{
		pointsY[i] = function_of_x(x);
		pointsX[i] = x;
		x += step;
	}
	double stepInterpolation = (pointsX[size-1] - pointsX[0])/number_of_N;

	print(pointsX, pointsY, size);


#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < number_of_N; i++)
		{
			new_pointsX[i] = i*((pointsX[size - 1] - pointsX[0]) / number_of_N) + x0;
			new_pointsY[i] = lagrange(pointsX, pointsY, size, new_pointsX[i]);
		}
	}

	//print(new_pointsX, new_pointsY, number_of_N);

	// Create and open a text file
	std::ofstream MyFile("points.txt");

	// Write to the file
	for (size_t i = 0; i < number_of_N; i++)
	{
		MyFile << new_pointsX[i] << " " << new_pointsY[i] << "\n";
	}

	// Close the file
	MyFile.close();


	return 0;
}
