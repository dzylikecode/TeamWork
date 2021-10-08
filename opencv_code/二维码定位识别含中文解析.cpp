#include <opencv2\opencv.hpp>  //����opencv4.1ͷ�ļ�
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
using namespace cv;  //opencv�������ռ�
std::wstring AToW_U8(std::string pszInBuf)
{
	wstring result;
	int nInSize = pszInBuf.length();
	int pnOutSize = MultiByteToWideChar(CP_UTF8, NULL, pszInBuf.c_str(), nInSize, nullptr, 0);// ��ȡ��ת���ַ����Ļ����������С
	if (pnOutSize == 0)
		return result;
	wchar_t *temp = new wchar_t[pnOutSize+1];
	if (MultiByteToWideChar(CP_UTF8, NULL, pszInBuf.c_str(), nInSize, temp, pnOutSize) == 0)
	{
		result.clear();
		return result;
	}
	temp[pnOutSize] = 0;
	result = temp;
	delete[]temp;
	return result;
}

std::string W_U8ToA(std::wstring pszInBuf)
{
	string result;
	int nInSize = pszInBuf.length();
	int pnOutSize = WideCharToMultiByte(NULL, NULL, pszInBuf.c_str(), nInSize, nullptr, 0,nullptr,nullptr);// ��ȡ��ת���ַ����Ļ����������С
	if (pnOutSize == 0)
		return result;
	char *temp = new char[pnOutSize + 1];
	if (WideCharToMultiByte(NULL, NULL, pszInBuf.c_str(), nInSize, temp, pnOutSize,0,nullptr) == 0)
	{
		result.clear();
		return result;
	}
	temp[pnOutSize] = 0;
	result = temp;
	delete[]temp;
	return result;
}

int main(int argc, char *argv[])
{
	vector<Point> points;
	Mat  qrCode_img = imread("C:\\Users\\С��\\Desktop\\��ά��.png", IMREAD_UNCHANGED);
	if (qrCode_img.empty())
	{
		cout << "��ȡͼƬʧ��" << endl;
		return -1;
	}
	bool result = false;
	QRCodeDetector qrcodedetector;
	result = qrcodedetector.detect(qrCode_img, points);
	string information;
	Mat two_qr;
	if (result)
	{
		information = qrcodedetector.decode(qrCode_img, points,two_qr);
	}
	else
	{
		return -1;
	}
	int infor_length = information.length();
	vector<int> arr;
	for (int i=0;i<infor_length;i++)
	{
		arr.push_back((int)information[i]);
		unsigned char ch = information[i];
		int iChch = ch;
		cout << hex << iChch;
	}
	wstring res = AToW_U8(information);
	cout << "��ά����Ϣ��" << W_U8ToA(res) << endl;
	
	namedWindow("�����Ͷ�ֵ���Ķ�ά��", WINDOW_NORMAL);
	imshow("�����Ͷ�ֵ���Ķ�ά��", two_qr);
	waitKey(0);
}