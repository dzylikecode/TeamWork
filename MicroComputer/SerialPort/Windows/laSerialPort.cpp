
#include "laSerialPort.h"
#include <stdio.h>

HANDLE SerialPortOpenSync(const char* String_Device_File_Name)
{
	HANDLE COM_Handle;
	char String_Full_Device_Name[128];

	// Access to the raw COM device
	sprintf(String_Full_Device_Name, "\\\\.\\%s", String_Device_File_Name);

	// Open the serial port and set all access rights
	COM_Handle = CreateFileA(String_Full_Device_Name, //������
		GENERIC_READ | GENERIC_WRITE, //֧�ֶ�д
		0, //��ռ��ʽ�����ڲ�֧�ֹ���
		NULL,//��ȫ����ָ�룬Ĭ��ֵΪNULL
		OPEN_EXISTING, //�����еĴ����ļ�
		0, //0��ͬ����ʽ
		NULL);//���ڸ����ļ������Ĭ��ֵΪNULL���Դ��ڶ��Ըò���������ΪNULL

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
	COM_Handle = CreateFileA(String_Full_Device_Name, //������
		GENERIC_READ | GENERIC_WRITE, //֧�ֶ�д
		0, //��ռ��ʽ�����ڲ�֧�ֹ���
		NULL,//��ȫ����ָ�룬Ĭ��ֵΪNULL
		OPEN_EXISTING, //�����еĴ����ļ�
		FILE_FLAG_OVERLAPPED, //FILE_FLAG_OVERLAPPED���첽��ʽ
		NULL);//���ڸ����ļ������Ĭ��ֵΪNULL���Դ��ڶ��Ըò���������ΪNULL

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
		COM_Parameters.Parity = NOPARITY; //��У��
		break;

	case 1:
		COM_Parameters.fParity = 1; // Enable parity checking
		COM_Parameters.Parity = ODDPARITY;//��У��
		break;

	case 2:
		COM_Parameters.fParity = 1; // Enable parity checking
		COM_Parameters.Parity = EVENPARITY;//żУ��
		break;

	case 3:
		COM_Parameters.fParity = 1; // Enable parity checking
		COM_Parameters.Parity = MARKPARITY; //���У��
		break;

	default:
		return false;
	}

	switch (stopbit) //ֹͣλ
	{
	case 1:
		COM_Parameters.StopBits = ONESTOPBIT; //1λֹͣλ
		break;
	case 2:
		COM_Parameters.StopBits = TWOSTOPBITS; //2λֹͣλ
		break;
	case 3:
		COM_Parameters.StopBits = ONE5STOPBITS; //1.5λֹͣλ
		break;
	}

	// Set transmit and receive speed
	COM_Parameters.BaudRate = baudrate;

	// Set new parameters
	if (!SetCommState(hSP, &COM_Parameters))
	{
		// ���ò���ʧ��
		return false;
	}

	return true;
}

bool SetSerialPortTimeOut(HANDLE hSP, DWORD rInverval, DWORD rMulti, DWORD rConst, DWORD wMulti, DWORD wConst)
{
	//��ʱ����,��λ������
	COMMTIMEOUTS Timing_Parameters;
	// Make reads non blocking

	Timing_Parameters.ReadIntervalTimeout = rInverval;		//�������ʱ
	//���ַ�֮��������ʱ��
	//����ȡ��������ʱ��ʱ�����ڴӵ�һ���ַ����յ�����,һ�������ַ������ʱ������ʱ�䣬
	//ReadFile������ϲ��������л������ݡ�
	//����Ϊ0��ʾ�ò����������á� 
	//���ֵΪMAXDWORD, ����ReadTotalTimeoutConstant��ReadTotalTimeoutMultiplier����ֵ��Ϊ0, 
	//��ָ��������Я���Ѿ��յ����ַ��������أ���ʹû���յ��κ��ַ���


	//�ܳ�ʱ��ʱ��ϵ��������д���ַ�����ʱ�䳣��
	Timing_Parameters.ReadTotalTimeoutMultiplier = rMulti;	//��ʱ��ϵ��
	Timing_Parameters.ReadTotalTimeoutConstant = rConst;	//��ʱ�䳣��


	Timing_Parameters.WriteTotalTimeoutMultiplier = wMulti;	// дʱ��ϵ��
	Timing_Parameters.WriteTotalTimeoutConstant = wConst;	//дʱ�䳣��
	return SetCommTimeouts(hSP, &Timing_Parameters);
}

bool SetSerialPortBufferSize(HANDLE hSP, DWORD inSize, DWORD outSize)
{
	return SetupComm(hSP, inSize, outSize);
}

bool ClearSerialPortBuffer(HANDLE hSP)
{
	return PurgeComm(hSP, PURGE_TXCLEAR | PURGE_RXCLEAR);//��մ��ڻ�����
}

