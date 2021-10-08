#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
	Mat mat1;
	mat1 = imread("C:/Users/小永/Desktop/1620138717965.jpg",IMREAD_UNCHANGED);
	vector <int> compress_params;
	compress_params.push_back(IMWRITE_PNG_COMPRESSION);
	compress_params.push_back(9);
	//使用vector容器对第三个参数进行赋值，对输出的图片的属性进行设置
	bool result = imwrite("C:/Users/小永/Desktop/合照1.png", mat1, compress_params);
	if (result)
	{
		cout << "保存成功" << endl;
	}
	else {
		cout << "保存失败" << endl;
		return -1;
	}
	return 0;
}
