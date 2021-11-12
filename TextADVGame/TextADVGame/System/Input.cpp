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









