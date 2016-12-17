#include <iostream>
#include <fstream>
#include "Gnuplot.h"

using namespace std;

string FILE_PATH = "plot.dat";
int MIN_X = 0;
int MAX_X = 1;

double H = 0.1;
double DEFAULT_Y0 = 3;

double fun(double x);
void calculateRK3(double y0, double e);
void drawResult();

double fun(double x, double y)
{
	//Moze tu coœ zjeba³em..
	//https://www.wolframalpha.com/input/?i=y%3D3*exp(-2*x) - to wzór z tego tutka: http://lpsa.swarthmore.edu/NumInt/NumIntFourth.html
	//Ten wzór bankowo jest jakiœ z³y.
	return -2*y;
}

void calculateRK3(double y0, double epsilon)
{
	ofstream resultFile;
	resultFile.open(FILE_PATH);

	double y = y0;
	double x = MIN_X;

	resultFile << x << " " << y << "\n";

	for (x = MIN_X+H; x <= MAX_X; x+=H)
	{
		/*Zrodla:
		http://www.ikb.poznan.pl/almamater/wyklady/metody_komputerowe_03-04/03.pdf - wzor
		http://lpsa.swarthmore.edu/NumInt/NumIntFourth.html - sposob implementacji
		*/

		double K1 = H * fun(x, y);
		double K2 = H * fun((x + H/2), (y + K1/2));
		double K3 = H * fun((x + H), (y - K1 + 2*K2));
		y = y + (y + ((K1 + 4*K2 + K3) / 6));
		
		resultFile << x << " " << y << "\n";
	}
	
	resultFile.close();
}

void calculateeExample(double x0, double epsilon)
{
	ofstream resultFile;
	resultFile.open(FILE_PATH);

	for (int x = MIN_X; x <= MAX_X; x += H)
	{
		resultFile << x << " " << x << "\n";
	}

	resultFile.close();
}

void drawResult()
{
	Gnuplot gp;
	gp("set xrange ["+to_string(MIN_X)+":"+to_string(MAX_X)+"]");
	gp("set xlabel \"Oœ X\"");
	gp("set ylabel \"Oœ Y\"");
	gp("set title \"Wykres z pliku\"");
	gp("set key top left");
	gp("plot \"" + FILE_PATH + "\" index 0:0 using 1:2 title \"f(x)\" with linespoints" );
	system("pause");
}

int main(int argc, char* argv[])
{
	double y0, epsilon;

	if (argc != 3)
	{
		cout << "Niewystarczajaca ilosc parametrow! Uzywam domyslnych.\n";
		y0 = DEFAULT_Y0;
		epsilon = 1;
	}
	else
	{
		y0 = atoi(argv[1]);
		epsilon = atoi(argv[2]);
	}

	calculateRK3(y0, epsilon);
	drawResult();
}