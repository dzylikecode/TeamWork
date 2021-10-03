#include <opencv2\opencv.hpp>  //加载opencv4.1头文件
#include <iostream>
using namespace std;
using namespace cv;  //opencv的命名空间
int main(int argc, char *argv[])
{
	Mat img = Mat::zeros(Size(512, 512), CV_8UC3);
	//画与矩阵内切的椭圆
	ellipse(img, RotatedRect(Point2f(150, 100), Size2f(200, 200), 0), Scalar(0, 0, 255),2);
	//生成文字
	putText(img, "Learn", Point(0,512), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255));
	imshow("img", img);
	Point point(0, 512);
	cout << point.x;
	waitKey(0);
}