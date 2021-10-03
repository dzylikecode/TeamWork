#include <opencv2\opencv.hpp>  //加载opencv4.1头文件
#include <iostream>
using namespace std;
using namespace cv;  //opencv的命名空间


void callBack(int Pos, void* val);
void callBackmouse(int event, int x, int y, int flags, void *userdata);

int main(int argc, char *argv[])
{
	Mat mat=imread("D:/meng/opencv/资料/learnOpenCV4-master/data/lena.png");
	Mat mat1(Size(2, 2), CV_8UC3, Scalar(1, 2, 3));
	Mat mat2(Size(2, 2), CV_8UC3, Scalar(4, 5, 6));
	imshow("滑动条和鼠标",mat);
	int value = 100;
	createTrackbar("滑动条拖把", "滑动条和鼠标", &value, 600, callBack,&mat1);
	setMouseCallback("滑动条和鼠标", callBackmouse,&mat2);

	
	waitKey(0);
}
void callBack(int Pos, void *userdata)//传入的参数先用一个变量接收，因为一般带着指针不好操作
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
		cout << "点击左键才可开始绘画" << mat.at<Vec3b>(1, 1);
		cout << "(" << x << "," << y << ")" << endl;
	}
}