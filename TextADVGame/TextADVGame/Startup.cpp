#include <Windows.h>
#include <cstdio>
#include <crtdbg.h>
#include "Defines.h"
#include "System/Main.h"

//timeGetTime周りの使用
#pragma comment(lib,"winmm.lib")

//--プロトタイプ--//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//--エントリポイント--//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

}
