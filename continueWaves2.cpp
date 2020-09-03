#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

bool continueWaves2(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1,double offset)
{
	ofstream myGcodefile(myFile, ios_base::app);

	if (!myGcodefile)
	{
		cout << "false continuewaves2";
	}

	double tempPoint[2] = { PointA[0],PointA[1] };

	for (int j = 0; j < M; j++)
	{
		for (int i = 0; i < numberOfwaves; i++)
		{
			myGcodefile << "G1 F8000 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i << " Y" << tempPoint[1] + 2 * N * j << " Z" << Z1 << " E" << sumOfE << endl;

			sumOfE += E1 * E * lengthOflow ;

			myGcodefile << "G1 F2000 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i + lengthOflow <<" E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z2 << endl;

			sumOfE += E1 * E * lengthOfhigh ;

			myGcodefile << "G1 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i + lengthOflow + lengthOfhigh << " E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z1 << endl;
		}

		tempPoint[0] += offset;

		for (int i = numberOfwaves-1; i >= 0; i--)
		{
			myGcodefile << "G1 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i + lengthOflow + lengthOfhigh <<" Y"<< tempPoint[1] + (2 * j + 1) * N << endl;

			myGcodefile << "G1 Z" << Z2 << endl;

			sumOfE += E1 * E * lengthOfhigh ;

			myGcodefile << "G1 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i + lengthOflow << " E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z1 << endl;

			sumOfE += E1 * E * lengthOflow ;

			myGcodefile << "G1 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i << " E" << sumOfE << endl;

		}

	}
	return true;
}