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

BOOLEAN IKernel::GetModules()
{
	if (hDriver == INVALID_HANDLE_VALUE)
		return false;

	_KERNEL_GET_MODULES_REQUEST req{ 0, -1 };

	BOOL result = DeviceIoControl(hDriver, IO_GET_MODULES, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);

	if (!result) return false;

	if (!NT_SUCCESS(req.result)) return false;

	Modules->bClient = req.bCLIENT;

	return true;
}

BOOLEAN IKernel::Init()
{
	_KERNEL_INIT_DATA_REQUEST req{0, GetCurrentProcessId(), -1};
	DeviceIoControl(hDriver, IO_INIT_DATA, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);

	Modules->processId = req.gameId;
	return true;
}

IKernel::~IKernel()
{
	CloseHandle(hDriver);
	CloseHandle(hProcess);
	delete Modules;
}