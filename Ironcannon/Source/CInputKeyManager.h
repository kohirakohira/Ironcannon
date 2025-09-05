#pragma once
#include <iostream>


//--------------------------------------------------------------
// �L�[���͐�p�N���X.
//--------------------------------------------------------------
// NowInputKey()	�F�����ꂽ�u�Ԃ�Ԃ��Ă����.
// InputKey()		�F������Ă���Ԃ�Ԃ��Ă����.
// ReleseInputKey()	�F�������u�Ԃ�Ԃ��Ă����.


class CInputKeyManager
{
public:
	CInputKeyManager();
	~CInputKeyManager();

	//��ɉ񂵂Ăق���.
	void Update();
	//������.
	void Init();

	//�����ꂽ�u��.
	bool NowInputKey();
	//������Ă����.
	bool InputKey();
	//�������u��.
	bool ReleseInputKey();

	//���͂��󂯕t����.
	void SetKey(char key) { CheckKey = key; }

private:
	//���������̔���.
	bool Input;
	//1�t���[���O�̏��.
	bool OldInput;
	//������Ă��邩�`�F�b�N����L�[.
	char CheckKey;

};