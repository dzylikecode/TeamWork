#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	Mat mat = imread("D:/meng/opencv/资料/learnOpenCV4-master/data/lena.png");
	if (mat.empty())
	{
		cout << "读取失败" << endl;
		return -1;
	}
	//Range range1(0,2);
	//Mat mat3(Size(3, 3), CV_8UC3, Scalar(1, 2, 3));
	//mat3.at<Vec3b>(0, 0).val[2]=0;
	//Mat mat4(mat3, range1, range1);

	//将图片拆为子图，再合并
	Range range1(0, 256), range2(256, 512);
	Mat l_u(mat, range1, range1);
	Mat r_u(mat, range1, range2);
	Mat l_d(mat, range2, range1);
	Mat r_d(mat, range2, range2);
	imshow("l_u", l_u);
	imshow("r_u", r_u);
	imshow("l_d", l_d);
	imshow("r_d", r_d);

	Mat lr1,lr2,out;
	
	hconcat(l_u, r_u, lr1);
	hconcat(l_d, r_d, lr2);
	vconcat(lr1, lr2,out);
	imshow("lr1", lr1);
	imshow("lr2", lr2);
	imshow("out", out);

	//Mat数组连接
	Mat mat2[4] = { mat,mat,mat,mat };
	Mat out1,out2,out3,out4;
	//竖直连接
	vconcat(mat2,sizeof(mat2)/sizeof(mat),out1);
	imshow("out1",out1);
	//水平连接
	hconcat(mat2, sizeof(mat2) / sizeof(mat), out2);
	imshow("out2", out2);

	//两个Mat连接
	vconcat(mat, mat, out3);
	imshow("out3", out3);
	hconcat(mat, mat, out4);
	imshow("out4", out4);

	//图像尺寸变换
	waitKey(0);
}