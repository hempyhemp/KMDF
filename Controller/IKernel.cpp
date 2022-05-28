#include "IKernel.hpp"

IKernel::IKernel(LPCSTR RegistryPath)
{
	hDriver = CreateFileA(RegistryPath,
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		0, OPEN_EXISTING, 0, 0);

	dwProcessId = 0;
	hProcess = INVALID_HANDLE_VALUE;

	Modules = new GameModules();
}


BOOLEAN IKernel::Init()
{
	_KERNEL_PROCESS_DATA_REQUEST req{0, GetCurrentProcessId(), 0, -1};
	DeviceIoControl(hDriver, IO_INIT_DATA, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);

	Modules->processId = req.gameId;
	Modules->baseAdress = req.baseAdress;

	if (!req.gameId) return false;
	return true;
}

void IKernel::SendPath(wchar_t path)
{
	_KERNEL_INIT_REQUEST req{ path };

	DeviceIoControl(hDriver, IO_INIT_PATH, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
}

IKernel::~IKernel()
{
	CloseHandle(hDriver);
	CloseHandle(hProcess);
	delete Modules;
}