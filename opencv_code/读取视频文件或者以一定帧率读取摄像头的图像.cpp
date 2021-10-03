#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int arg[],char* argv[])
{
	//����������ֵΪ0Ĭ�ϴ�����ͷ������Ϊ��Ƶ�ļ�·�������Ƶ
	VideoCapture vcap("D:/meng/opencv/code/opencv4_test/opencv4_test/����ͷ������Ƶ����.avi");
	if (vcap.isOpened())
	{
		cout << vcap.get(CAP_PROP_FRAME_WIDTH);
		cout << vcap.get(CAP_PROP_FRAME_HEIGHT);
		cout << vcap.get(CAP_PROP_FPS);
		cout << vcap.get(CAP_PROP_FRAME_COUNT);
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
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
		waitKey(1000/vcap.get(CAP_PROP_FPS));//��ʱ ��ʱ ��Ƶ֡�ʼ���
	}
	return 0;
}
