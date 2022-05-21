#include "events.h"
#include "messages.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallBack(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	//DebugMessage("ImageLoaded: %ls \n", (*FullImageName).Buffer);
	//if (wcsstr((*FullImageName).Buffer, L"\\Program Files\\WindowsApps\\F510D05A.ChickenZooma_1.0.0.2017_neutral__0d7vrcwhmw17a\\ZumaGame.exe"))

	if (wcsstr((*FullImageName).Buffer, L"\\SteamLibrary\\steamapps\\common\\Apex Legends\\r5apex.exe"))
	{
		DbgPrintEx(0, 0, "Process found!");

		ProcId = ProcessId;
		ClientBase = (DWORD64)ImageInfo->ImageBase;
	}

	return STATUS_SUCCESS;
}
