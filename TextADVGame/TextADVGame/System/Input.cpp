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
* �t�b�N�Ƃ́E�E�E
*	���b�Z�[�W��}�E�X�A�N�V�����E�L�[�X�g���[�N�Ȃǂ�
*	�C�x���g���C���^�[�Z�v�g(�T��)�ł��郁�J�j�Y���B
*	��������{���Ƀt�b�N�̊T�O�����ĂāA
*	�}�E�X�̓���⃁�b�Z�[�W�������|���Ď����Ă����悤��
*	�������Ă�Ǝv���B
*/
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		//���̃t�b�N��Ԃ�(?)
		return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
	}

	//cast���Ă�
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

	//�}�E�X�t�b�N��Ԃ�
	return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
}

HRESULT InitInput()
{
	//�L�[�{�[�h
	//�����܂��ł킩���
	ZeroMemory(g_key, KEYTABLE_SIZE);			//���݃L�[�̃�����������?
	ZeroMemory(g_oldKey, KEYTABLE_SIZE);		//������Ă����L�[�̃�����������?
	ZeroMemory(g_repeatCount, KEYTABLE_SIZE);	//�A�����ĉ�����Ă����L�[�̃�����������?
	memset(g_force, 255, KEYTABLE_SIZE);		//���L�[�̃��������蓖��?

	//�}�E�X
	g_mousehWnd = GetActiveWindow();			//�����Ă���E�B���h�E����n���h�����擾?
	g_mouseHook = SetWindowsHookEx(WH_GETMESSAGE, MouseProc, 0, GetCurrentThreadId());	//�}�E�X�̃t�b�N��ݒ�
	return S_OK;
}

void UninitInput()
{
	//�t�b�N�̊J��
	UnhookWindowsHookEx(g_mouseHook);
}

void UpdateInput()
{
	//�L�[�{�[�h
	memcpy(g_oldKey, g_key, sizeof(g_key));
	GetKeyboardState(g_key);

	for (int i = 0; i < KEYTABLE_SIZE; ++i)
	{
		if (g_force[i] != 255)
		{
			g_key[i] = g_force[i];
			g_force[i] = 255;
		}

		if (IsKeyPress(i))
		{
			if (g_repeatCount[i] <= KEY_REPEAT_WAIT)
			{
				++g_repeatCount[i];
			}
			else
			{
				g_repeatCount[i] -= KEY_REPEAT_TICK;
			}
		}
		else
		{
			g_repeatCount[i] = 0;
		}
	}

	//�}�E�X
	//�}�E�X���W
	GetCursorPos(&g_mousePos);
	ScreenToClient(g_mousehWnd, &g_mousePos);

	//�}�E�X�z�C�[��
	g_wheelValue = g_wheelCount;
	g_wheelCount = 0;

	//�}�E�X�N���b�N
	for (int i = 0; i < 3; ++i)
	{
		g_doubleClick[i] = g_doubleClickMsg[i];
		g_doubleClickMsg[i] = false;
	}
}

void InstantForceInput(int nKey, bool bPress)
{
	g_force[nKey] = bPress ? 0x80 : 0;
}

bool IsKeyPress(int nKey)
{
	return g_key[nKey] & 0x80;


}

bool IsKeyTrigger(int nKey)
{
	return (g_key[nKey] ^ g_oldKey[nKey]) & g_key[nKey] & 0x80;
}

bool IsKeyRelease(int nKey)
{
	return (g_key[nKey] ^ g_oldKey[nKey]) & g_oldKey[nKey] & 0x80;
}

bool IsKeyRepeat(int nKey)
{
	return g_repeatCount[nKey] == 1 || g_repeatCount[nKey] >= KEY_REPEAT_WAIT;
}

bool IsMouseDoubleClick(int nKey)
{
	switch (nKey)
	{
	default:	return false;
	case VK_LBUTTON: return g_doubleClick[0];
	case VK_MBUTTON: return g_doubleClick[1];
	case VK_RBUTTON: return g_doubleClick[2];
	}
}

const POINT& GetMousePos()
{
	return g_mousePos;
}

int GetMouseWheel()
{
	return g_wheelValue;
}








