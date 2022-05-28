#include "events.h"
#include "messages.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallBack(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	//DebugMessage("ImageLoaded: %ls \n", (*FullImageName).Buffer);
	//if (wcsstr((*FullImageName).Buffer, L"\\SteamLibrary\\steamapps\\common\\Counter-Strike Global Offensive\\csgo\\bin\\client.dll"))
	//L"\\SteamLibrary\\steamapps\\common\\Apex Legends\\r5apex.exe"
	//Path

		//if (wcsstr((*FullImageName).Buffer, L"\\SteamLibrary\\steamapps\\common\\Apex Legends\\r5apex.exe"))
		if (wcsstr((*FullImageName).Buffer, L"\\DayZ_x64.exe")) //\Steam\\steamapps\\common\\DayZ
		{
			DbgPrintEx(0, 0, "Process found!");

			ProcId = ProcessId;
			BaseAdress = (DWORD64)ImageInfo->ImageBase;
		}
		//if (strlen(Path) != 0 || Path != NULL)
		//{}

	return STATUS_SUCCESS;
}
