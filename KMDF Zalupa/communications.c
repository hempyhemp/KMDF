#include "communications.h"
#include "messages.h"
#include "data.h"
#include "memory.h"


NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	(*Irp).IoStatus.Status = STATUS_SUCCESS;
	(*Irp).IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("CloseCall was called, Terminated\n");

	return STATUS_SUCCESS;
}

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	(*Irp).IoStatus.Status = STATUS_SUCCESS;
	(*Irp).IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("CreateCall was called, connected\n");

	return STATUS_SUCCESS;
}

void InitData(PIRP Irp)
{
	PKERNEL_PROCESS_DATA_REQUEST pInitData = (PKERNEL_PROCESS_DATA_REQUEST)Irp->AssociatedIrp.SystemBuffer;

	if (pInitData)
	{
		//ProcId = (HANDLE)pInitData->gameId;
		pInitData->procId = ProcId;

		ControllerId = (HANDLE)pInitData->controllerId;

		PsLookupProcessByProcessId(ProcId, &GameProcess);
		PsLookupProcessByProcessId(ControllerId, &ControllerProcess);
		pInitData->baseAdress = BaseAdress;
	}
}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	ULONG bytesIo = 0;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	const ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	PKERNEL_WRITE_REQUEST2 pWriteRequest;
	PKERNEL_READ_REQUEST2 pReadRequest;
	PKERNEL_INIT_REQUEST pInitRequest;

	SIZE_T rwBytes = 0;

	switch (ControlCode)
	{
	case IO_INIT_DATA:
		DbgPrintEx(0, 0, "IO_INIT_DATA code");
		InitData(Irp);
		bytesIo = sizeof(_KERNEL_PROCESS_DATA_REQUEST);
		break;

	case IO_READ_PROCESS_MEMORY:
		pReadRequest = (PKERNEL_READ_REQUEST2)Irp->AssociatedIrp.SystemBuffer;
	
		if (pReadRequest)
		{
			pReadRequest->Result = KeReadVirtualMemory(GameProcess, pReadRequest->Adress, pReadRequest->Response, pReadRequest->Size, &rwBytes);
		}
		bytesIo = sizeof(_KERNEL_READ_REQUEST);
		break;

	case IO_WRITE_PROCESS_MEMORY:
		pWriteRequest = (PKERNEL_WRITE_REQUEST2)Irp->AssociatedIrp.SystemBuffer;
		if (pWriteRequest)
		{
			pWriteRequest->Result = KWriteVirtualMemory(GameProcess, pWriteRequest->Adress, pWriteRequest->Value, pWriteRequest->Size, &rwBytes);
		}
		bytesIo = sizeof(_KERNEL_WRITE_REQUEST);
		break;

	case IO_INIT_PATH:
		pInitRequest = (PKERNEL_INIT_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		if (pInitRequest)
		{
			Path = pInitRequest->path;
		}
		bytesIo = sizeof(PKERNEL_INIT_REQUEST);
		break;

	default:
		break;
	}

	(*Irp).IoStatus.Status = STATUS_SUCCESS;
	(*Irp).IoStatus.Information = bytesIo;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}