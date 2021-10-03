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
		cout << "��ʧ��" << endl;
		return -1;
	}
	video >> img;
	if (img.empty())
	{
		cout << "û�л�ȡ��ͼ��" << endl;
		return -1;
	}
	bool isColor = (img.type() == CV_8UC3);//�ж�����Ƿ��ǲ�ɫ��
	
	VideoWriter writer;
	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
	double fps = 25.0;
	string  filename = "����ͷ������Ƶ����.avi";
	writer.open(filename, codec,fps,img.size(), isColor);
	if (!writer.isOpened())//�ж���Ƶ���Ƿ񴴽��ɹ�
	{
		cout << "������" << endl;
		return -1;
	}
	while (1)
	{
		if (!video.read(img))
		{
			//����ͷ�Ͽ�����û��ͼ��ɶ�����Ƶ��ȡ��ɻὫimg��Ϊ�վ���
			cout << "����ͷ���ӶϿ�������Ƶ��ȡ���" << endl;
			break;
		}
		writer.write(img);//��ͼ��д����Ƶ�����imgһֱ��Ϊ�գ���һֱѭ��д��
		//writer<<img;Ҳ����ʵ��ͼ��д����Ƶ��
		imshow("����ͷ������Ƶ����", img);
		char c = waitKey(50);
		if (c==27)
		{
			break;
		}
	}
	video.release();
	writer.release();
}