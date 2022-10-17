#include "input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void Input::Initialize(HINSTANCE hInstance, HWND hwnd) {

    HRESULT result;

    // DirectInput�̏�����
    result = DirectInput8Create(
        hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // �L�[�{�[�h�f�o�C�X�̐���
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    // ���̓f�[�^�`���̃Z�b�g
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    assert(SUCCEEDED(result));
    // �r�����䃌�x���̃Z�b�g
    result = keyboard->SetCooperativeLevel(
        hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}
void Input::Update() {


    // �L�[�{�[�h���̎擾�J�n
    keyboard->Acquire();
    // �O��̃L�[���͂�ۑ�
    memcpy(keyPre, key, sizeof(key));
    // �S�L�[�̓��͏�Ԃ��擾����
    keyboard->GetDeviceState(sizeof(key), key);
}
bool Input::PushKey(BYTE keyNumber) {
    // �ُ�Ȉ��������o
    assert(0 <= keyNumber && keyNumber <= 256);

    // 0�łȂ���Ή����Ă���
    if (key[keyNumber]) {
        return true;
    }

    // �����Ă��Ȃ�
    return false;
}

bool Input::TriggerKey(BYTE keyNumber) {
    // �ُ�Ȉ��������o
    assert(0 <= keyNumber && keyNumber <= 256);

    // �O��0�ŁA����0�łȂ���΃g���K�[
    if (!keyPre[keyNumber] && key[keyNumber]) {
        return true;
    }

    // �g���K�[�łȂ�
    return false;
}