#include "CInputKeyManager.h"

CInputKeyManager::CInputKeyManager()
	: Input			( false )		//false: , true: .
	, OldInput		( false )		//false: , true: .
	, CheckKey		( ' ' )		//���ɓ���̂́A�Ȃ�̃L�[��.
{

}

CInputKeyManager::~CInputKeyManager()
{

}

void CInputKeyManager::Update()
{
	//���̓��͂�ۑ�����.
	OldInput = Input;
	//��������Ă��邩�ǂ���.
	//�r�b�g�}�X�N�̌��ʂ�0�Ȃ牟����Ă��Ȃ�(false),0����Ȃ��Ȃ牟����Ă���(true).
	Input = (GetAsyncKeyState(CheckKey) & 0x8000) != 0;
}
void CInputKeyManager::Init()
{
	//���������Ă�����.
	Input		= false;
	OldInput	= false;
	CheckKey	= ' ';
}

//�����ꂽ�u��.
bool CInputKeyManager::NowInputKey()
{
	//�O�t���[��������Ă��Ȃ�������.
	if (Input == true && OldInput == false)
	{
		return true;
	}
	return false;
}

//������Ă����.
bool CInputKeyManager::InputKey()
{
	//�����ꂽ�u�Ԃ�Ԃ�.
	return Input;
}

//�������u��.
bool CInputKeyManager::ReleseInputKey()
{
	//��������Ă��Ȃ�������.
	if (Input == false && OldInput == true)
	{
		return true;
	}
	return false;
}
