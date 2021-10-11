
#include "laSerialPort.h"
#include <stdio.h>

HANDLE SerialPortOpenSync(const char* String_Device_File_Name)
{
	HANDLE COM_Handle;
	char String_Full_Device_Name[128];

	// Access to the raw COM device
	sprintf(String_Full_Device_Name, "\\\\.\\%s", String_Device_File_Name);

	// Open the serial port and set all access rights
	COM_Handle = CreateFileA(String_Full_Device_Name, //串口名
		GENERIC_READ | GENERIC_WRITE, //支持读写
		0, //独占方式，串口不支持共享
		NULL,//安全属性指针，默认值为NULL
		OPEN_EXISTING, //打开现有的串口文件
		0, //0：同步方式
		NULL);//用于复制文件句柄，默认值为NULL，对串口而言该参数必须置为NULL

	if (COM_Handle == INVALID_HANDLE_VALUE) return INVALID_HANDLE_VALUE; // Error : can't access to the serial port

	// No error
	return COM_Handle;
}

HANDLE SerialPortOpenAsync(const char* String_Device_File_Name)
{
	HANDLE COM_Handle;
	char String_Full_Device_Name[128];

	// Access to the raw COM device
	sprintf(String_Full_Device_Name, "\\\\.\\%s", String_Device_File_Name);

	// Open the serial port and set all access rights
	COM_Handle = CreateFileA(String_Full_Device_Name, //串口名
		GENERIC_READ | GENERIC_WRITE, //支持读写
		0, //独占方式，串口不支持共享
		NULL,//安全属性指针，默认值为NULL
		OPEN_EXISTING, //打开现有的串口文件
		FILE_FLAG_OVERLAPPED, //FILE_FLAG_OVERLAPPED：异步方式
		NULL);//用于复制文件句柄，默认值为NULL，对串口而言该参数必须置为NULL

	if (COM_Handle == INVALID_HANDLE_VALUE) return INVALID_HANDLE_VALUE; // Error : can't access to the serial port

	// No error
	return COM_Handle;
}

bool SetSerialPortState(HANDLE hSP, unsigned int baudrate, char parity, char databit, char stopbit)
{
	DCB COM_Parameters;
	// Configure port
	COM_Parameters.DCBlength = sizeof(DCB);
	COM_Parameters.fBinary = 1; // Must be set to 1 or Windows becomes angry
	// Ignore modem signals
	COM_Parameters.fOutxCtsFlow = 0;
	COM_Parameters.fOutxDsrFlow = 0;
	COM_Parameters.fDtrControl = DTR_CONTROL_DISABLE;
	COM_Parameters.fDsrSensitivity = 0;
	COM_Parameters.fTXContinueOnXoff = 0;
	COM_Parameters.fOutX = 0;
	COM_Parameters.fInX = 0;
	COM_Parameters.fErrorChar = 0;
	COM_Parameters.fNull = 0;
	COM_Parameters.fRtsControl = RTS_CONTROL_DISABLE;
	COM_Parameters.fAbortOnError = 0;
	COM_Parameters.fDummy2 = 0;
	COM_Parameters.wReserved = 0;
	COM_Parameters.XonLim = 0;
	COM_Parameters.XoffLim = 0;
	COM_Parameters.ByteSize = databit; 
	COM_Parameters.XonChar = 0;
	COM_Parameters.XoffChar = 0;
	COM_Parameters.ErrorChar = 0;
	COM_Parameters.EofChar = 0;
	COM_Parameters.EvtChar = 0;
	COM_Parameters.wReserved1 = 0;

	// Set requested parity
	switch (parity)
	{
	case 0:
		COM_Parameters.fParity = 0; // Disable parity checking
		COM_Parameters.Parity = NOPARITY; //无校验
		break;

	case 1:
		COM_Parameters.fParity = 1; // Enable parity checking
		COM_Parameters.Parity = ODDPARITY;//奇校验
		break;

	case 2:
		COM_Parameters.fParity = 1; // Enable parity checking
		COM_Parameters.Parity = EVENPARITY;//偶校验
		break;

	case 3:
		COM_Parameters.fParity = 1; // Enable parity checking
		COM_Parameters.Parity = MARKPARITY; //标记校验
		break;

	default:
		return false;
	}

	switch (stopbit) //停止位
	{
	case 1:
		COM_Parameters.StopBits = ONESTOPBIT; //1位停止位
		break;
	case 2:
		COM_Parameters.StopBits = TWOSTOPBITS; //2位停止位
		break;
	case 3:
		COM_Parameters.StopBits = ONE5STOPBITS; //1.5位停止位
		break;
	}

	// Set transmit and receive speed
	COM_Parameters.BaudRate = baudrate;

	// Set new parameters
	if (!SetCommState(hSP, &COM_Parameters))
	{
		// 设置参数失败
		return false;
	}

	return true;
}

