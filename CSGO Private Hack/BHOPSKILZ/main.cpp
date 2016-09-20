#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <random>
#include <thread>
#include <string>
#include <math.h>


// Cryptic CSGO CHEAT MADE BY LOLS MAKE SURE TO GIVE A THANK IN THE OFFICIAL POST! 

using namespace std;
int ConsolePos_x = 5;
int ConsolePos_y = 5;


#include "MManager.h"

#define Pressed 0x8000

bool eON = false; 
bool bON = false; 
bool nfON = false;
bool hON = false;
bool fON = false;
bool flON = false;
bool tON = false;


Memory MManager;
Module Client;
Module Engine;

int FOVInput = 90;
int MyTeam;
int tTeam;
int InCross;
int triggerdelay = 7;

const DWORD LocalPlayer = 0x00A3A43C; 
const DWORD EnginePointer = 0x005BB2C4; 
const DWORD EntityList = 0x04A57EA4; 
const DWORD GlowObject = 0x04F6DAD4; 
const DWORD ForceJump = 0x04EED318; 
const DWORD m_flFlashDuration = 0x0000A2F8; 
const DWORD m_szArmsModel = 0x38E3; 
const DWORD m_dwClientState = 0x005BB2C4; 
const DWORD m_iFov = 0x31C8; 
const DWORD m_iItemDefinitionIndex = 0x2F88; 
const DWORD activeweapon = 0x00002EE8; 
const DWORD m_bIsScoped = 0x388C; 
const DWORD m_zoomlevel = 0x3340; 
const DWORD m_iTeamNum = 0xF0; 
const DWORD m_iCrossHairID = 0xAA54; 
const DWORD attack = 0x02E97EC4; 

DWORD WepIndex;
DWORD LocalBase;
DWORD Wepentitiy;
DWORD WepHandle;
DWORD IsScoped;
DWORD zoom;
DWORD tEntity;





void ActivationByHotkeys()
{
	
	for (;;)
	{
		
		if (GetAsyncKeyState(VK_F5) & Pressed)
		{
			
			while (GetAsyncKeyState(VK_F5) & Pressed)
			{
				Sleep(50);
			}
			
			bON = !bON;

			if (bON) 
			{
				cout << "|     BHOP is now ON        |" << endl;
			}
			else 
			{
				cout << "--->   BHOP is now OFF   <---" << endl;
			}
		}

		if (GetAsyncKeyState(VK_F2) & Pressed)
		{

			while (GetAsyncKeyState(VK_F2) & Pressed)
			{
				Sleep(50);
			}

			flON = !flON;

			if (flON)
			{
				cout << "FakeLag is now ON" << endl;
			}
			else
			{
				cout << "FakeLag is now OFF" << endl;
			}
		}

		if (GetAsyncKeyState(VK_INSERT) & Pressed)
		{
			cout << "Enter Trigger Delay (ms): ";
			cin >> triggerdelay;
			Sleep(100);
		}

		if (GetAsyncKeyState(VK_F3) & Pressed)
		{

			while (GetAsyncKeyState(VK_F3) & Pressed)
			{
				Sleep(50);
			}

			tON = !tON;

			if (tON)
			{
				cout << "|     Triggerbot is now ON        |" << endl;
			}
			else
			{
				cout << "--->   Triggerbot is now OFF   <---" << endl;
			}
		}

		if (GetAsyncKeyState(VK_F8) & Pressed)
		{

			while (GetAsyncKeyState(VK_F8) & Pressed)
			{
				Sleep(50);
			}

			hON = !hON;

			if (hON)
			{
				cout << "|     NOHANDS is now ON      |" << endl;
			}
			else
			{
				cout << "-->   NOHANDS is now OFF <---" << endl;
			}
		}

		if (GetAsyncKeyState(VK_F6) & Pressed)
		{

			while (GetAsyncKeyState(VK_F6) & Pressed)
			{
				Sleep(50);
			}

			nfON = !nfON;

			if (nfON)
			{
				cout << "|    NOFLASH is now ON      |" << endl;
			}
			else
			{
				cout << "--->   NOFLASH is now OFF    <---" << endl;
			}
		}

		if (GetAsyncKeyState(VK_F9) & Pressed)
		{

			while (GetAsyncKeyState(VK_F9) & Pressed)
			{
				Sleep(50);
			}

			fON = !fON;

			if (fON)
			{
				cout << "|     FOV is now ON      |" << endl;
			}
			else
			{
				cout << "--->   FOV is now OFF    <---" << endl;
			}
		}

		if (GetAsyncKeyState(VK_HOME) & Pressed)
		{
			cout << "Enter FOV: ";
			cin >> FOVInput;
		}

		if (GetAsyncKeyState(VK_F4) & Pressed)
		{
			
			while (GetAsyncKeyState(VK_F4) & Pressed)
			{
				Sleep(50);
			}
			
			eON = !eON;
		
			if (eON)
			{
				cout << "|      ESP is now ON        |" << endl;
			}
			else
			{
				cout << "--->    ESP is now OFF   <---" << endl;
			}
		}

		if (GetAsyncKeyState(VK_F7) & Pressed)
		{
			cout << "|                           |" << endl;
			cout << "|   Bye                     |" << endl;
			cout << "-----------------------------" << endl;
			Sleep(100);
			exit(0);
		}
		
		Sleep(1);
	}
}

