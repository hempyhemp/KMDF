#pragma once
#include <ntdef.h>

PDEVICE_OBJECT pDeviceObject;

UNICODE_STRING dev, dos;

HANDLE ProcId;
PEPROCESS GameProcess;

HANDLE CheatId;
PEPROCESS CheatProcess;

DWORD64 ClientBase;