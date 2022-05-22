#include "memory.h"
#include "data.h"

//NTSTATUS KeReadVirtualMemory(PEPROCESS Process, DWORD32 SourceAdress, DWORD64 TargetAdress, SIZE_T Size, PSIZE_T ReadedBytes)
//{
//	//DbgPrintEx(0, 0, "kernel reading... %d", (int)SourceAdress); PsGetCurrentProcess() = CheatProcess
//	return MmCopyVirtualMemory(Process, (PVOID)SourceAdress, CheatProcess, (PVOID)TargetAdress, Size, KernelMode, ReadedBytes); 
//}
//
//NTSTATUS KWriteVirtualMemory(PEPROCESS Process, DWORD32 SourceAdress, DWORD64 TargetAdress, SIZE_T Size, PSIZE_T WritedBytes)
//{
//	//DbgPrintEx(0, 0, "kernel writing... %d", (int)(PVOID)SourceAdress);
//	return MmCopyVirtualMemory(CheatProcess, (PVOID)TargetAdress, Process, (PVOID)SourceAdress, Size, KernelMode, WritedBytes);
//	//return MmCopyVirtualMemory(PsGetCurrentProcess(), (PVOID)SourceAdress, Process, (PVOID)TargetAdress, Size, KernelMode, WritedBytes);
//	//MmCopyVirtualMemory(с какого процесса, какой адресс, в какой процесс, какого адреса, sizeof(тип), KernelMode, указатель размера);
//}


NTSTATUS KeReadVirtualMemory(PEPROCESS Process, DWORD64 SourceAdress, DWORD64 TargetAdress, SIZE_T Size, PSIZE_T ReadedBytes)
{
	//DbgPrintEx(0, 0, "kernel reading... %d", (int)SourceAdress); PsGetCurrentProcess() = CheatProcess
	return MmCopyVirtualMemory(Process, (PVOID)SourceAdress, CheatProcess, (PVOID)TargetAdress, Size, KernelMode, ReadedBytes);
}

NTSTATUS KWriteVirtualMemory(PEPROCESS Process, DWORD64 SourceAdress, DWORD64 TargetAdress, SIZE_T Size, PSIZE_T WritedBytes)
{
	//DbgPrintEx(0, 0, "kernel writing... %d", (int)(PVOID)SourceAdress);
	return MmCopyVirtualMemory(CheatProcess, (PVOID)TargetAdress, Process, (PVOID)SourceAdress, Size, KernelMode, WritedBytes);
	//return MmCopyVirtualMemory(PsGetCurrentProcess(), (PVOID)SourceAdress, Process, (PVOID)TargetAdress, Size, KernelMode, WritedBytes);
	//MmCopyVirtualMemory(с какого процесса, какой адресс, в какой процесс, какого адреса, sizeof(тип), KernelMode, указатель размера);
}