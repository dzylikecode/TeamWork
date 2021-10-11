#pragma once

#include <windows.h>



HANDLE SerialPortOpenSync(const char* String_Device_File_Name);
HANDLE SerialPortOpenAsync(const char* String_Device_File_Name);

bool SetSerialPortState(HANDLE hSP, unsigned int baudrate, char parity, char databit, char stopbit);

bool SetSerialPortTimeOut(HANDLE hSP, DWORD rInverval = MAXDWORD, DWORD rMulti = 0, DWORD rConst = 0, DWORD wMulti = 50, DWORD wConst = 2000);

bool SetSerialPortBufferSize(HANDLE hSP, DWORD inSize, DWORD outSize);

bool ClearSerialPortBuffer(HANDLE hSP);

bool CloseSerialPort(HANDLE hSP);

int  SendSerialPortSync(HANDLE hSP, const BYTE* buffer, int len);
int  SendSerialPortAsync(HANDLE hSP, const BYTE* buffer, int len);

int  ReceiveSerialPortSync(HANDLE hSP, BYTE* buffer, int maxLen);
int  ReceiveSerialPortAsync(HANDLE hSP, BYTE* buffer, int maxLen);