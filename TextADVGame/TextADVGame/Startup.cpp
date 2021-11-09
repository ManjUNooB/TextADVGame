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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//--変数宣言--//
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG message;

	//ウィンドウクラス情報の設定//
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.hInstance = hInstance;
	wcex.lpszClassName = "Class Name";
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_CLASSDC | CS_DBLCLKS;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//ウィンドウクラス情報の登録
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(nullptr, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	//ウィンドウの作成
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, wcex.lpszClassName,
		APP_TITLE, WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		HWND_DESKTOP,
		nullptr, hInstance, nullptr
	);

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//初期化処理
	if (FAILED(Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT)))
	{
		return 0;
	}

	//FPS制御
	timeBeginPeriod(1);	//1ms単位でタイマを設定
	DWORD countStartTime = timeGetTime();	//現在時刻を取得
	DWORD preExecTime = countStartTime;		//直前の時間を別領域に保存??

	//--ウィンドウ管理--//
	while (1)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&message, nullptr, 0, 0))
			{
				break;
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			DWORD nowTime = timeGetTime();	//現在時刻を取得
			if (nowTime - preExecTime >= 1000 / 60)	//現在時刻から直前時間(???)を引いたものが 
													//60分の1000よりも大きい場合、更新処理・描画処理の
													//呼び出し、直前時間を現在時刻で上書き
			{
				Update();
				Draw();
				preExecTime = nowTime;
			}
		}
	}

	//終了時
	timeEndPeriod(1);
	Uninit();
	UnregisterClass(wcex.lpszClassName, hInstance);

	return 0;

}

//--ウィンドウプロシージャ--//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

