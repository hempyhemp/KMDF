
#include <iostream>
#include "IKernel.hpp"
#include <Windows.h>
#include "offsets.hpp"
#include <cstdint>
#include <string>


//
//uintptr_t SFGetEPROCESS(int dwProcessId)
//{
//    auto pHandleInfo = QueryInfo<SYSTEM_HANDLE_INFORMATION>(SystemHandleInformation);
//    if (pHandleInfo.get())
//    {
//        for (size_t i = 0; i < pHandleInfo->HandleCount; i++)
//        {
//            if (dwProcessId == pHandleInfo->Handles[i].ProcessId && 7 == pHandleInfo->Handles[i].ObjectTypeNumber)
//            {
//                return reinterpret_cast<size_t>(pHandleInfo->Handles[i].Object);
//            }
//        }
//    }
//    return 0;
//}
//
//uintptr_t GetEPROCESS(int dwProcessId, IKernel Driver)
//{
//    _LIST_ENTRY pActiveProcessLinks;
//    Driver.Read(SFGetEPROCESS(4) + Utilities::pActiveProcessLinkOffset, (uint8_t*)&pActiveProcessLinks);
//    
//    if (&pActiveProcessLinks)
//    {
//        while (true)
//        {
//            uint64_t pNextPid = 0;
//            uint64_t pNextLink = (uint64_t)(pActiveProcessLinks.Flink);
//            uint64_t pNext = pNextLink - Utilities::pActiveProcessLinkOffset;
//            if (pNext)
//            {
//                Driver.Read(SFGetEPROCESS(4) + Utilities::pUniqueProcessIdOffset, (uint8_t*)&pNextPid);
//
//                Driver.Read(pNext + Utilities::pActiveProcessLinkOffset, (uint8_t*)&pActiveProcessLinks);
//                if (pNextPid == dwProcessId)
//                {
//                    return pNext;
//                }
//                if (pNextPid == 4 || pNextPid == 0)
//                {
//                    break;
//                }
//            }
//        }
//    }
//    return 0;
//}
//
//uintptr_t GetProcessBaseAddress(uintptr_t dwProcessId, IKernel Driver)
//{
//    //uintptr_t pEPROCESS = GetEPROCESS(dwProcessId, Driver);
//    uintptr_t pEPROCESS = dwProcessId;
//    uintptr_t pBaseAddress = 0;
//    if (pEPROCESS)
//    {
//        Driver.Read(pEPROCESS + Utilities::pSectionBaseOffset, (uint8_t*)&pBaseAddress);
//
//        std::cout << " GetProcessBaseAddress: " << Utilities::pSectionBaseOffset << " + "<< pEPROCESS << " = " << pEPROCESS + Utilities::pSectionBaseOffset << std::endl;
//        return pBaseAddress;
//    }
//    return 0;
//}

int main()
{
    IKernel Driver = IKernel("\\\\.\\zalupka");

    std::cout << "\t---Assalamoaleykum!---\n";
    while(!Driver.Init()){
        std::cout << " initialising...\n";
        Sleep(1000);
    }
    while (!Driver.GetModules()) {
        std::cout << " getting modules...\n";
        Sleep(1000);
    }

    //GetProcessBaseAddress(Driver.Modules->processId, Driver);

    std::cout << " process id: " << Driver.Modules->processId << std::endl;
    std::cout << " game base adress?: "  << Driver.Modules->baseAdress << std::endl; //<< "0x" std::hex << 


    DWORD64 base = 0;
    DWORD32 health = 0;


    //Client "add" offset
    uint64_t add_off = 0x3f870;

    uint64_t g_Base_addr = 0;

    //Driver.Read(Driver.Modules->bClient, &base);

    std::cout << " base: " << base << std::endl;

    //Driver.Read(base , &g_Base_addr);

    //std::cout << " g_Base_addr: " << g_Base_addr << std::endl;

    while (true)
    {
        
        

        //Driver.Read(playerBase + offsets::Classes::CPlayer::m_iHealth, &health);
        //std::cout << "health : " << health << std::endl;

        Sleep(300);
    }

}


