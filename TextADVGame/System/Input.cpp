#include <System/Input.h>

//--定数
const int KEYTABLE_SIZE = 256;		//キーボードの最大容量(???)
const int KEY_REPEAT_TICK = 3;		//キーの入力リピート速度
const int KEY_REPEAT_WAIT = 25;		//キーの入力リピートの待ち時間

//--グローバル変数
//キーボード
BYTE g_key[KEYTABLE_SIZE];		//現在のキー?
BYTE g_oldKey[KEYTABLE_SIZE];	//押されていたキー？
BYTE g_repeatCount[KEYTABLE_SIZE];	//リピート時のカウント
BYTE g_force[KEYTABLE_SIZE];		//多分方向とかそのへん(わからん)

//マウス
HWND g_mousehWnd;	//マウスハンドル
HHOOK g_mouseHook;	//グローバルフック
int g_wheelCount;
int g_wheelValue;
bool g_doubleClickMsg[3];
bool g_doubleClick[3];
POINT g_mousePos;


//Doxygenの書き方↓
/**
* @brief マウスメッセージフック
* フックとは・・・
*	メッセージやマウスアクション・キーストロークなどの
*	イベントをインターセプト(傍受)できるメカニズム。
*	多分これ本当にフックの概念持ってて、
*	マウスの動作やメッセージを引っ掛けて持ってこれるような
*	働きしてると思われ。
*/
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		//次のフックを返す(?)
		return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
	}

	//castしてる
	MSG* pMsg = reinterpret_cast<MSG*>(lParam);
	switch (pMsg->message)
	{
		//ホイール
	case WM_MOUSEWHEEL:
		g_wheelCount += GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
		break;
		//左ダブルクリック
	case WM_LBUTTONDBLCLK:
		g_doubleClickMsg[0] = true;
		break;
		//中ダブルクリック
	case WM_MBUTTONDBLCLK:
		g_doubleClickMsg[1] = true;
		break;
		//右ダブルクリック
	case WM_RBUTTONDBLCLK:
		g_doubleClickMsg[2] = true;
		break;
	}

	//マウスフックを返す
	return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
}

HRESULT InitInput()
{
	//キーボード
	//正直まじでわからん
	ZeroMemory(g_key, KEYTABLE_SIZE);			//現在キーのメモリ初期化?
	ZeroMemory(g_oldKey, KEYTABLE_SIZE);		//押されていたキーのメモリ初期化?
	ZeroMemory(g_repeatCount, KEYTABLE_SIZE);	//連続して押されていたキーのメモリ初期化?
	memset(g_force, 255, KEYTABLE_SIZE);		//矢印キーのメモリ割り当て?

	//マウス
	g_mousehWnd = GetActiveWindow();			//動いているウィンドウからハンドルを取得?
	g_mouseHook = SetWindowsHookEx(WH_GETMESSAGE, MouseProc, 0, GetCurrentThreadId());	//マウスのフックを設定
	return S_OK;
}

void UninitInput()
{
	//フックの開放
	UnhookWindowsHookEx(g_mouseHook);
}

void UpdateInput()
{
	//キーボード
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

	//マウス
	//マウス座標
	GetCursorPos(&g_mousePos);
	ScreenToClient(g_mousehWnd, &g_mousePos);

	//マウスホイール
	g_wheelValue = g_wheelCount;
	g_wheelCount = 0;

	//マウスクリック
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








