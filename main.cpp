#include <iostream>
#include <Windows.h>


uintptr_t y_adr = 0x1D05A0E9680;
DWORD pid;
int y_value;

using namespace std;

int main()
{
	HWND hwnd = FindWindowA(NULL, "CrossCraft-Classic");
	if (hwnd == NULL)
	{
		cout << "CrossCraft not found! Exiting...";
		Sleep(2500);
		return 1;
	}

	else if (hwnd != NULL)
	{
		cout << "Crosscraft was found! Please wait..." << endl;
		Sleep(2500);
		cout << "Finding PID..." << endl;
		Sleep(2500);
	}


	DWORD GetPID = GetWindowThreadProcessId(hwnd, (LPDWORD)&pid);
	if (GetPID == NULL)
	{
		cout << "Can not find the ProcessID. Exiting...";
		Sleep(2500);
		return 1;
	}

	else if (GetPID != NULL)
	{
		cout << "PID Found: " << pid << endl;
		Sleep(2500);

	}


	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == NULL)
	{
		cout << "Could not open process, try running in Administrator. Exiting..." << endl;
		Sleep(2500);
		return 1;
	}


	while (true)
	{
		if (ReadProcessMemory(hProcess, (LPCVOID)y_adr, &y_value, sizeof(y_value), NULL))
		{
			cout << "Y Coordinate: " << y_value << endl;
		}

		else
		{
			cout << "Failed to read memory. Exiting..." << endl;
			Sleep(2500);
			return 1;
		}

		Sleep(500);
	}
	CloseHandle(hProcess);
	return 0;
}
