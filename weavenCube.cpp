#include"initGcode.h"
#include<fstream>
#include<iostream>
using namespace std;

//起点，长宽高abc，M是填充模式决定了tiaowen 和waves的小条纹数量，一个是M,另一个是M，喷嘴N
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
	//大竖条纹数量,长的等分 8.4 实际打印效果
	int numOftiaowen = a / (width + 2 * N) / 2;
	//打印一次循环上升3H1个高度
	int numOfz = c / (3 * H1);


	//第一道纹为空，参考论文，这是第二道纹，都是偶数纹,第一层
	printWireframe(tempPointWire, a+3, b+3, H1);

	for (int i = 0; i < numOftiaowen; i++)
	{
		//最后+N为了让第一道和边框的距离合理  8.4 实际打印效果改了最后的N
		double startPointx = tempPoint[0] + width * ((i * 2) + 1) + (i * 2)*N;
		double startPointy = tempPoint[1];
		double startPoint[2] = { startPointx ,startPointy };

		stripe(startPoint, b, H1, N, M, 1);
	}

	//7.24  第一层结束少量回抽
	sumOfE -= E * 10;
	myGcodefile << "G1 E" << sumOfE << endl;
	myGcodefile << "G1 F8000 Z" << H1 +1<< endl;

	for (int ii = 0; ii < numOfz; ii++)
	{
		//第二层 
		//大横条纹数量，宽的等分
		int numOftiaowen2 = b / (width+2*N )/ 2;

		//printWireframe(tempPointWire, a+3, b+3, 2 * H1 + 3 * H1*ii);

		for (int i = 0; i < numOftiaowen2; i++)
		{
			//8.4 实际打印效果改了最后的N
			double startPointx = tempPoint[0] - 1.5 * N;
			//8.4 实际打印效果改了最后的N
			double startPointy = tempPoint[1] + width * ((i * 2) + 1) + N + (i * 2 + 1)*N;
			double startPoint[2] = { startPointx ,startPointy };

			//这边需要不+—N？？
			continueWaves2(startPoint, width + N, width + N, H1 + 3 * H1*ii, 2 * H1 + 3 * H1*ii, numOftiaowen, M, N, 1.1, 0);

			//抬高一下z,回抽 7.24
			//sumOfE -= E * 1;
			//myGcodefile << "G1 E" << sumOfE << endl;
			//myGcodefile << "G1 F8000 Z" << 2 * H1 + 3 * H1*ii + 0.5 << endl;
		}

		//8.5加抬高
		//myGcodefile << "G1 F8000 Z" << 2 * H1 + 3 * H1*ii + 1.5 << endl;

		//第三层
		//printWireframe(tempPoint, a, b, tempZ);
		for (int i = 0; i < numOftiaowen; i++)
		{
			//8.4 实际打印效果改了最后的N
			double startPointx = tempPoint[0] + width * ((i * 2) + 1) + (i * 2)*N- width-N;
			double startPointy = tempPoint[1]-N;
			double startPoint[2] = { startPointx ,startPointy };

			//8.5 改了倒数第三个参数+1了
			continueWaves(startPoint, width + N, width + N, H1 + 3 * H1*ii, 2 * H1 + 3 * H1*ii, numOftiaowen2, M , N, 1, 0);
			//抬高一下z 7.24
			//myGcodefile << "G1 F8000 Z" << 2 * H1 + 3 * H1*ii + 0.5 << " E" << sumOfE << endl;
		}

		//7.24  第三层结束少量回抽
		sumOfE -= E * 10;
		myGcodefile << "G1 E" << sumOfE << endl;
		//myGcodefile << "G1 F8000 Z" << 2 * H1 + 3 * H1*ii + 0.5 << endl;


		//第四层
		//printWireframe(tempPoint, a, b, 3 * H1 + 3 * H1*ii);
		for (int i = 0; i < numOftiaowen2; i++)
		{
			double startPointx = tempPoint[0];
			double startPointy = tempPoint[1] + width * ((i * 2) + 1) + N + (i * 2 + 1)*N- width-N-N;
			double startPoint[2] = { startPointx ,startPointy };
			stripe2(startPoint, a, 3 * H1 + 3 * H1*ii, N, M+1, 1.8);

			//抬高一下z 7.24
			//myGcodefile << "G1 F8000 Z" << 3 * H1 + 3 * H1*ii + 0.5 << " E" << sumOfE << endl;
		}

		//8.11  第四层结束少量回抽
		sumOfE -= E * 10;
		myGcodefile << "G1 E" << sumOfE << endl;
		//myGcodefile << "G1 F8000 Z" << 3 * H1 + 3 * H1*ii + 0.5 << endl;

		//第五层
		printWireframe(tempPoint, a, b, 4 * H1 + 3 * H1*ii);
		for (int i = 0; i < numOftiaowen; i++)
		{
			double startPointx = tempPoint[0] + width * ((i * 2) + 1) + (i * 2)*N;
			double startPointy = tempPoint[1];
			double startPoint[2] = { startPointx ,startPointy };
			continueWaves(startPoint, width + N, width +N, 4 * H1 + 3 * H1*ii, 3 * H1 + 3 * H1*ii, numOftiaowen2, M, N, 1,0);
			//抬高一下z 7.24
			//myGcodefile << "G1 F8000 Z" << 4 * H1 + 3 * H1*ii + 0.5 << " E" << sumOfE << endl;

		}

		//第六层
		//printWireframe(tempPoint, a, b, tempZ + H1 * 2 + H2 + H1 + H1);
		for (int i = 0; i < numOftiaowen2; i++)
		{
			double startPointx = tempPoint[0] - 1.5 * N;
			double startPointy = tempPoint[1] + width * ((i * 2) + 1) + N + (i * 2 + 1)*N;
			double startPoint[2] = { startPointx ,startPointy };
			//+N -N 进行微调
			continueWaves2(startPoint, width + N, width + N, 3 * H1 + 3 * H1*ii, 4 * H1 + 3 * H1*ii, numOftiaowen, M , N, 1,0);
			//myGcodefile << "G1 F8000 Z" << 4 * H1 + 3 * H1*ii + 0.5 << " E" << sumOfE << endl;
		}
	}

}