#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	Mat mat1 = imread("D:/meng/opencv/����/learnOpenCV4-master/data/lena.png");
	if (mat1.empty())
	{
		cout << "��ʧ��" << endl;
		return -1;
	}
	imshow("mat1",mat1);
	Mat mat2[3];
	split(mat1, mat2);
	Mat mat3 = mat2[0];
	mat2[0] = mat1;
	imshow("mat2[0]", mat2[0]);
	Mat result0;
	//��ʱresult0Ϊ5ͨ����Mat
	merge(mat2, 3, result0);
	imshow("result0", result0);
	//mergeʵ�ֵĹ���һһ��Ӧ���γ�һ����ͨ�����ݡ�
	Mat mat4(1, 3, CV_8UC1, Scalar(1));
	Mat mat5(1, 3, CV_8UC1, Scalar(2));
	Mat mat6(1, 3, CV_8UC1, Scalar(3));
	vector <Mat> mattree;
	mattree.push_back(mat4);
	mattree.push_back(mat5);
	mattree.push_back(mat6);
	Mat mat7;
	merge(mattree, mat7);
	waitKey(0);
}