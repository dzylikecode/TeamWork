#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	//�Ҷ�ͼ��
	Mat mat2 = imread("D:/meng/opencv/����/learnOpenCV4-master/data/lena.png");
	Mat gray;
	cvtColor(mat2, gray, COLOR_BGR2GRAY);
	imshow("gray",gray);
	Mat matOutput;
	//����20�ı�Ϊ255��С��20�ı�Ϊ0��
	threshold(gray, matOutput, 20,255, THRESH_BINARY);
	imshow("matOutput",matOutput);
	waitKey(0);
}