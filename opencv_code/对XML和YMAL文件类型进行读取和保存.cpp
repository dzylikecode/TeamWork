#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	string filename = "data.xml";
	FileStorage fwrite(filename, FileStorage::WRITE);//��дģʽ���ļ�
	//����Mat����
	Mat mat = Mat::eye(3, 3, CV_8U);
	fwrite.write("mat", mat);
	float x = 100;
	fwrite << "x" << x;
	fwrite << "array" << "[" << 1 << 2 << 3<<"]";//д��["1 2 3"]
	//�����node�ڵ����ݣ�����Ϊmulti_node
	fwrite << "multi_node" << "{" << "month" << 9 << "day" << 16 << "year" << 2021
		<<"time"<<"["<<1<<2<<3<<4<<"]"<<"}";
	fwrite.release();

	//�Զ�ȡ��ʽ��
	FileStorage fread(filename, FileStorage::READ);
	if (!fread.isOpened())
	{
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}
	float xread;
	fread["x"] >> xread;
	cout << "xread=" << xread << endl;
	/*�����ж�����ݵ�array,ʹ��filenode���������б���
	��������ַ��������filenode��������,�������Ϊһ��д�ļ�����������ifstream*/
	FileNode fnode = fread["array"];
	cout << "array=[";
	for (FileNodeIterator it = fnode.begin();it!= fnode.end();it++)
	{
		int a;
		(*it) >> a;
		cout << a << " ";
	}
	cout << "]"<<endl;
	//��ȡMat����
	Mat matRead;
	fread["mat"] >> matRead;
	cout << "mat=" << endl;
	cout<< matRead<<endl;
	//��ȡ������ӽڵ����ݣ���ʹ��FileNode+��������ȡ
	//ͨ��filenodeʹ��[]��ȡ��������[�����±�]���Զ�����Ԫ��ֵ��
	//����ֵ����֮ǰд��Ķ�Ӧ���ͣ���Ҫ�Լ����������ȡ����ǿ������ת��
	FileNode fileNode1 = fread["multi_node"];
	int month = fileNode1["month"];
	int day = fileNode1["day"];
	int year = fileNode1["year"];
	cout << "multi_node:" << endl
		<< "month=" << month<<endl
		<< "day=" << day<<endl
		<< "year=" << year<<endl;
	cout << "time=[";
	for (int i=0;i<4;i++)
	{
		int a;
		//�˴�ΪʲôҪ����ת��
		a = fileNode1["time"][i];
		cout << a<<" ";
	}
	cout << "]"<<endl;
	fread.release();
	mat.convertTo(mat, CV_32F, 1.0 / 255);
	return 0;
	
}