//Nohands


void HANDS()
{
	for (;;)
	{
		DWORD Localxd = MManager.Read<DWORD>(Client.dwBase + LocalPlayer);
		MManager.Write(Localx + m_szArmsModel, 0);

		if (hON && GetAsyncKeyState(VK_INSERT) != 0) 
		{
			DWORD ClientState = MManager.Read<DWORDDDS>(Engine.dwBase + m_dwClientState);
			MManager.Write(ClientState + 0x16C, -1);
		}
		Sleep(25);
	}

}


//Triggerbot

void Trigger()
{
	while (true)
	{
		MyTeam = MManager.Read<int>(LocalBase + m_iTeamNum);
		tTeam = MManager.Read<int>(tEntity + m_iTeamNum);
		tEntity = MManager.Read<DWORD>(Client.dwBase + EntityList + ((InCross - 1) * 16));
		InCross = MManager.Read<int>(LocalBase + m_iCrossHairID);

		if (tON)
		{
			if (MyTeam != tTeam && tTeam > 1 && GetAsyncKeyState(VK_LSHIFT) && InCross > 0 && InCross < 64)
			{
				//Weapon Check
				if ((WepIndex != 42) && (WepIndex != 43) && (WepIndex != 44) && (WepIndex != 45) && (WepIndex != 46) && (WepIndex != 47) && (WepIndex != 59))
				{
					Sleep(triggerdelay);
					MManager.Write(Client.dwBase + attack, 1);
					Sleep(1);
					MManager.Write(Client.dwBase + attack, 0);
				}
			}
		}
		Sleep(25);
	}
}

// FOV

void FOV()
{
	while (true)
	{
		IsScoped = MManager.Read<bool>(LocalBase + m_bIsScoped);
		zoom = MManager.Read<int>(Wepentitiy + m_zoomlevel);
		WepHandle = MManager.Read<DWORD>(LocalBase + activeweapon);
		Wepentitiy = MManager.Read<DWORD>(Client.dwBase + EntityList + ((WepHandle & 0xFFF) - 1) * 0x10);
		LocalBase = MManager.Read<DWORD>(Client.dwBase + LocalPlayer);
		WepIndex = MManager.Read<int>(Wepentitiy + m_iItemDefinitionIndex);

		if (fON)
		{
			if (GetAsyncKeyState(VK_F10) & Pressed && (WepIndex != 41) && (WepIndex != 59) && (WepIndex != 42))
			{
				MManager.Write<int>(LocalBase + m_iFov, 50);

			}
			//FOV
			else if ((zoom == 2) && (IsScoped == 1))
				MManager.Write(LocalBase + m_iFov, 10);
			else if ((zoom == 1) && (IsScoped == 1))
				MManager.Write(LocalBase + m_iFov, 40);
			else
				MManager.Write(LocalBase + m_iFov, FOVInput);

		}

		Sleep(25);
	}
}
	


//Noflash

void FLASH()
{
	while (true)
	{

		DWORD Localxdd = MManager.Read<DWORD>(Client.dwBase + LocalPlayer);

		if (nfON && m_flFlashDuration > 0.f)

			MManager.Write(Localxdd + m_flFlashDuration, 0.f);

		Sleep(1);
	}
}

