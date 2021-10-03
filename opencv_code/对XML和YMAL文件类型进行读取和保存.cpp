#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	string filename = "data.xml";
	FileStorage fwrite(filename, FileStorage::WRITE);//以写模式打开文件
	//存入Mat数据
	Mat mat = Mat::eye(3, 3, CV_8U);
	fwrite.write("mat", mat);
	float x = 100;
	fwrite << "x" << x;
	fwrite << "array" << "[" << 1 << 2 << 3<<"]";//写入["1 2 3"]
	//存入多node节点数据，主名为multi_node
	fwrite << "multi_node" << "{" << "month" << 9 << "day" << 16 << "year" << 2021
		<<"time"<<"["<<1<<2<<3<<4<<"]"<<"}";
	fwrite.release();

	//以读取方式打开
	FileStorage fread(filename, FileStorage::READ);
	if (!fread.isOpened())
	{
		cout << "打开文件失败" << endl;
		return -1;
	}
	float xread;
	fread["x"] >> xread;
	cout << "xread=" << xread << endl;
	/*读含有多个数据的array,使用filenode迭代器进行遍历
	迭代器间址出来的是filenode类型数据,可以理解为一种写文件流对象，类似ifstream*/
	FileNode fnode = fread["array"];
	cout << "array=[";
	for (FileNodeIterator it = fnode.begin();it!= fnode.end();it++)
	{
		int a;
		(*it) >> a;
		cout << a << " ";
	}
	cout << "]"<<endl;
	//读取Mat数据
	Mat matRead;
	fread["mat"] >> matRead;
	cout << "mat=" << endl;
	cout<< matRead<<endl;
	//读取含多个子节点数据，不使用FileNode+迭代器读取
	//通过filenode使用[]读取变量，再[数组下标]可以读数组元素值，
	//返回值不是之前写入的对应类型，需要自己定义变量存取或者强制类型转换
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
		//此处为什么要类型转换
		a = fileNode1["time"][i];
		cout << a<<" ";
	}
	cout << "]"<<endl;
	fread.release();
	mat.convertTo(mat, CV_32F, 1.0 / 255);
	return 0;
	
}