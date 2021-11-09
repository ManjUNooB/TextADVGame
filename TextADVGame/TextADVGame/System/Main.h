#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>

HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update();
void Draw();

#endif	//_MAIN_H_