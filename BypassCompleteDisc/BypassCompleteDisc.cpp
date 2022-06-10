#include <Windows.h>
#include <iostream>


int Patch(std::wstring setupName,DWORD addrPass)
{
	HWND exeHWND = { NULL };
	exeHWND = FindWindowW(NULL, setupName.c_str());
	if (exeHWND != NULL)
	{
		std::cout << "(1/4)Success Find the game installer --->HWND:0x" << std::hex << exeHWND << std::endl << std::endl;
	}
	else
	{
		std::cout << "(1/4)failure Find the game installer" << std::endl << std::endl;
		return 0;
	}

	DWORD exeProID = { NULL };
	GetWindowThreadProcessId(exeHWND, &exeProID);
	if (exeProID != NULL)
	{
		std::cout << "(2/4)Success Get the game installer PID --->PID:" << std::dec << exeProID << std::endl << std::endl;
	}
	else
	{
		std::cout << "(2/4)failure Get the game installer PID" << std::endl << std::endl;
		return 0;
	}


	HANDLE exeHANDLE = OpenProcess(PROCESS_ALL_ACCESS, FALSE, exeProID);
	if (exeHANDLE != INVALID_HANDLE_VALUE)
	{
		std::cout << "(3/4)Success Get the game installer handle --->HANDLE:0x" << std::hex << exeHANDLE << std::endl << std::endl;
	}
	else
	{
		std::cout << "(3/4)failure Get the game installer handle" << std::endl << std::endl;
		return 0;
	}

	DWORD oldProtect = { 0 };
	char bypass[] = { 0xC7,0x40,0x0C,0x01,0x00,0x00,0x00,0xC3 };
	VirtualProtectEx(exeHANDLE, (LPVOID)addrPass, sizeof(bypass), PAGE_EXECUTE_READWRITE, &oldProtect);
	if (WriteProcessMemory(exeHANDLE, (LPVOID)addrPass, bypass, sizeof(bypass), NULL))
	{
		std::cout << "(4/4)Success Write patch" << std::endl << std::endl;
		CloseHandle(exeHANDLE);
	}
	else
	{
		std::cout << "(4/4)failure Write patch" << std::endl << std::endl;
		std::cout << "Please run this program as administrator" << std::endl << std::endl;
		CloseHandle(exeHANDLE);
		return 0;
	}

}

int main()
{
	char a = { 0 };
	std::cout << "Enter the number：" << std::endl;
	std::cout << "order：1     コンプリートディスク5,Triangle Complete Disc 5 DISC 1" << std::endl;
	std::cout << "order：2     コンプリートディスク5,Triangle Complete Disc 5 DISC 2" << std::endl;
	std::cout << "order：3     コンプリートディスク6,Triangle Complete Disc 6 DISC 1" << std::endl;
	std::cout << "order：4     コンプリートディスク6,Triangle Complete Disc 6 DISC 2" << std::endl;
	std::cout << "order：5     コンプリートディスク7,Triangle Complete Disc 7" << std::endl << std::endl;




	while (1)
	{
		std::cout << "Input order：";
		std::cin >> a;
		std::cout << std::endl;
		switch (a)
		{
		case '5':
			Patch(L"コンプリートディスク7 Setup", 0x00433AFC);
			break;
		case '4':
			Patch(L"CompleteDisc6_DISC2 Setup", 0x00433AA4);
			break;
		case '3':
			Patch(L"CompleteDisc6_DISC1 Setup", 0x00433AA4);
			break;
		case '2':
			Patch(L"コンプリートディスク5 Setup", 0x00433A4C);
			break;
		case '1':
			Patch(L"コンプリートディスク5 Setup", 0x00433A4C);
			break;
		default:
			break;
		}
	}


	system("pause");
}
