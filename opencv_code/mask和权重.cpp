#include <opencv2\opencv.hpp>  //����opencv4.1ͷ�ļ�
#include <iostream>
using namespace std;
using namespace cv;  //opencv�������ռ�
int main()
{
	Mat  img;
	img = imread("C:/Users/С��/Pictures/Saved Pictures/΢��ͼƬ_20210811182335.jpg");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("test", img);	//��ʾͼ��
	Mat mask(img.rows, img.cols, CV_8UC3);
	for(int i=0;i<img.rows;i++)
	{
		for (int j=0;j<img.cols;j++)
		{
			mask.at<Vec3b>(i, j).val[0]=0;
			mask.at<Vec3b>(i, j).val[1] = 0;
			mask.at<Vec3b>(i, j).val[2] = (uchar)(255.0/img.cols*j);
		}
	}
	Mat output;
	addWeighted(img, 1.0, mask, 0.6, 0, output);
	imshow("mask", mask);
	
	
	/*bitwise_or(img, mask, output);*/
	namedWindow("output", WINDOW_NORMAL);
	imshow("output", output);

	

	waitKey(0);  //�ȴ� ��������
	return 0;
}