// ESP

void ESP()
{

	for (;;)
	{
		if (eON)
		{
	
			DWORD Engine_dwBase = MManager.Read<DWORD>(Engine.dwBase + EnginePointer);
			DWORD LocalPlayer_dwBase = MManager.Read<DWORD>(Client.dwBase + LocalPlayer);

			int LocalPlayer_isConnected = MManager.Read<int>(Engine_dwBase + 0x100);
			
			if (LocalPlayer_isConnected == 6)
			{

				DWORD Client_glowPointer = MManager.Read<DWORD>(Client.dwBase + GlowObject);
			
				int Client_objectCount = MManager.Read<int>(Client.dwBase + GlowObject + 0x4);

				
				for (int i = 0; i < Client_objectCount; i++)
				{
	
					Gllow glowObj = MManager.Read<Gllow>(Client_glowPointer + (i * sizeof(Gllow)));

					if (Client_glowPointer != NULL && glowObj.pEntity != NULL)
					{
						
						bool EntityPlayer_isDormant = MManager.Read<bool>(glowObj.pEntity + 0xE9);
				
						int EntityPlayer_teamNum = MManager.Read<int>(glowObj.pEntity + 0xF0);
						int ClassID = MManager.Read<int>(MManager.Read<int>(MManager.Read<int>(MManager.Read<int>(glowObj.pEntity + 0x8) + 2 * 0x4) + 0x1) + 20);
						int LocalPlayer_teamNum = MManager.Read<int>(LocalPlayer_dwBase + 0xF0);

						
						if (ClassID == 35)
						{
							
							if (!EntityPlayer_isDormant)
							{
								
								if (LocalPlayer_teamNum != EntityPlayer_teamNum)
								{
									glowObj.r = 1.0f;
									glowObj.g = 0.0f;
									glowObj.b = 0.0f;
									glowObj.a = 1.0f;
								}
								else
								{
									
									glowObj.r = 0.0f;
									glowObj.g = 0.0f;
									glowObj.b = 1.0f;
									glowObj.a = 1.0f;
								}
							
								glowObj.RenderWhenOccluded = true;
								glowObj.RenderWhenUnoccluded = false;
								glowObj.FullBloom = false;

							
								MManager.Write<Gllow>(Client_glowPointer + (i * sizeof(Gllow)), glowObj);
							}
						}
					}
				}
			}
		}

		Sleep(25);
	}
}

void JUMP()
{
	
	for (;;)
	{

		if (bON)
		{

			DWORD LocalPlayer_dwBase = MManager.Read<DWORD>(Client.dwBase + LocalPlayer);
	
			int LocalPlayer_fFlag = MManager.Read<int>(LocalPlayer_dwBase + 0x100);

		
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
		
				if (LocalPlayer_fFlag & (1 << 0))
				{
				
					MManager.Write<int>(Client.dwBase + ForceJump, 5);
					
					Sleep(20);
			
					MManager.Write<int>(Client.dwBase + ForceJump, 4);
				}
			}
		}
	
		Sleep(1);
	}
}

void main()
{
	SetConsoleTitle(" GT45GD ");
	cout << "Lol you thought i was going to give you my nice" << endl;
	cout << "looking menu, nah bro better take this. Easy to make" << endl;


	if (!MManager.Attach("csgo.exe"))
	{
		cout << "                CSGO NOT RUNNING CLOSING            " << endl;
		Sleep(1000 * 3);
		exit(0);
	}
	cout << "|                :ACTIVE CHEATS:                   |" << endl;


	Client = MManager.GetModule("client.dll");
	Engine = MManager.GetModule("engine.dll");


	thread ACTIVATION_thread = thread(ActivationByHotkeys);
	thread ESP_thread = thread(ESP);
	thread JUMP_thread = thread(JUMP);
	thread FLASH_thread = thread(FLASH);
	thread HANDS_thread = thread(HANDS);
	thread FOV_thread = thread(FOV);
	thread TRIGGER_thread = thread(Trigger);


	ACTIVATION_thread.join();
	ESP_thread.join();
	JUMP_thread.join();
	FLASH_thread.join();
	HANDS_thread.join();
	FOV_thread.join();
	TRIGGER_thread.join();


}