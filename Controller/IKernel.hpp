#pragma warning( disable : 6001)
#include "communication.hpp"
#include <iostream>
#include <Windows.h>
#include <SubAuth.h>
#include <TlHelp32.h>
#include <comdef.h>

struct GameModules
{
	DWORD64 baseAdress; //DWORD64 rabotalo
	DWORD32 processId;
};

class IKernel
{
public:
	IKernel(LPCSTR RegistryPath);
	~IKernel();

	BOOLEAN GetModules();
	BOOLEAN Init();

	GameModules* Modules;

	HANDLE hDriver;
	DWORD32 dwProcessId;
	HANDLE hProcess;

	template<typename T>
	_inline void Read(uint64_t adress, T* result)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
		{
			std::cout << "Invalid read handle" << std::endl;
			return;
		}

		_KERNEL_READ_REQUEST req;

		req.Size = sizeof(T);
		req.Adress = static_cast<uint32_t>(adress);
		req.Response = (uint64_t)result;
		req.Result = -1;

		DeviceIoControl(hDriver, IO_READ_PROCESS_MEMORY, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);

		//std::cout << "---read started---" << std::endl;

		//std::cout << "size = " << req.Size << std::endl;
		//std::cout << "Adress = 0x" << req.Adress << std::endl;
		//std::cout << "response = " << req.Response << std::endl;
		//std::cout << "result = " << req.Result << std::endl;

		//std::cout << "---read ended---" << std::endl << std::endl;
	}

	template<typename T>
	_inline void Write(uint64_t adress, T* value)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
		{
			std::cout << "Invalid write handle" << std::endl;
			return;
		}

		_KERNEL_WRITE_REQUEST req;

		req.Size = sizeof(T);
		req.Adress = static_cast<uint32_t>(adress);
		req.Value = (DWORD64)value;
		req.Result = -1;

		DeviceIoControl(hDriver, IO_WRITE_PROCESS_MEMORY, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);

		//std::cout << "---write started---" << std::endl;

		//std::cout << "size = " << req.Size << std::endl;
		//std::cout << "Adress = 0x" << req.Adress << std::endl;
		//std::cout << "value = " << req.Value << std::endl;
		//std::cout << "result = " << req.Result << std::endl;

		//std::cout << "---write ended---" << std::endl << std::endl;
	}
};

//class IKernel
//{
//public:
//	HANDLE hDriver;
//
//	IKernel(LPCSTR RegistryPath)
//	{
//		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
//	}
//
//	DWORD64 GetAdress()
//	{
//		if (hDriver == INVALID_HANDLE_VALUE)
//		{
//			std::cout << "\t!get adress: invalid handle" << std::endl;
//			return 0;
//		}
//
//		DWORD64 Adress;
//
//		DWORD Bytes;
//
//		if (DeviceIoControl(hDriver, IO_GET_CLIENTADRESS, &Adress, sizeof(Adress), &Adress, sizeof(Adress), &Bytes, NULL))
//		{
//			return Adress;
//		}
//
//		return 0;
//	}
//
//	ULONG GetProcessId()
//	{
//		if (hDriver == INVALID_HANDLE_VALUE)
//		{
//			return 0;
//		}
//
//		ULONG ProcessID = 0;
//
//		ULONG Bytes;
//
//		if (DeviceIoControl(hDriver, IO_REQUEST_PROCESSID, &ProcessID, sizeof(ProcessID), &ProcessID, sizeof(ProcessID), &Bytes, NULL))
//		{
//			return ProcessID;
//		}
//
//		return 0;
//	}
//
//	template <typename type>
//	type ReadVirutalMemory(ULONG ProcessId, DWORD64 ReadAdress) //, SIZE_T Size
//	{
//		type Buffer;
//
//		//if (hDriver == INVALID_HANDLE_VALUE)
//		//{
//		//	return Buffer;
//		//}
//
//		KERNEL_READ_REQUEST ReadRequest;
//
//		ReadRequest.ProcessId = ProcessId;
//		ReadRequest.Adress = ReadAdress;
//		ReadRequest.pBuff = &Buffer;
//		ReadRequest.Size = sizeof(type);
//
//		//std::cout << "read request: "
//		//	<< ReadRequest.ProcessId
//		//	<< " "
//		//	<< ReadRequest.Adress
//		//	<< " "
//		//	<< ReadRequest.pBuff
//		//	<< " "
//		//	<< ReadRequest.Size
//		//	<< " "
//		//	<< std::endl;
//
//		if (DeviceIoControl(hDriver, IO_READ_REQUEST, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0))
//		{
//			return Buffer;
//		}
//
//
//		return Buffer;
//	}
//
//	template <typename type>
//	bool WriteVirtualMemory(ULONG ProcessId, DWORD64 WriteAdress, type WriteValue) //, SIZE_T Size
//	{
//		if (hDriver == INVALID_HANDLE_VALUE)
//		{
//			return false;
//		}
//
//		DWORD Bytes;
//
//		KERNEL_WRITE_REQUEST WriteRequest;
//
//		WriteRequest.ProcessId = ProcessId;
//		WriteRequest.Adress = WriteAdress;
//		WriteRequest.pBuff = &WriteValue;
//		WriteRequest.Size = sizeof(type);
//
//		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, &WriteRequest, sizeof(WriteRequest), 0, 0, &Bytes, NULL))
//		{
//			return true;
//		}
//
//		return false;
//	}
//};


