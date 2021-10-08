#include <opencv2\opencv.hpp>  //加载opencv4.1头文件
#include <iostream>
using namespace std;
using namespace cv;  //opencv的命名空间
int main()
{
	Mat  img;
	img = imread("C:/Users/小永/Pictures/Saved Pictures/微信图片_20210811182335.jpg");
	if (img.empty())
	{
		cout << "请确认图像文件名称是否正确" << endl;
		return -1;
	}
	imshow("test", img);	//显示图像
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

	

	waitKey(0);  //等待 键盘输入
	return 0;
}