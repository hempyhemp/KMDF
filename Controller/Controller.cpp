
#include <iostream>
#include "IKernel.hpp"
#include <Windows.h>
//#include "offsets.hpp"
#include <cstdint>
//#include <string>
#include "globals.hpp"
#include "offsets2.hpp"

using namespace std;

_globals globals;

std::vector<player_t> entities = {};
std::vector<item_t> items = {};


int main()
{
    IKernel Driver = IKernel("\\\\.\\zalupka");

    cout << "\t---Assalamoaleykum!---\n";


	//wchar_t* path = L"\\SteamLibrary\\steamapps\\common\\Apex Legends\\r5apex.exe";

    while(!Driver.Init()){
        cout << " initialising...\n";
        Sleep(300);
    }

	cout << " process id: " << Driver.Modules->processId << endl;
	cout << " game base adress?: " << Driver.Modules->baseAdress << endl;



	cout << " world: " << Driver.Modules->baseAdress << endl;

	uintptr_t localPlayer = Driver.rpm<uintptr_t>(Driver.Modules->baseAdress + OFFSET_LOCAL_ENT);

	while (true)
	{
		//localPlayer = Driver.rpm<uintptr_t>(Driver.Modules->baseAdress + OFFSET_LOCAL_ENT);

		//int health = Driver.rpm<int>(localPlayer + OFFSET_HEALTH);
		//int s = Driver.rpm<int>(localPlayer + 0x2a34);

		//int helmetType = Driver.rpm<int>(localPlayer + 0x4608); //0x3ff0

		//Driver.Read(Base + OFFSET_AMMO, &World);
		//system("CLS");
		//cout << "Duck State: " << s << endl;
		//cout << "health: " << health << endl;
		//out << "helmet type: " << helmetType << endl;
		//
		Sleep(300);
	}
}


