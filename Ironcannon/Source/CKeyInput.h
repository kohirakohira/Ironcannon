#pragma once

#include <Windows.h>
#include <vector>

//==========================================
// �L�[���̓N���X
// �S���F�M���@����
//==========================================

//-----------------------
// �萔�錾
//-----------------------
constexpr int MaxFrame = 10; // ���͎��ԕێ�

class CKeyInput
{
public:
	CKeyInput();	// �R���X�g���N�^
	~CKeyInput();	// �f�X�g���N�^

	// �L�[���͂̎�t
	void Update();

	bool IsDown(int Key);	// �L�[���������u��(�g���K�[)
	bool IsRepeat(int Key);	// �L�[�������ꑱ���Ă���
	bool IsUp(int Key);		// �L�[�������ꂽ(�����[�X)

private:
	// �L�[�̏�Ԃ��擾
	bool IsGetKeyInfo(int WantKey, std::vector<int> CheckKey);

private:
	std::vector<std::vector<int>>	m_KeyCnt; // �L�[����
	std::vector<int>				m_NowKey; // ����̓���
	std::vector<int>				m_OldKey; // 1F�O�̃L�[����
};
