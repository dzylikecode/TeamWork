#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
	Mat mat1;
	mat1 = imread("C:/Users/С��/Desktop/1620138717965.jpg",IMREAD_UNCHANGED);
	vector <int> compress_params;
	compress_params.push_back(IMWRITE_PNG_COMPRESSION);
	compress_params.push_back(9);
	//ʹ��vector�����Ե������������и�ֵ���������ͼƬ�����Խ�������
	bool result = imwrite("C:/Users/С��/Desktop/����1.png", mat1, compress_params);
	if (result)
	{
		cout << "����ɹ�" << endl;
	}
	else {
		cout << "����ʧ��" << endl;
		return -1;
	}
	return 0;
}
