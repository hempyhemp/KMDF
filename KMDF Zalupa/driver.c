//#pragma warning (disable : 6011)

#include "driver.h"
#include "messages.h"
#include "events.h"
#include "data.h"
#include "communications.h"
#include "memory.h"

//HANDLE Process = (HANDLE)0x2130;
//DWORD64 Addr = 0x010AED20;
//DWORD32 TestVal = 0;


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pathString)
{
    UNREFERENCED_PARAMETER(pathString);

    (*pDriverObject).DriverUnload = UnloadDriver;

    DebugMessage("Salamoaleykum");

    PsSetLoadImageNotifyRoutine(ImageLoadCallBack);

    RtlInitUnicodeString(&dev, L"\\Device\\zalupka");
    RtlInitUnicodeString(&dos, L"\\DosDevices\\zalupka");

    if (NT_SUCCESS(IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject)))
    {
        IoCreateSymbolicLink(&dos, &dev);
        DbgPrintEx(0, 0, "Device created...");

        (*pDriverObject).MajorFunction[IRP_MJ_CREATE] = CreateCall;
        (*pDriverObject).MajorFunction[IRP_MJ_CLOSE] = CloseCall;
        (*pDriverObject).MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

        (*pDeviceObject).Flags |= DO_DIRECT_IO;
        (*pDeviceObject).Flags &= ~DO_DEVICE_INITIALIZING;
    }
    //PEPROCESS pProcess;
    //SIZE_T size = 0;

    //if (NT_SUCCESS(PsLookupProcessByProcessId(Process, &pProcess)))
    //{
    //    MmCopyVirtualMemory(pProcess, (PVOID)Addr, PsGetCurrentProcess(), &TestVal, sizeof(DWORD32), KernelMode, &size);
    //    DbgPrintEx(0, 0, "readed value: %d", TestVal);

    //    TestVal = 1337;

    //    MmCopyVirtualMemory(PsGetCurrentProcess(), &TestVal, pProcess, (PVOID)Addr, sizeof(DWORD32), KernelMode, &size);
    //    DbgPrintEx(0, 0, "writed value: %d", TestVal);
    //}


    return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
    DebugMessage("Bye!");

    PsRemoveLoadImageNotifyRoutine(ImageLoadCallBack);

    IoDeleteSymbolicLink(&dos);
    IoDeleteDevice((*pDriverObject).DeviceObject);
    
    return STATUS_SUCCESS;
}