bool CloseSerialPort(HANDLE hSP)
{
	return CloseHandle(hSP);
}

int  SendSerialPortSync(HANDLE hSP, const BYTE* buffer, int len)
{
	// ͬ����ʽ
	DWORD dwBytesWrite = len; //�ɹ�д��������ֽ���
	BOOL bWriteStat = WriteFile(hSP, //���ھ��
		buffer, //�����׵�ַ
		dwBytesWrite, //Ҫ���͵������ֽ���
		&dwBytesWrite, //DWORD*���������շ��سɹ����͵������ֽ���
		NULL); //NULLΪͬ������

	if (!bWriteStat) return 0;

	return dwBytesWrite;
}

int  SendSerialPortAsync(HANDLE hSP, const BYTE* buffer, int len)
{
	//�첽��ʽ
	DWORD dwBytesWrite = len;		//�ɹ�д��������ֽ���
	DWORD dwErrorFlags;				//�����־
	COMSTAT comStat;				//ͨѶ״̬
	OVERLAPPED m_osWrite;			//�첽��������ṹ��

	//����һ������OVERLAPPED���¼��������������õ�����ϵͳҪ����ô��
	memset(&m_osWrite, 0, sizeof(m_osWrite));
	m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("WriteEvent"));

	ClearCommError(hSP, &dwErrorFlags, &comStat); //���ͨѶ���󣬻���豸��ǰ״̬
	BOOL bWriteStat = WriteFile(hSP,	//���ھ��
		buffer,							//�����׵�ַ
		dwBytesWrite,					//Ҫ���͵������ֽ���
		&dwBytesWrite,					//DWORD*���������շ��سɹ����͵������ֽ���
		&m_osWrite);					//��OVERLAPPED*Ϊ�첽����
	if (!bWriteStat)
	{
		if (GetLastError() == ERROR_IO_PENDING) //�����������д��
		{
			WaitForSingleObject(m_osWrite.hEvent, 1000); //�ȴ�д���¼�1����
		}
		else
		{
			ClearCommError(hSP, &dwErrorFlags, &comStat); //���ͨѶ����
			CloseHandle(m_osWrite.hEvent); //�رղ��ͷ�hEvent�ڴ�
			return 0;
		}
	}
	return dwBytesWrite;
}

int  ReceiveSerialPortSync(HANDLE hSP, BYTE* buffer, int maxLen)
{
	//ͬ����ʽ
	DWORD wCount = maxLen; //�ɹ���ȡ�������ֽ���
	BOOL bReadStat = ReadFile(hSP,	//���ھ��
		buffer,						//�����׵�ַ
		wCount,						//Ҫ��ȡ����������ֽ���
		&wCount,					//DWORD*,�������շ��سɹ���ȡ�������ֽ���
		NULL);						//NULLΪͬ������
	if (!bReadStat) return 0;

	return wCount;
}

int  ReceiveSerialPortAsync(HANDLE hSP, BYTE* buffer, int maxLen)
{
	//�첽��ʽ
	DWORD wCount = maxLen; //�ɹ���ȡ�������ֽ���
	DWORD dwErrorFlags; //�����־
	COMSTAT comStat; //ͨѶ״̬
	OVERLAPPED m_osRead; //�첽��������ṹ��

	//����һ������OVERLAPPED���¼��������������õ�����ϵͳҪ����ô��
	memset(&m_osRead, 0, sizeof(m_osRead));
	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("ReadEvent"));

	ClearCommError(hSP, &dwErrorFlags, &comStat); //���ͨѶ���󣬻���豸��ǰ״̬
	if (!comStat.cbInQue)return 0; //������뻺�����ֽ���Ϊ0���򷵻�false

	BOOL bReadStat = ReadFile(hSP,	//���ھ��
		buffer,						//�����׵�ַ
		wCount,						//Ҫ��ȡ����������ֽ���
		&wCount,					//DWORD*,�������շ��سɹ���ȡ�������ֽ���
		&m_osRead);					//OVERLAPPED*Ϊ�첽����
	if (!bReadStat)
	{
		if (GetLastError() == ERROR_IO_PENDING) //����������ڶ�ȡ��
		{
			//GetOverlappedResult���������һ��������ΪTRUE
			//������һֱ�ȴ���ֱ����������ɻ����ڴ��������
			GetOverlappedResult(hSP, &m_osRead, &wCount, TRUE);
		}
		else
		{
			ClearCommError(hSP, &dwErrorFlags, &comStat); //���ͨѶ����
			CloseHandle(m_osRead.hEvent); //�رղ��ͷ�hEvent���ڴ�
			return 0;
		}
	}
	return wCount;
}