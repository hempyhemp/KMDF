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


	bool ReadRaw(UINT_PTR readAddress, UINT_PTR targetAddress, ULONG size)
	{
		_KERNEL_READ_REQUEST req;

		req.Size = size;
		req.Adress = readAddress;
		req.Response = targetAddress; //uint64_t
		req.Result = -1;

		DeviceIoControl(hDriver, IO_READ_PROCESS_MEMORY, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
		return true;
	}

	template<class type>
	type rpm(UINT_PTR readAddress)
	{
		// use the ReadRaw function we defined earlier
		type tmp;
		if (ReadRaw(readAddress, (UINT_PTR)&tmp, sizeof(type)))
			return tmp;
		else
			return { 0 };
	}

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
		req.Response = (DWORD64)result; //uint64_t
		req.Result = -1;

		DeviceIoControl(hDriver, IO_READ_PROCESS_MEMORY, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
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
	}

	std::string ReadString(uintptr_t address)
	{
		// creating a buffer and copying memory to it
		char buf[100] = { 0 };
		ReadRaw(address, (UINT_PTR)&buf, 100);
		return buf;
	}
};
