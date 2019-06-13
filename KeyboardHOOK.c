#include <Windows.h>
#include <stdio.h>
HHOOK lngHook;
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT Param;
		memcpy(&Param, lParam, 20);
		switch (wParam)
		{
		case WM_KEYDOWN:
			printf("KeyDown:%d\n", Param.vkCode);
			break;
		case WM_SYSKEYDOWN:
			printf("SysKeyDown:%d\n", Param.vkCode);
			break;
		case WM_KEYUP:
			printf("KeyUp:%d\n", Param.vkCode);
			break;
		case WM_SYSKEYUP:
			printf("SysKeyUp:%d\n", Param.vkCode);
			break;
		default:
			break;
		}
	}
	//Call next HOOK. If you want to intercept the message, plase return 1;.
	return CallNextHookEx(lngHook, nCode, wParam, lParam);
}
int main()
{
	//Set HOOK, HOOK handle record to lngHook variable.
	lngHook = SetWindowsHookExA(WH_KEYBOARD_LL, LowLevelKeyboardProc , GetModuleHandleA(0), 0);
	//A message while, handling HOOK messages.
	MSG msg;
	while (GetMessageA(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	UnhookWindowsHookEx(lngHook);//Unhook.
	return 0;
}
