#include <opencv2\opencv.hpp>  //����opencv4.1ͷ�ļ�
#include <iostream>
using namespace std;
using namespace cv;  //opencv�������ռ�
int main(int argc, char *argv[])
{
	Mat mat1;
	mat1=imread("C:/Users/С��/Desktop/1620138717965.jpg", IMREAD_UNCHANGED);
	namedWindow("Yong",WINDOW_FREERATIO|WINDOW_KEEPRATIO|WINDOW_GUI_NORMAL|WINDOW_NORMAL);
	imshow("Yong", mat1);
	waitKey(0);
}