#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

bool continueWaves(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1, double offset)
{
	ofstream myGcodefile(myFile, ios_base::app);

	if (!myGcodefile)
	{
		cout << "false continuewaves";
	}

	double tempPoint[2] = { PointA[0],PointA[1] };

	for (int j = 0; j < M; j++)
	{
		for (int i = 0; i < numberOfwaves; i++)
		{
			myGcodefile << "G1 F8000 X" << tempPoint[0] + 2 * N * j << " Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i << " Z" << Z1 << " E" << sumOfE << endl;

			sumOfE += E1 * E * lengthOflow;

			myGcodefile << "G1 F2000 Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i + lengthOflow << " E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z2 << endl;

			sumOfE += E1 * E * lengthOfhigh;

			myGcodefile << "G1 Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i + lengthOflow + lengthOfhigh << " E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z1 << endl;
		}

		tempPoint[1] += offset;

		for (int i = numberOfwaves - 1; i >= 0; i--)
		{
			myGcodefile << "G1 X" << tempPoint[0] + (2 * j + 1) * N <<" Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i + lengthOflow + lengthOfhigh << endl;

			myGcodefile << "G1 Z" << Z2 << endl;

			sumOfE += E1 * E * lengthOfhigh;

			myGcodefile << "G1 Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i + lengthOflow << " E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z1 << endl;

			sumOfE += E1 * E * lengthOflow;

			myGcodefile << "G1 Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i << " E" << sumOfE << endl;

		}

	}
	return true;
}