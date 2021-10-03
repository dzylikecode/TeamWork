#include <opencv2\opencv.hpp>  //加载opencv4.1头文件
#include <iostream>
using namespace std;
using namespace cv;  //opencv的命名空间
int main(int argc, char *argv[])
{
	Mat mat1;
	mat1=imread("C:/Users/小永/Desktop/1620138717965.jpg", IMREAD_UNCHANGED);
	namedWindow("Yong",WINDOW_FREERATIO|WINDOW_KEEPRATIO|WINDOW_GUI_NORMAL|WINDOW_NORMAL);
	imshow("Yong", mat1);
	waitKey(0);
}