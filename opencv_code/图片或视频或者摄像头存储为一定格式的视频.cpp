#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	Mat img;
	VideoCapture video(0);
	if (!video.isOpened())
	{
		cout << "打开失败" << endl;
		return -1;
	}
	video >> img;
	if (img.empty())
	{
		cout << "没有获取到图像" << endl;
		return -1;
	}
	bool isColor = (img.type() == CV_8UC3);//判断相机是否是彩色的
	
	VideoWriter writer;
	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
	double fps = 25.0;
	string  filename = "摄像头捕获视频下载.avi";
	writer.open(filename, codec,fps,img.size(), isColor);
	if (!writer.isOpened())//判断视频流是否创建成功
	{
		cout << "打开有误" << endl;
		return -1;
	}
	while (1)
	{
		if (!video.read(img))
		{
			//摄像头断开连接没有图像可读，视频读取完成会将img变为空矩阵
			cout << "摄像头连接断开或者视频读取完成" << endl;
			break;
		}
		writer.write(img);//将图像写入视频流如果img一直不为空，就一直循环写入
		//writer<<img;也可以实现图像写入视频流
		imshow("摄像头捕获视频下载", img);
		char c = waitKey(50);
		if (c==27)
		{
			break;
		}
	}
	video.release();
	writer.release();
}