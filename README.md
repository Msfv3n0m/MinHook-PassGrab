# Minhook simple dll attach example

Based on https://shubakki.github.io/posts/2022/12/detecting-and-evading-sandboxing-through-time-based-evasion/

Simple minhook example via run-time dynamic linking for fun and learning

## Code structure

- **MinHookClient** console win app that loads MinHoookDll, and attempts to change the `ao` user's password to a hardcoded value
- **MinHoookDll** dll that hooks NetUserSetInfo on DLL_PROCESS_ATTACH such that when the function is called, it creates a message box with the password in addition to changing the user's password

![](https://github.com/Msfv3n0m/MinHook-PassGrab/blob/main/ur_password.PNG)
