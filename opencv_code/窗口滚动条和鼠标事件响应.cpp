#include <opencv2\opencv.hpp>  //����opencv4.1ͷ�ļ�
#include <iostream>
using namespace std;
using namespace cv;  //opencv�������ռ�


void callBack(int Pos, void* val);
void callBackmouse(int event, int x, int y, int flags, void *userdata);

int main(int argc, char *argv[])
{
	Mat mat=imread("D:/meng/opencv/����/learnOpenCV4-master/data/lena.png");
	Mat mat1(Size(2, 2), CV_8UC3, Scalar(1, 2, 3));
	Mat mat2(Size(2, 2), CV_8UC3, Scalar(4, 5, 6));
	imshow("�����������",mat);
	int value = 100;
	createTrackbar("�������ϰ�", "�����������", &value, 600, callBack,&mat1);
	setMouseCallback("�����������", callBackmouse,&mat2);

	
	waitKey(0);
}
void callBack(int Pos, void *userdata)//����Ĳ�������һ���������գ���Ϊһ�����ָ�벻�ò���
{
	/*int curPos = *(int*)val;
	cout << "val=" << curPos << endl;*/
	//Mat mat = *(Mat*)mat1;
	Mat mat(*(Mat*)userdata);
	cout << mat.at<Vec3b>(1,1);
	cout << "pos=" << Pos << endl;
}
void callBackmouse(int event, int x, int y, int flags, void *userdata) 
{
	Mat mat = *(Mat*)userdata;
	if (event==EVENT_RBUTTONDOWN)
	{
		cout << "�������ſɿ�ʼ�滭" << mat.at<Vec3b>(1, 1);
		cout << "(" << x << "," << y << ")" << endl;
	}
}