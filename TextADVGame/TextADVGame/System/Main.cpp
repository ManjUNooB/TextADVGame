#include <System/Main.h>
#include <Defines.h>

//先生特製マクロ
//よくわからん
//見るからに初期化失敗時のマクロなんだろうけど
//どういう動きしてるのかさっぱり
//↓ここから予測
//fnに初期化関数が入って
//HRESULT型のhrに初期化関数の処理結果が入る。
//FAILEDならメッセージボックスでメッセージを出力して
//エラーを出してhrを戻す。
//do whileなので条件を満たしていなくとも実行する
#define ASSERT_FAILED(fn) do{\
hr = fn; \
if(FAILED(hr)){ \
	MessageBox(nullptr,"Init failed : "#fn, "Error",MB_OK);	\
	return hr; \
}} while(0)

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	//ASSERT_FAILED(InitDx(hWnd, width, height, false)); DirectX初期化
	//ASSERT_FAILED(InitGeometory());	//ジオメトリ初期化
	//ASSERT_FAILED(InitInput());	//入力初期化
}