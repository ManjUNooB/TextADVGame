#include <Windows.h>
#include <cstdio>
#include <crtdbg.h>
#include "Defines.h"
#include "System/Main.h"

//timeGetTime����̎g�p
#pragma comment(lib,"winmm.lib")

//--�v���g�^�C�v--//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//--�G���g���|�C���g--//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//--�ϐ��錾--//
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG message;

	//�E�B���h�E�N���X���̐ݒ�//
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

	//�E�B���h�E�N���X���̓o�^
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(nullptr, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	//�E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, wcex.lpszClassName,
		APP_TITLE, WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		HWND_DESKTOP,
		nullptr, hInstance, nullptr
	);

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//����������
	if (FAILED(Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT)))
	{
		return 0;
	}

	//FPS����
	timeBeginPeriod(1);	//1ms�P�ʂŃ^�C�}��ݒ�
	DWORD countStartTime = timeGetTime();	//���ݎ������擾
	DWORD preExecTime = countStartTime;		//���O�̎��Ԃ�ʗ̈�ɕۑ�??

	//--�E�B���h�E�Ǘ�--//
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
			DWORD nowTime = timeGetTime();	//���ݎ������擾
			if (nowTime - preExecTime >= 1000 / 60)	//���ݎ������璼�O����(???)�����������̂� 
													//60����1000�����傫���ꍇ�A�X�V�����E�`�揈����
													//�Ăяo���A���O���Ԃ����ݎ����ŏ㏑��
			{
				Update();
				Draw();
				preExecTime = nowTime;
			}
		}
	}

	//�I����
	timeEndPeriod(1);
	Uninit();
	UnregisterClass(wcex.lpszClassName, hInstance);

	return 0;

}

//--�E�B���h�E�v���V�[�W��--//
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

