#include <opencv2\opencv.hpp>  //加载opencv4.1头文件
#include <iostream>
using namespace std;
using namespace cv;  //opencv的命名空间
int main(int argc, char *argv[])
{
	Mat mat1(Size(10,10), CV_8UC3,Scalar(1,2,3));

	MatIterator_<Vec3b> it = mat1.begin<Vec3b>();
	MatIterator_<Vec3b> it_end = mat1.end<Vec3b>();
	for (int i = 0; it != it_end; it++)
	{
		 cout<<(*it).val[0]<<" ";
		if (++i%mat1.cols == 0)
		{
			cout << endl;
		}
	}
	Vec3b vc1 = mat1.at<Vec3b>(0, 0).val[0];
	cout <<"vc1="<<vc1;
	//cout << (int)vc1.val[0]<<endl;

	/*for (int i = 0; i < mat1.rows; i++)
	{	
		uchar *ptr = mat1.ptr<uchar>(i);
		for (int j = 0; j < mat1.cols*mat1.channels(); j++)
		{
			ptr[j] = i + j;
		}
	}*/
	
	namedWindow("永江之窗", WINDOW_AUTOSIZE | WINDOW_KEEPRATIO | WINDOW_GUI_EXPANDED);
	imshow("永江之窗",mat1);
	waitKey(0);
}
