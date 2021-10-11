#include "La_NetWorkBase.h"


#pragma comment(lib, "Urlmon.lib")
#pragma comment(lib, "Ws2_32.lib")
namespace
{
	WSADATA wsaData;
}

namespace LADZY
{
	bool InitializeNetWork()
	{
		//��Windows Sockets�Ķ�̬���ӿ�WS2_32.dll���г�ʼ��,�汾��Ϊ 2.2
		int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (result != 0)
		{
			/*MessageWarn(TEXT("WSAStartupʧ�ܣ�%d\n"), result);*/
			return false;
		}
		return true;
	}

	bool CloseNetWork()
	{
		WSACleanup();
		return true;
	}
}