bool SetSerialPortTimeOut(HANDLE hSP, DWORD rInverval, DWORD rMulti, DWORD rConst, DWORD wMulti, DWORD wConst)
{
	//超时处理,单位：毫秒
	COMMTIMEOUTS Timing_Parameters;
	// Make reads non blocking

	Timing_Parameters.ReadIntervalTimeout = rInverval;		//读间隔超时
	//两字符之间最大的延时，
	//当读取串口数据时，时间周期从第一个字符接收到算起,一旦两个字符传输的时间差超过该时间，
	//ReadFile操作完毕并返回所有缓冲数据。
	//设置为0表示该参数不起作用。 
	//如果值为MAXDWORD, 并且ReadTotalTimeoutConstant和ReadTotalTimeoutMultiplier两个值都为0, 
	//则指定读操作携带已经收到的字符立即返回，即使没有收到任何字符。


	//总超时＝时间系数×读或写的字符数＋时间常量
	Timing_Parameters.ReadTotalTimeoutMultiplier = rMulti;	//读时间系数
	Timing_Parameters.ReadTotalTimeoutConstant = rConst;	//读时间常量


	Timing_Parameters.WriteTotalTimeoutMultiplier = wMulti;	// 写时间系数
	Timing_Parameters.WriteTotalTimeoutConstant = wConst;	//写时间常量
	return SetCommTimeouts(hSP, &Timing_Parameters);
}

bool SetSerialPortBufferSize(HANDLE hSP, DWORD inSize, DWORD outSize)
{
	return SetupComm(hSP, inSize, outSize);
}

bool ClearSerialPortBuffer(HANDLE hSP)
{
	return PurgeComm(hSP, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空串口缓冲区
}

bool CloseSerialPort(HANDLE hSP)
{
	return CloseHandle(hSP);
}

int  SendSerialPortSync(HANDLE hSP, const BYTE* buffer, int len)
{
	// 同步方式
	DWORD dwBytesWrite = len; //成功写入的数据字节数
	BOOL bWriteStat = WriteFile(hSP, //串口句柄
		buffer, //数据首地址
		dwBytesWrite, //要发送的数据字节数
		&dwBytesWrite, //DWORD*，用来接收返回成功发送的数据字节数
		NULL); //NULL为同步发送

	if (!bWriteStat) return 0;

	return dwBytesWrite;
}

int  SendSerialPortAsync(HANDLE hSP, const BYTE* buffer, int len)
{
	//异步方式
	DWORD dwBytesWrite = len;		//成功写入的数据字节数
	DWORD dwErrorFlags;				//错误标志
	COMSTAT comStat;				//通讯状态
	OVERLAPPED m_osWrite;			//异步输入输出结构体

	//创建一个用于OVERLAPPED的事件处理，不会真正用到，但系统要求这么做
	memset(&m_osWrite, 0, sizeof(m_osWrite));
	m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("WriteEvent"));

	ClearCommError(hSP, &dwErrorFlags, &comStat); //清除通讯错误，获得设备当前状态
	BOOL bWriteStat = WriteFile(hSP,	//串口句柄
		buffer,							//数据首地址
		dwBytesWrite,					//要发送的数据字节数
		&dwBytesWrite,					//DWORD*，用来接收返回成功发送的数据字节数
		&m_osWrite);					//，OVERLAPPED*为异步发送
	if (!bWriteStat)
	{
		if (GetLastError() == ERROR_IO_PENDING) //如果串口正在写入
		{
			WaitForSingleObject(m_osWrite.hEvent, 1000); //等待写入事件1秒钟
		}
		else
		{
			ClearCommError(hSP, &dwErrorFlags, &comStat); //清除通讯错误
			CloseHandle(m_osWrite.hEvent); //关闭并释放hEvent内存
			return 0;
		}
	}
	return dwBytesWrite;
}

int  ReceiveSerialPortSync(HANDLE hSP, BYTE* buffer, int maxLen)
{
	//同步方式
	DWORD wCount = maxLen; //成功读取的数据字节数
	BOOL bReadStat = ReadFile(hSP,	//串口句柄
		buffer,						//数据首地址
		wCount,						//要读取的数据最大字节数
		&wCount,					//DWORD*,用来接收返回成功读取的数据字节数
		NULL);						//NULL为同步发送
	if (!bReadStat) return 0;

	return wCount;
}

int  ReceiveSerialPortAsync(HANDLE hSP, BYTE* buffer, int maxLen)
{
	//异步方式
	DWORD wCount = maxLen; //成功读取的数据字节数
	DWORD dwErrorFlags; //错误标志
	COMSTAT comStat; //通讯状态
	OVERLAPPED m_osRead; //异步输入输出结构体

	//创建一个用于OVERLAPPED的事件处理，不会真正用到，但系统要求这么做
	memset(&m_osRead, 0, sizeof(m_osRead));
	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("ReadEvent"));

	ClearCommError(hSP, &dwErrorFlags, &comStat); //清除通讯错误，获得设备当前状态
	if (!comStat.cbInQue)return 0; //如果输入缓冲区字节数为0，则返回false

	BOOL bReadStat = ReadFile(hSP,	//串口句柄
		buffer,						//数据首地址
		wCount,						//要读取的数据最大字节数
		&wCount,					//DWORD*,用来接收返回成功读取的数据字节数
		&m_osRead);					//OVERLAPPED*为异步发送
	if (!bReadStat)
	{
		if (GetLastError() == ERROR_IO_PENDING) //如果串口正在读取中
		{
			//GetOverlappedResult函数的最后一个参数设为TRUE
			//函数会一直等待，直到读操作完成或由于错误而返回
			GetOverlappedResult(hSP, &m_osRead, &wCount, TRUE);
		}
		else
		{
			ClearCommError(hSP, &dwErrorFlags, &comStat); //清除通讯错误
			CloseHandle(m_osRead.hEvent); //关闭并释放hEvent的内存
			return 0;
		}
	}
	return wCount;
}