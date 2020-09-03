#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

//z «≤„∏ﬂ
void cube(const double PointA[2], double a, double b, double c, double z)
{
	ofstream myGcodefile(myFile, ios_base::app);

	if (!myGcodefile)
	{
		cout << "false cube";
	}

	int M = a / 0.8;
	int numberOfz = c / z;
	double flag = z;

	while (flag <= c)
	{
		stripe(PointA, b, flag, 0.4, M, 1);
		flag += z;
	}
}