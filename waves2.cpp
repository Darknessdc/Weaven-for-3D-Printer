#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

bool waves2(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1)
{
	ofstream myGcodefile(myFile, ios_base::app);

	if (!myGcodefile)
	{
		cout << "false waves2";
	}

	double tempPoint[2] = { PointA[0],PointA[1] };

	for (double j = 0; j < M; j++)
	{

		for (int i = 0; i < numberOfwaves; i++)
		{
			//改变N 太挤了
			myGcodefile << "G1 F8000 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i << " Y" << tempPoint[1] + N * 1.1*j << " Z" << Z1 << endl;

			sumOfE += E1 * E * lengthOflow;

			myGcodefile << "G1 F1000 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i + lengthOflow << " E" << sumOfE << endl;

			//sumOfE += E1 * E *H1;

			myGcodefile << "G1 Z" << Z2 << endl;

			sumOfE += E1 * E * lengthOfhigh;

			myGcodefile << "G1 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i + lengthOflow + lengthOfhigh << " E" << sumOfE << endl;

			//sumOfE += E1 * E *H1;

			myGcodefile << "G1 Z" << Z1 << endl;
		}

		//回抽 7.23 只要防磕碰
		myGcodefile << "G1 F8000 Z" << Z2 + 0.3 << " E" << sumOfE << endl;
	}
	return true;
}