#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	Mat gray=imread("D:/meng/opencv/����/learnOpenCV4-master/data/lena.png");
	if (gray.empty())
	{
		cout << "��ȡʧ��" << endl;
		return -1;
	}
			Mat img_y,img_x,img_xy;//flip
	
	flip(gray, img_y, 1);
	flip(gray, img_x, 0);
	flip(gray, img_xy, -1);
	imshow("��y��", img_y);
	imshow("��x��", img_x);
	imshow("��x&y��", img_xy);
	waitKey(0);
}