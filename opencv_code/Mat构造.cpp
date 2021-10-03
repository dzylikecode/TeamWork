#include <opencv2\opencv.hpp>  //加载opencv4.1头文件
#include <iostream>
using namespace std;
using namespace cv;		//opencv的命名空间
int main(int argc, char* argv[])
{
	Mat mat1;
	Mat mat2 = Mat_<double>(3, 3);
	Mat mat3(3, 3, CV_8UC3);
	Mat mat4();
	mat1 = Mat::Mat(3, 3, CV_8UC3,Scalar(1,2,3));//将所有像素值赋值为[1,2,3]

	Vec3i vc3 =mat1.at<Vec3b>(0, 0);
	cout<<"vc3.val[0]="<<vc3.val[0]<<endl;
	Mat mat5 = (Mat_<int>(1, 3));
	//Mat mat6 = Mat::diag(mat5);
	float a[5] = {1, 2, 3, 4, 5};
	Mat mat6 = Mat(Size(2, 5), CV_32FC1);
	mat6 = Mat(2, 5,CV_32FC1, a);
	mat6.at<float>(0, 1)=1.2;
	cout << mat6.at<float>(0, 1);
	Mat mat7 = Mat::ones(3, 3, CV_8UC1);
}