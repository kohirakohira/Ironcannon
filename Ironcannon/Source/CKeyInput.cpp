#include "CKeyInput.h"

// �R���X�g���N�^
CKeyInput::CKeyInput()
	: m_KeyCnt()
	, m_NowKey()
	, m_OldKey()
{
}

// �f�X�g���N�^
CKeyInput::~CKeyInput()
{
}

// �L�[���͂̎�t
void CKeyInput::Update()
{
	std::vector<int> m_Key; // ���t���[���̃L�[���͂��ꎞ�ۑ�

	m_OldKey.clear();

	// 1F�O�̃L�[�Ɍ��݂̃L�[���͂��L�^
	if (!m_NowKey.empty())
	{
		m_OldKey = m_NowKey;
	}

	// ���t���[���̃L�[��Ԃ�������
	m_NowKey.clear();

	// ���݉�����Ă���L�[���`�F�b�N���Ēǉ�
	// �L�[�{�[�h��A�`Z
	for (int KeyInput = 'A'; KeyInput <= 'Z'; ++KeyInput)
	{
		if (GetAsyncKeyState(KeyInput) & 0x8000)
		{
			m_Key.emplace_back(KeyInput);
			m_NowKey.emplace_back(KeyInput);
		}
	}

	// ���̑��L�[�i����X�y�[�X�Ȃǁj
	if (GetAsyncKeyState(VK_SPACE)	& 0x8000)  m_NowKey.emplace_back(VK_SPACE);
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)  m_NowKey.emplace_back(VK_RETURN);
	if (GetAsyncKeyState(VK_LEFT)	& 0x8000)  m_NowKey.emplace_back(VK_LEFT);
	if (GetAsyncKeyState(VK_RIGHT)	& 0x8000)  m_NowKey.emplace_back(VK_RIGHT);
	if (GetAsyncKeyState(VK_UP)		& 0x8000)  m_NowKey.emplace_back(VK_UP);
	if (GetAsyncKeyState(VK_DOWN)	& 0x8000)  m_NowKey.emplace_back(VK_DOWN);

	// ���t���[���̃L�[�𗚗��ɒǉ�
	m_KeyCnt.emplace_back(m_Key);

	// ����������������폜�i�ő�10�t���[���ێ��j

	if (m_KeyCnt.size() > MaxFrame)
	{
		m_KeyCnt.erase(m_KeyCnt.begin());
	}
}

// �L�[���������u��(�g���K�[)
bool CKeyInput::IsDown(int Key)
{
	if (IsGetKeyInfo(Key, m_NowKey)== true // �������ꂽ
		&& IsGetKeyInfo(Key, m_OldKey) == false) // �O�t���[���͉�����Ă��Ȃ�
	{
		return true;
	}
	return false;
}

// �L�[�������ꑱ���Ă���
bool CKeyInput::IsRepeat(int Key)
{
	if (IsGetKeyInfo(Key, m_NowKey) == true // �������ꂽ
		&& IsGetKeyInfo(Key, m_OldKey) == true) // �O�t���[����������Ă���
	{
		return true;
	}
	return false;
}

// �L�[�������ꂽ(�����[�X)
bool CKeyInput::IsUp(int Key)
{
	if (IsGetKeyInfo(Key, m_NowKey) == false // ��������Ă��Ȃ�
		&& IsGetKeyInfo(Key, m_OldKey) == true) // �O�t���[���͉�����Ă���
	{
		return true;
	}
	return false;
}

// �L�[�̏�Ԃ��擾
bool CKeyInput::IsGetKeyInfo(int WantKey, std::vector<int> CheckKey)
{
	for (auto Key : CheckKey)
	{
		if (Key == WantKey)
		{
			return true;
		}
	}
	return false;
}
