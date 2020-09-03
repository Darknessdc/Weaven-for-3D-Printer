#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

//��㣬�����abc��M�����ģʽ������tiaowen ��waves��С����������һ����M,��һ����M������N
void cube(const double PointA[2], double a, double b, double c, int M, double N)
{
	ofstream myGcodefile(myFile, ios_base::app);

	if (!myGcodefile)
	{
		cout << "false cube";
	}

	double tempPoint[2] = { PointA[0],PointA[1] };
	double tempPointWire[2] = { PointA[0] - N * 1.5,PointA[1] - N * 1.5 };
	double width = M * N * 2;
	//������������,���ĵȷ� 8.4 ʵ�ʴ�ӡЧ��
	int numOftiaowen = a / (width + 2 * N) / 2;
	//��ӡһ��ѭ������3H1���߶�
	int numOfz = c / (3 * H1);


	//��һ����Ϊ�գ��ο����ģ����ǵڶ����ƣ�����ż����,��һ��
	printWireframe(tempPointWire, a+3, b+3, H1);

	for (int i = 0; i < numOftiaowen; i++)
	{
		//���+NΪ���õ�һ���ͱ߿�ľ������  8.4 ʵ�ʴ�ӡЧ����������N
		double startPointx = tempPoint[0] + width * ((i * 2) + 1) + (i * 2)*N;
		double startPointy = tempPoint[1];
		double startPoint[2] = { startPointx ,startPointy };

		stripe(startPoint, b, H1, N, M, 1);
	}

	//7.24  ��һ����������س�
	sumOfE -= E * 10;
	myGcodefile << "G1 E" << sumOfE << endl;
	myGcodefile << "G1 F8000 Z" << H1 +1<< endl;

	for (int ii = 0; ii < numOfz; ii++)
	{
		//�ڶ��� 
		//���������������ĵȷ�
		int numOftiaowen2 = b / (width+2*N )/ 2;

		//printWireframe(tempPointWire, a+3, b+3, 2 * H1 + 3 * H1*ii);

		for (int i = 0; i < numOftiaowen2; i++)
		{
			//8.4 ʵ�ʴ�ӡЧ����������N
			double startPointx = tempPoint[0] - 1.5 * N;
			//8.4 ʵ�ʴ�ӡЧ����������N
			double startPointy = tempPoint[1] + width * ((i * 2) + 1) + N + (i * 2 + 1)*N;
			double startPoint[2] = { startPointx ,startPointy };

			//�����Ҫ��+��N����
			continueWaves2(startPoint, width + N, width + N, H1 + 3 * H1*ii, 2 * H1 + 3 * H1*ii, numOftiaowen, M, N, 1.1, 0);

			//̧��һ��z,�س� 7.24
			//sumOfE -= E * 1;
			//myGcodefile << "G1 E" << sumOfE << endl;
			//myGcodefile << "G1 F8000 Z" << 2 * H1 + 3 * H1*ii + 0.5 << endl;
		}

		//8.5��̧��
		//myGcodefile << "G1 F8000 Z" << 2 * H1 + 3 * H1*ii + 1.5 << endl;

		//������
		//printWireframe(tempPoint, a, b, tempZ);
		for (int i = 0; i < numOftiaowen; i++)
		{
			//8.4 ʵ�ʴ�ӡЧ����������N
			double startPointx = tempPoint[0] + width * ((i * 2) + 1) + (i * 2)*N- width-N;
			double startPointy = tempPoint[1]-N;
			double startPoint[2] = { startPointx ,startPointy };

			//8.5 ���˵�������������+1��
			continueWaves(startPoint, width + N, width + N, H1 + 3 * H1*ii, 2 * H1 + 3 * H1*ii, numOftiaowen2, M , N, 1, 0);
			//̧��һ��z 7.24
			//myGcodefile << "G1 F8000 Z" << 2 * H1 + 3 * H1*ii + 0.5 << " E" << sumOfE << endl;
		}

		//7.24  ��������������س�
		sumOfE -= E * 10;
		myGcodefile << "G1 E" << sumOfE << endl;
		//myGcodefile << "G1 F8000 Z" << 2 * H1 + 3 * H1*ii + 0.5 << endl;


		//���Ĳ�
		//printWireframe(tempPoint, a, b, 3 * H1 + 3 * H1*ii);
		for (int i = 0; i < numOftiaowen2; i++)
		{
			double startPointx = tempPoint[0];
			double startPointy = tempPoint[1] + width * ((i * 2) + 1) + N + (i * 2 + 1)*N- width-N-N;
			double startPoint[2] = { startPointx ,startPointy };
			stripe2(startPoint, a, 3 * H1 + 3 * H1*ii, N, M+1, 1.8);

			//̧��һ��z 7.24
			//myGcodefile << "G1 F8000 Z" << 3 * H1 + 3 * H1*ii + 0.5 << " E" << sumOfE << endl;
		}

		//8.11  ���Ĳ���������س�
		sumOfE -= E * 10;
		myGcodefile << "G1 E" << sumOfE << endl;
		//myGcodefile << "G1 F8000 Z" << 3 * H1 + 3 * H1*ii + 0.5 << endl;

		//�����
		printWireframe(tempPoint, a, b, 4 * H1 + 3 * H1*ii);
		for (int i = 0; i < numOftiaowen; i++)
		{
			double startPointx = tempPoint[0] + width * ((i * 2) + 1) + (i * 2)*N;
			double startPointy = tempPoint[1];
			double startPoint[2] = { startPointx ,startPointy };
			continueWaves(startPoint, width + N, width +N, 4 * H1 + 3 * H1*ii, 3 * H1 + 3 * H1*ii, numOftiaowen2, M, N, 1,0);
			//̧��һ��z 7.24
			//myGcodefile << "G1 F8000 Z" << 4 * H1 + 3 * H1*ii + 0.5 << " E" << sumOfE << endl;

		}

		//������
		//printWireframe(tempPoint, a, b, tempZ + H1 * 2 + H2 + H1 + H1);
		for (int i = 0; i < numOftiaowen2; i++)
		{
			double startPointx = tempPoint[0] - 1.5 * N;
			double startPointy = tempPoint[1] + width * ((i * 2) + 1) + N + (i * 2 + 1)*N;
			double startPoint[2] = { startPointx ,startPointy };
			//+N -N ����΢��
			continueWaves2(startPoint, width + N, width + N, 3 * H1 + 3 * H1*ii, 4 * H1 + 3 * H1*ii, numOftiaowen, M , N, 1,0);
			//myGcodefile << "G1 F8000 Z" << 4 * H1 + 3 * H1*ii + 0.5 << " E" << sumOfE << endl;
		}
	}

}