
#include <iostream>
#include "IKernel.hpp"
#include <Windows.h>
#include "offsets.hpp"
#include <cstdint>
#include <string>

uintptr_t GetLocalPlayer(IKernel Driver)
{
    uintptr_t pointer;
    Driver.Read(Driver.Modules->bClient + offsets::local_player, &pointer);

    return  pointer;
}

//uintptr_t GetEntityBase(DWORD dwEntityIndex, IKernel Driver)
//{
//    uintptr_t pointer;
//    Driver.Read((Driver.Modules->bClient + offsets::cl_entitylist) + (dwEntityIndex << 5), &pointer);
//
//    return  pointer;
//}

//std::string GetPlayerName(int  EntityID, IKernel Driver)
//{
//
//    EntityID--;
//    EntityID *= 0x10;
//    uint64_t name_ptr = 0;
//
//    Driver.Read(Driver.Modules->bClient + offsets::name_list + EntityID, &name_ptr);
//
//    char name[32];
//    Driver.Read(name_ptr, &name);
//
//    return std::string(name);
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

    std::cout << " process id: " << Driver.Modules->processId << std::endl;
    std::cout << " game base adress: "  << Driver.Modules->bClient << std::endl; //<< "0x" std::hex << 

    DWORD64 playerBase;
    float health = 0;

    //int i = 228;
    //Driver.Write(0x009AD1C4, &i);

    //int debbug;
    //Driver.Read(0x009AD1C4, &debbug);
    //std::cout << "debbug: " << debbug << std::endl;

    while (true)
    {
        Driver.Read(Driver.Modules->bClient + offsets::local_player, &playerBase);
        if (!playerBase) continue;
        std::cout << "player base: " << playerBase << std::endl;

        Driver.Read(playerBase + offsets::Classes::CPlayer::m_angEyeAnglesy, &health);
        std::cout << "health offset: " << health << std::endl;

        Sleep(1000);
    }

}


