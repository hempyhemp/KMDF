#pragma once

#include "ntifs.h"

NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	PVOID SourceAdress,
	PEPROCESS TargetProcess,
	PVOID TargetAdress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);


NTSTATUS KWriteVirtualMemory(PEPROCESS Process, DWORD32 SourceAdress, DWORD64 TargetAdress, SIZE_T Size, PSIZE_T WritedBytes);

NTSTATUS KeReadVirtualMemory(PEPROCESS Process, DWORD32 SourceAdress, DWORD64 TargetAdress, SIZE_T Size, PSIZE_T ReadedBytes);