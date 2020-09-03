#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

bool initPrinter()
{
	ofstream myGcodefile(myFile);
	if (!myGcodefile) return false;

	
	myGcodefile << "M104 S190" << endl;
	myGcodefile << "M140 S40" << endl;
	myGcodefile << "M190 S40" << endl;
	myGcodefile << "M109 S190" << endl;
	myGcodefile << "G28" << endl;

	return true;
}

bool endPrinter()
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;

	myGcodefile<<";End GCode" << endl
		<<"M104 S0; extruder heater off" << endl
		<<"M140 S0; heated bed heater off(if you have it)" << endl
		<<"G91; relative positioning" << endl
		<<"G1 E - 1 F300; retract the filament a bit before lifting the nozzle, to release some of the pressure" << endl
		<<"G1 Z + 0.5 E - 5 X - 20 Y - 20 F2700; move Z up a bit and retract filament even more"<< endl
		<<"G28 X0 Y0; move X / Y to min endstops, so the head is out of the way"<< endl
		<<"M84; steppers off" << endl
		<<"G90"<< endl;
}

bool printWireframe(const double PointA[2], double a, double b, double Z)
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;

	double tempPoint[2] = { PointA[0],PointA[1] };
	myGcodefile << "G1 F2000 Z" << Z << endl;

	myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempPoint[1] << endl;
	sumOfE += E * a;
	myGcodefile << "G1 X" << tempPoint[0]+a << " Y" << tempPoint[1] <<" E"<< sumOfE << endl;
	sumOfE += E * b;
	myGcodefile << "G1 X" << tempPoint[0] + a << " Y" << tempPoint[1]+b << " E" << sumOfE << endl;
	sumOfE += E * a;
	myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempPoint[1] + b << " E" << sumOfE << endl;
	sumOfE += E * b;
	myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempPoint[1] << " E" << sumOfE << endl;

	return true;
}