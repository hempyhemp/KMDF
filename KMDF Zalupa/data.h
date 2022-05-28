#pragma once
#include <ntdef.h>

PDEVICE_OBJECT pDeviceObject;

UNICODE_STRING dev, dos;

HANDLE ProcId;
PEPROCESS GameProcess;

HANDLE ControllerId;
PEPROCESS ControllerProcess;

wchar_t* Path;

DWORD64 BaseAdress; //dword64 rabotalo