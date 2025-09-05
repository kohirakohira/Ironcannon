#pragma once
#include <iostream>
#include <unordered_map>			//unordered_map:�A�z�R���e�i�������ȃA�N�Z�X.

#include "CInputKeyManager.h"		//�L�[�}�l�[�W���[.


//--------------------------------------------------------------
// �L�[���͐�p�N���X.
//--------------------------------------------------------------
class CMultiInputKeyManager
{
public:
	CMultiInputKeyManager();
	~CMultiInputKeyManager();

	//��ɉ���ė~����.
	void Update();
	//������.
	void Init();


	//�K�v�ȃL�[���ݒ肵�Ă�����.
	void SetKey(const std::vector<char>& keys);
	//�����ꂽ�u��.
	bool NowInputKey(char key);
	//������Ă����.
	bool InputKey(char key);
	//�������u��.
	bool ReleaseInputKey(char key);



public:
	//�K�v�ȃL�[�����m�ۂ���ϐ��R���e�i.
	std::unordered_map<char, CInputKeyManager> m_Key;


};