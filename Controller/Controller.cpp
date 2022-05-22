
#include <iostream>
#include "IKernel.hpp"
#include <Windows.h>
#include "offsets.hpp"
#include <cstdint>
#include <string>
#include "globals.hpp"
#include "offsets2.hpp"


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

void UpdateList(IKernel Driver);

_globals globals;

std::vector<player_t> entities = {};
std::vector<item_t> items = {};

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

    std::cout << " process id: " << Driver.Modules->processId << std::endl;
    std::cout << " game base adress?: "  << Driver.Modules->baseAdress << std::endl; //<< "0x" std::hex << 

	uint64_t Base = Driver.Modules->baseAdress;
    DWORD32 health = 0;
	DWORD32  World = 0;

	uintptr_t localPlayer;

	localPlayer = Driver.rpm<uintptr_t>(Driver.Modules->baseAdress + OFFSET_LOCAL_ENT);

	//UpdateList(Driver);
	while (true)
	{
		localPlayer = Driver.rpm<uintptr_t>(Driver.Modules->baseAdress + OFFSET_LOCAL_ENT);

		int health = Driver.rpm<int>(localPlayer + OFFSET_HEALTH);

		//Driver.Read(Base + OFFSET_AMMO, &World);
		std::cout << "localPlayer: " << localPlayer << std::endl;
		std::cout << "health: " << health << std::endl;
		Sleep(300);
	}
}


void UpdateList(IKernel Driver)
{
	while (true)
	{
		// stores all data
		std::vector<player_t> tmp{};

		uint64_t NearTableSize = 0;
		Driver.Read(globals.World + 0xEA8 + 0x08, &NearTableSize); //<uint32_t>

		uint64_t FarTableSize = 0;
		Driver.Read(globals.World + 0xFF0 + 0x08, &FarTableSize);


		for (int i = 0; i < NearTableSize; i++)
		{
			uint64_t EntityTable = 0;
			Driver.Read(globals.World + 0xEA8, &EntityTable);
			if (!EntityTable) continue;

			uint64_t Entity = 0;
			Driver.Read(EntityTable + (i * 0x8), &Entity);
			if (!Entity) continue;

			// checking if player even networked
			uintptr_t networkId = 0;
			Driver.Read(Entity + 0x634, &networkId);
			if (networkId == 0) continue;

			player_t Player{};
			Player.NetworkID = networkId;
			Player.TableEntry = EntityTable;
			Player.EntityPtr = Entity;

			std::cout << " networkId: " << networkId << std::endl;

			// adds info to the vector
			tmp.push_back(Player);
		}

		for (int i = 0; i < FarTableSize; i++)
		{
			uint64_t EntityTable = 0;
			Driver.Read(globals.World + 0xFF0, &EntityTable);
			if (!EntityTable) continue;

			uint64_t Entity = 0;
			Driver.Read(EntityTable + (i * 0x8), &Entity);
			if (!Entity) continue;

			uintptr_t networkId = 0;
			Driver.Read(Entity + 0x634, &networkId);
			if (networkId == 0) continue;

			player_t Player{};
			Player.NetworkID = networkId;
			Player.TableEntry = EntityTable;
			Player.EntityPtr = Entity;
			tmp.push_back(Player);
		}
		entities = tmp;
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		Sleep(100);
	}
}
