#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	Mat mat = imread("D:/meng/opencv/资料/learnOpenCV4-master/data/lena.png");
	if (mat.empty())
	{
		cout << "图像读入失败";
	}
	Mat mat1(Size(1,2 ),CV_8UC3, Scalar(1, 2, 3));
	//reshape必须保证处理的数据个数守恒。
	/*即row*col*channel必须前后相等，数据拆分是遵循从上到下从左往右*/
	/*   mat1=mat1.reshape(2, 3);  */
	mat1 = mat1.reshape(1, 1);
	double minVal,maxVal;
	Point minLoc, maxLoc;
	cout << mat1.channels() << endl;
	cout << mat1.rows << endl;
	cout << mat1.cols << endl;
	//只能找出一个最大和最小，输出的位置point是列在前行在后。
	minMaxLoc(mat1,&maxVal,&minVal,&minLoc,&maxLoc,noArray());
	cout << "minVal=" << minVal << "位置" << minLoc << endl;
	cout << "maxVal=" << maxVal << "位置" << maxLoc << endl;
	mat1 = mat1.reshape(2, 1);
	Scalar scalar;
	scalar = mean(mat1, noArray());
	cout << "scalar:" << scalar[0]<<" "<<scalar[1]<<" "<<scalar[2]<<" "<<scalar[3] << endl;
	Mat meanMat, stdDevMat;
	meanStdDev(mat1, meanMat, stdDevMat);
	cout << "标准差=" << stdDevMat << endl;
	cout << "平均值=" << meanMat << endl;
	waitKey(0);
}