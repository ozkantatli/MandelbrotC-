// mandelbrot.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

using namespace std;


int findmandelbrot(double cr, double ci, int maxiteration) {
	int i = 0;
	double zr = 0.0, zi = 0.0;
	while (i < maxiteration && zr * zr + zi * zi < 4.0) {
		double temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}
	return i;
}

double mapToReal(int x, int imageWidt, double minR, double maxR)
{
	double range = maxR - minR;
	return x * (range / imageWidt) + minR;
}

double mapToImaginary(int y, int imageHeight, double minI, double maxI)
{
	double range = maxI - minI;
	return y * (range / imageHeight) + minI;
}

int main()
{
	ifstream fin("input.txt");
	int imageWidth, imageHeight, maxN;
	double minR, maxR, minI, maxI;
	if (!fin) {
		cout << "Dosya bulunamadi \n";
		cin.ignore();
		return 0;
	}
	
	fin >> imageWidth >> imageHeight >> maxN;
	fin >> minR >> maxR >> minI >> maxI;
	fin.close();

	ofstream fout("output_image1.ppm");
	fout << "P3" << endl;
	fout << imageWidth << " " << imageHeight << endl;
	fout << "256" << endl;


	for (int y = 0; y < imageHeight; y++)
	{
		for (int  x = 0; x < imageWidth; x++)
		{
			double cr = mapToReal(x, imageWidth, minR, maxR);
			double ci = mapToImaginary(y, imageHeight, minI, maxI);


			int n = findmandelbrot(cr, ci, maxN);

			int r = (int(n * sinf(n)) % 256);
			//int r = (n % 256);
			int g = (int(n * cosf(n)) % 256);
			//int b = (n+(n/2) % 256);
			int b = (int(n * tanf(n)) % 256);
			//fout << r << g << b ;
			fout << r << " " << g << " " << b << " ";
		}
		fout << endl;
	}
	fout.close();
	cout << "finish" << endl;

	return 0;
}

