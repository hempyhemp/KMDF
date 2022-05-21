#include "communications.h"
#include "messages.h"
#include "data.h"
#include "memory.h"

//NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
//{
//	NTSTATUS Status = STATUS_UNSUCCESSFUL;
//	ULONG ByteIO = 0;
//
//	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
//
//	ULONG ControlCode = (*stack).Parameters.DeviceIoControl.IoControlCode;
//	SIZE_T rwBytes = 0;
//
//	if (ControlCode == IO_GET_CLIENTADRESS)
//	{
//		PULONG OutPut = (PULONG)(*Irp).AssociatedIrp.SystemBuffer;
//
//		*OutPut = GameAdress;
//
//		DebugMessage("GameAdress requested\n");
//
//		Status = STATUS_SUCCESS;
//		ByteIO = sizeof(*OutPut);
//	}
//	else if (ControlCode == IO_REQUEST_PROCESSID)
//	{
//		PULONG OutPut = (PULONG)(*Irp).AssociatedIrp.SystemBuffer;
//
//		*OutPut = ProcessID;
//
//		DebugMessage("ProcessId sended\n");
//
//		Status = STATUS_SUCCESS;
//		ByteIO = sizeof(*OutPut);
//	}
//	else if(ControlCode == IO_READ_REQUEST)
//	{
//		PKERNEL_READ_REQUEST ReadInput = (PKERNEL_READ_REQUEST)(*Irp).AssociatedIrp.SystemBuffer;
//		PEPROCESS Process;
//
//		if (NT_SUCCESS(PsLookupProcessByProcessId((*ReadInput).ProcessId, &Process)))
//		{
//			KReadVirtualMemory(Process, (*ReadInput).Adress, (*ReadInput).pBuff, (*ReadInput).Size, &rwBytes);
//			Status = STATUS_SUCCESS;
//			ByteIO = sizeof(KERNEL_READ_REQUEST);
//		}
//	}
//	else if(ControlCode == IO_WRITE_REQUEST)
//	{
//		PKERNEL_WRITE_REQUEST WriteInput = (PKERNEL_WRITE_REQUEST)(*Irp).AssociatedIrp.SystemBuffer;
//		PEPROCESS Process;
//
//		if (NT_SUCCESS(PsLookupProcessByProcessId((*WriteInput).ProcessId, &Process)))
//		{
//			KWriteVirtualMemory(Process, (*WriteInput).pBuff, (*WriteInput).Adress, (*WriteInput).Size, &rwBytes);
//			Status = STATUS_SUCCESS;
//			ByteIO = sizeof(KERNEL_READ_REQUEST);
//		}
//	}
//	else
//	{
//		ByteIO = 0;
//	}
//
//	(*Irp).IoStatus.Status = Status;
//	(*Irp).IoStatus.Information = ByteIO;
//
//	IoCompleteRequest(Irp, IO_NO_INCREMENT);
//
//	return Status;
//}


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
	PKERNEL_INIT_DATA_REQUEST pInitData = (PKERNEL_INIT_DATA_REQUEST)Irp->AssociatedIrp.SystemBuffer;

	if (pInitData)
	{
		//ProcId = (HANDLE)pInitData->gameId;
		pInitData->gameId = ProcId;
		CheatId = (HANDLE)pInitData->cheatId;

		pInitData->Result = PsLookupProcessByProcessId(ProcId, &GameProcess);

		pInitData->Result |= PsLookupProcessByProcessId(CheatId, &CheatProcess);
	}
}

void GetAllModules(PIRP Irp)
{
	PKERNEL_GET_MODULES_REQUEST pModules = (PKERNEL_GET_MODULES_REQUEST)Irp->AssociatedIrp.SystemBuffer;

	if (pModules)
	{
		if (BaseAdress == 0)
		{
			pModules->result = STATUS_NOT_FOUND;
		}
		else
		{
			pModules->baseAdress = BaseAdress;
			pModules->result = STATUS_SUCCESS;
		}
	}
}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	ULONG bytesIo = 0;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	const ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	PKERNEL_WRITE_REQUEST2 pWriteRequest;
	PKERNEL_READ_REQUEST2 pReadRequest;
	SIZE_T rwBytes = 0;

	switch (ControlCode)
	{
	case IO_INIT_DATA:
		InitData(Irp);
		bytesIo = sizeof(_KERNEL_INIT_DATA_REQUEST);
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

	case IO_GET_MODULES:
		GetAllModules(Irp);
		bytesIo = sizeof(_KERNEL_GET_MODULES_REQUEST);
		break;

	default:
		break;
	}

	(*Irp).IoStatus.Status = STATUS_SUCCESS;
	(*Irp).IoStatus.Information = bytesIo;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}