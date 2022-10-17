#include "input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void Input::Initialize(HINSTANCE hInstance, HWND hwnd) {

    HRESULT result;

    // DirectInputの初期化
    result = DirectInput8Create(
        hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // キーボードデバイスの生成
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    // 入力データ形式のセット
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
    assert(SUCCEEDED(result));
    // 排他制御レベルのセット
    result = keyboard->SetCooperativeLevel(
        hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}
void Input::Update() {


    // キーボード情報の取得開始
    keyboard->Acquire();
    // 前回のキー入力を保存
    memcpy(keyPre, key, sizeof(key));
    // 全キーの入力状態を取得する
    keyboard->GetDeviceState(sizeof(key), key);
}
bool Input::PushKey(BYTE keyNumber) {
    // 異常な引数を検出
    assert(0 <= keyNumber && keyNumber <= 256);

    // 0でなければ押している
    if (key[keyNumber]) {
        return true;
    }

    // 押していない
    return false;
}

bool Input::TriggerKey(BYTE keyNumber) {
    // 異常な引数を検出
    assert(0 <= keyNumber && keyNumber <= 256);

    // 前回が0で、今回が0でなければトリガー
    if (!keyPre[keyNumber] && key[keyNumber]) {
        return true;
    }

    // トリガーでない
    return false;
}