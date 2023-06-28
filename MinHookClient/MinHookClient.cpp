// MinHookClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>
#include<LM.h>
#pragma comment(lib, "netapi32.lib")
int main()
{
    HMODULE hHookEngineDll = LoadLibrary(L"MinHoookDll.dll");
    // wait for key press to avoid race condition (Sleep 1 run before being hooked)
	system("pause");

	NET_API_STATUS status;
	USER_INFO_1003 userInfo;
	wchar_t* username = (wchar_t*)L"ao";
	wchar_t* newPassword = (wchar_t*)L"p29ifajwpa2938u4p298jf23p9rjASDFASFIKAWenfajwpa2938u4p298jf23p9rjASDFASFIKAWenfpir;fnjapoeifajwpa2938u4p298jf23";
	userInfo.usri1003_password = newPassword;
	status = NetUserSetInfo(NULL, username, 1003, (LPBYTE)&userInfo, NULL);
	if (status != NERR_Success)
		printf("error: %d\n", status);
	printf("done\n");
    return 0;
}
