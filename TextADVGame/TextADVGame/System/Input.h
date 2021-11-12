#ifndef _INPUT_H_
#define _INPUT_H_

#include <Windows.h>

HRESULT InitInput();
void UninitInput();
void UpdateInput();

//void InstantForceInput(int nKey, bool bPress);	//���ꑽ���ړ��n�̃C���v�b�g����Ȃ����ȁH�H

bool IsKeyPress(int nKey);
bool IsKeyTrigger(int nKey);
bool IsKeyRelease(int nKey);
bool IsKeyRepeat(int nKey);

bool IsMouseDoubleClick(int nKey);
const POINT& GetMousePos();
int GetMouseWheel();

#endif	//	_INPUT_H_




