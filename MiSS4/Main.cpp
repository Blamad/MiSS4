#include <iostream>
#include <fstream>
#include "Gnuplot.h"

using namespace std;

string FILE_PATH = "plot.dat";

double fun(double x);
void calculateRK3(double x0, double e);
void drawResult();

double fun(double x)
{
	return x;
}

void calculateRK3(double x0, double epsilon)
{
	ofstream resultFile;
	resultFile.open(FILE_PATH);
	for (double i = -1; i <= 1; i+=0.1)
	{
		resultFile << i << " " << i << "\n";
	}
	resultFile.close();
}

void drawResult()
{
	Gnuplot gp;
	gp("set xrange [-1:1]");
	gp("set yrange [-1:1]");
	gp("set xlabel \"Oœ X\"");
	gp("set ylabel \"Oœ Y\"");
	gp("set title \"Wykres z pliku\"");

	gp("plot \"" + FILE_PATH + "\" index 0:0 using 1:2 with linespoints" );
	system("pause");
}

int main(int argc, char* argv[])
{
	double x0, epsilon;

	if (argc != 3)
	{
		cout << "Niewystarczaj¹ca ilosc parametrow! Domyslnie uzyte zostana x0=1 & e=1!" << "\n";
		x0 = 1;
		epsilon = 1;
	}
	else
	{
		x0 = atoi(argv[1]);
		epsilon = atoi(argv[2]);
	}

	calculateRK3(x0, epsilon);
	drawResult();
}