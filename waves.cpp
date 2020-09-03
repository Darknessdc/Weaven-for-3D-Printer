#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

bool waves(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1)
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;

	double tempPoint[2] = { PointA[0],PointA[1] };

	for (int j = 0; j < M; j++)
	{

		for (int i = 0; i < numberOfwaves; i++)
		{
			//j¼ÓÁË0.2 ²»È»Ì«½ôÁË 8.5
			myGcodefile << "G1 X" << tempPoint[0] + N * (j + 0.2) << " Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i << " Z" << Z1 << endl;
			sumOfE += E1 * E * lengthOflow;
			myGcodefile << "G1 F1000 X" << tempPoint[0] + N * (j + 0.2) << " Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i + lengthOflow << " E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z2 << endl;
			sumOfE += E1 * E * lengthOfhigh;
			myGcodefile << "G1 X" << tempPoint[0] + N * (j + 0.2) << " Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i + lengthOflow + lengthOfhigh << " E" << sumOfE << endl;
			myGcodefile << "G1 Z" << Z1 << endl;
		}

		//zÆ«ÒÆ£¬·ÀÖ¹¿ÄÅö
		myGcodefile << "G1 F8000 Z" << Z2 + 0.4 << endl;
	}
	return true;
}