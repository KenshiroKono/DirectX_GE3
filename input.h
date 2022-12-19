#pragma once

#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定
#include <dinput.h>
#include "WinApp.h"





//入力
class Input {

public: // 
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>トリガーか</returns>
	bool TriggerKey(BYTE keyNumber);

private:

	ComPtr<IDirectInput8> directInput;
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	//winapp
	WinApp* winApp_ = nullptr;

};

