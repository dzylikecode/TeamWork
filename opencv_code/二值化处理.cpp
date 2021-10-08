#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	//灰度图像
	Mat mat2 = imread("D:/meng/opencv/资料/learnOpenCV4-master/data/lena.png");
	Mat gray;
	cvtColor(mat2, gray, COLOR_BGR2GRAY);
	imshow("gray",gray);
	Mat matOutput;
	//大于20的变为255，小于20的变为0；
	threshold(gray, matOutput, 20,255, THRESH_BINARY);
	imshow("matOutput",matOutput);
	waitKey(0);
}