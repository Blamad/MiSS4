#include <iostream>
#include "GnuPlot.h"

#define DEBUG

using namespace std;

void calculateRK3(double x0, double e);
void testDrawGnuPlot();

int main(int argc, char* argv[])
{
	double x0, epsilon;

	if (argc != 3)
#ifdef DEBUG
	{
		x0 = 1;
		epsilon = 1;
	}
#elif
		return;
#endif
	else
	{
		x0 = atoi(argv[1]);
		epsilon = atoi(argv[2]);
	}

	calculateRK3(x0, epsilon);
}

void calculateRK3(double x0, double epsilon)
{
	testDrawGnuPlot();
}

void kozakPlot()
{
	Gnuplot gp;

	gp("set isosample 100\n");
	gp("min=-1\n");
	gp("max=1\n");
	gp("pi=3.141592\n");
	gp("set hidden3d\n");
	gp("set pm3d\n");
	gp("set contour\n");
	gp("splot [min:max] [min:max] x*x+2*y*y-0.3*cos(3*pi*x)-0.4*cos(4*pi*y)+0.7\n");
	gp("pause -1\n");


	std::cout << std::endl << "Press ENTER to continue..." << std::endl;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}

void biednyPlot()
{
	Gnuplot gp;
	gp("plot sin(x)");
	system("pause");
}

void testDrawGnuPlot()
{
	kozakPlot();
}