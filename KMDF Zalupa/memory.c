#include "memory.h"
#include "data.h"

//NTSTATUS KReadVirtualMemory(PEPROCESS Process, PVOID SourceAdress, PVOID TargetAdress, SIZE_T Size)
//{
//	PSIZE_T Bytes;
//
//	return MmCopyVirtualMemory(Process, SourceAdress, PsGetCurrentProcess(), TargetAdress, Size, KernelMode, &Bytes);
//}
//
//NTSTATUS KWriteVirtualMemory(PEPROCESS Process, PVOID SourceAdress, PVOID TargetAdress, SIZE_T Size)
//{
//	PSIZE_T Bytes;
//
//	return MmCopyVirtualMemory(PsGetCurrentProcess(), SourceAdress, Process, TargetAdress, Size, KernelMode, &Bytes);
//}

NTSTATUS KeReadVirtualMemory(PEPROCESS Process, DWORD32 SourceAdress, DWORD64 TargetAdress, SIZE_T Size, PSIZE_T ReadedBytes)
{
	//DbgPrintEx(0, 0, "kernel reading... %d", (int)SourceAdress);
	return MmCopyVirtualMemory(Process, (PVOID)SourceAdress, PsGetCurrentProcess(), (PVOID)TargetAdress, Size, KernelMode, ReadedBytes);
}

NTSTATUS KWriteVirtualMemory(PEPROCESS Process, DWORD32 SourceAdress, DWORD64 TargetAdress, SIZE_T Size, PSIZE_T WritedBytes)
{
	//DbgPrintEx(0, 0, "kernel writing... %d", (int)(PVOID)SourceAdress);
	return MmCopyVirtualMemory(CheatProcess, (PVOID)TargetAdress, Process, (PVOID)SourceAdress, Size, KernelMode, WritedBytes);
	//return MmCopyVirtualMemory(PsGetCurrentProcess(), (PVOID)SourceAdress, Process, (PVOID)TargetAdress, Size, KernelMode, WritedBytes);
	//MmCopyVirtualMemory(с какого процесса, какой адресс, в какой процесс, какого адреса, sizeof(тип), KernelMode, указатель размера);
}


