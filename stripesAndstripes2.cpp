#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

//A点是左下角 length是长度 N是喷嘴直径一般0.4mm M是数量,真实的小条纹数是M*2 E1挤出机比例系数的微调，可能与Z有关
bool stripe(const double PointA[2], int length, double Z, double N, int M, double E1)
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;

	myGcodefile << "G0 F6000 " << " Z" << Z << endl;

	double tempPoint[2] = { PointA[0],PointA[1] };
	double tempX = tempPoint[0];
	for (int i = 0; i < M; i++)
	{

		myGcodefile << "G1 F8000 X" << tempX << " Y" << tempPoint[1] << endl;
		sumOfE += E1 * E*length;
		myGcodefile << "G1 F2000 X" << tempX << " Y" << tempPoint[1] + length << " E" << sumOfE << endl;
		tempX += N;
		myGcodefile << "G1 X" << tempX << " Y" << tempPoint[1] + length << " E" << sumOfE << endl;
		sumOfE += E1 * E*length;
		myGcodefile << "G1 X" << tempX << " Y" << tempPoint[1] << " E" << sumOfE << endl;
		tempX += N;
		myGcodefile << "G1 X" << tempX << " Y" << tempPoint[1] << " E" << sumOfE << endl;

	}
	//z偏移，防止磕碰
	//sumOfE -= E1 * E * raiseZ;
	//myGcodefile<< "G1 F8000 Z" << Z+ raiseZ <<" E" << sumOfE <<endl;

	return true;
}

bool stripe2(const double PointA[2], int length, double Z, double N, int M, double E1)
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;
	myGcodefile << "G0 F2000 " << " Z" << Z << endl;

	double tempPoint[2] = { PointA[0],PointA[1] };
	double tempY = tempPoint[1];
	for (int i = 0; i < M; i++)
	{
		myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempY << endl;
		sumOfE += E1 * E*length;
		myGcodefile << "G1 X" << tempPoint[0] + length << " Y" << tempY << " E" << sumOfE << endl;
		tempY += N;
		myGcodefile << "G1 X" << tempPoint[0] + length << " Y" << tempY << " E" << sumOfE << endl;
		sumOfE += E1 * E*length;
		myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempY << " E" << sumOfE << endl;
		tempY += N;
		myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempY << " E" << sumOfE << endl;
	}
	//z偏移，防止磕碰
	//sumOfE -= E1 * E * raiseZ;
	//myGcodefile << "G1 Z" << Z + raiseZ << " E" << sumOfE << endl;

	return true;
}

