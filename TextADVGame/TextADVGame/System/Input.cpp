#include <System/Input.h>

//--�萔
const int KEYTABLE_SIZE = 256;		//�L�[�{�[�h�̍ő�e��(???)
const int KEY_REPEAT_TICK = 3;		//�L�[�̓��̓��s�[�g���x
const int KEY_REPEAT_WAIT = 25;		//�L�[�̓��̓��s�[�g�̑҂�����

//--�O���[�o���ϐ�
//�L�[�{�[�h
BYTE g_key[KEYTABLE_SIZE];		//���݂̃L�[?
BYTE g_oldKey[KEYTABLE_SIZE];	//������Ă����L�[�H
BYTE g_repeatCount[KEYTABLE_SIZE];	//���s�[�g���̃J�E���g
BYTE g_force[KEYTABLE_SIZE];		//���������Ƃ����̂ւ�(�킩���)

//�}�E�X
HWND g_mousehWnd;	//�}�E�X�n���h��
HHOOK g_mouseHook;	//�O���[�o���t�b�N
int g_wheelCount;
int g_wheelValue;
bool g_doubleClickMsg[3];
bool g_doubleClick[3];
POINT g_mousePos;


//Doxygen�̏�������
/**
* @brief �}�E�X���b�Z�[�W�t�b�N
*/
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
	}

	MSG* pMsg = reinterpret_cast<MSG*>(lParam);
	switch (pMsg->message)
	{
		//�z�C�[��
	case WM_MOUSEWHEEL:
		g_wheelCount += GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
		break;
		//���_�u���N���b�N
	case WM_LBUTTONDBLCLK:
		g_doubleClickMsg[0] = true;
		break;
		//���_�u���N���b�N
	case WM_MBUTTONDBLCLK:
		g_doubleClickMsg[1] = true;
		break;
		//�E�_�u���N���b�N
	case WM_RBUTTONDBLCLK:
		g_doubleClickMsg[2] = true;
		break;
	}

	return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
}

HRESULT InitInput()
{

}

void UninitInput()
{
	UnhookWindowsHookEx(g_mouseHook);
}

void UpdateInput()
{

}









