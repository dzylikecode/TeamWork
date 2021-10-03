#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	Mat mat = imread("D:/meng/opencv/����/learnOpenCV4-master/data/lena.png");
	if (mat.empty())
	{
		cout << "ͼ�����ʧ��";
	}
	Mat mat1(Size(1,2 ),CV_8UC3, Scalar(1, 2, 3));
	//reshape���뱣֤��������ݸ����غ㡣
	/*��row*col*channel����ǰ����ȣ����ݲ������ѭ���ϵ��´�������*/
	/*   mat1=mat1.reshape(2, 3);  */
	mat1 = mat1.reshape(1, 1);
	double minVal,maxVal;
	Point minLoc, maxLoc;
	cout << mat1.channels() << endl;
	cout << mat1.rows << endl;
	cout << mat1.cols << endl;
	//ֻ���ҳ�һ��������С�������λ��point������ǰ���ں�
	minMaxLoc(mat1,&maxVal,&minVal,&minLoc,&maxLoc,noArray());
	cout << "minVal=" << minVal << "λ��" << minLoc << endl;
	cout << "maxVal=" << maxVal << "λ��" << maxLoc << endl;
	mat1 = mat1.reshape(2, 1);
	Scalar scalar;
	scalar = mean(mat1, noArray());
	cout << "scalar:" << scalar[0]<<" "<<scalar[1]<<" "<<scalar[2]<<" "<<scalar[3] << endl;
	Mat meanMat, stdDevMat;
	meanStdDev(mat1, meanMat, stdDevMat);
	cout << "��׼��=" << stdDevMat << endl;
	cout << "ƽ��ֵ=" << meanMat << endl;
	waitKey(0);
}