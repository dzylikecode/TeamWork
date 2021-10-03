#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int arg[],char* argv[])
{
	//类对象参数赋值为0默认打开摄像头，参数为视频文件路径则打开视频
	VideoCapture vcap("D:/meng/opencv/code/opencv4_test/opencv4_test/摄像头捕获视频下载.avi");
	if (vcap.isOpened())
	{
		cout << vcap.get(CAP_PROP_FRAME_WIDTH);
		cout << vcap.get(CAP_PROP_FRAME_HEIGHT);
		cout << vcap.get(CAP_PROP_FPS);
		cout << vcap.get(CAP_PROP_FRAME_COUNT);
	}
	else
	{
		cout << "文件打开失败" << endl;
		return -1;
	}
	while (1)
	{
		Mat frame;
		vcap >> frame;
		if (frame.empty())
		{
			break;
		}
		imshow("video", frame);
		waitKey(1000/vcap.get(CAP_PROP_FPS));//延时 延时 视频帧率计算
	}
	return 0;
}
