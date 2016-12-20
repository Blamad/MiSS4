#include <iostream>
#include <fstream>
#include "Gnuplot.h"

using namespace std;

string FILE_PATH = "plot.dat";
int MIN_X = 0;
int MAX_X = 1;

double DEFAULT_Y0 = 3;

double fun(double x, double y);
void calculateRK3(double y0, double e);
void drawResult();

int main(int argc, char* argv[])
{
	double y0, epsilon, h;

	if (argc != 3)
	{
		cout << "Niewystarczajaca ilosc parametrow! Uzywam domyslnych.\n";
		y0 = DEFAULT_Y0;
		epsilon = 0.0001;
	}
	else
	{
		y0 = atoi(argv[1]);
		epsilon = atoi(argv[2]);
	}

	//http://www.ikb.poznan.pl/almamater/wyklady/metody_komputerowe_03-04/03.pdf
	//błąd aproksymacji - Ο(h^4)
	h = pow(epsilon, 1 / 4.0);

	calculateRK3(y0, h);
	drawResult();
}

void calculateRK3(double y0, double h)
{
	ofstream resultFile;
	resultFile.open(FILE_PATH);

	double y = y0;
	double x = MIN_X;

	resultFile << x << " " << y << "\n";

	for (x = MIN_X + h; x <= MAX_X; x += h)
	{
		/*Zrodla:
		http://www.ikb.poznan.pl/almamater/wyklady/metody_komputerowe_03-04/03.pdf - wzor
		http://lpsa.swarthmore.edu/NumInt/NumIntFourth.html - sposob implementacji
		*/

		double K1 = h * fun(x, y);
		double K2 = h * fun((x + h / 2), (y + K1 / 2));
		double K3 = h * fun((x + h), (y - K1 + 2 * K2));
		y = y + ((K1 + 4 * K2 + K3) / 6);

		resultFile << x << " " << y << "\n";
	}

	resultFile.close();
}

double fun(double x, double y)
{
	return -2 * y;
}

void drawResult()
{
	Gnuplot gp;
	gp("set xrange [" + to_string(MIN_X) + ":" + to_string(MAX_X) + "]");
	gp("set xlabel \"Oś X\"");
	gp("set ylabel \"Oś Y\"");
	gp("set title \"Wykres z pliku\"");
	gp("set key top left");
	gp("plot \"" + FILE_PATH + "\" index 0:0 using 1:2 title \"f(x)\" with linespoints");
	system("pause");
}