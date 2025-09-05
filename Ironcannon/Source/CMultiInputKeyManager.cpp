#include "CMultiInputKeyManager.h"

CMultiInputKeyManager::CMultiInputKeyManager()
	: m_Key				()
{

}

CMultiInputKeyManager::~CMultiInputKeyManager()
{
	
}

//��ɉ񂵂Ăق���.
void CMultiInputKeyManager::Update()
{
	//m_Key�́Astd::unodere_map<char, CInputKeyManager>�̏���ێ����Ă���.
	for (auto& pair : m_Key)
	{
		auto& Inkey		= pair.first;	//m_Key��1�ڂ̗v�f:char.
		auto& manager	= pair.second;	//m_Key��2�ڂ̗v�f:CInputKeyManager.

		//�L�[��Update()����.
		manager.Update();
	}
}

//������.
void CMultiInputKeyManager::Init()
{
	for (auto& pair : m_Key)
	{
		auto& Inkey = pair.first;	//m_Key��1�ڂ̗v�f:char.
		auto& manager = pair.second;	//m_Key��2�ڂ̗v�f:CInputKeyManager.

		//�L�[��Init()����.
		manager.Init();
	}
}

//�K�v�ȃL�[���ݒ肵�Ă�����.
void CMultiInputKeyManager::SetKey(const std::vector<char>& keys)
{
	for (char Inkey : keys)
	{
		if (m_Key.find(Inkey) == m_Key.end())
		{
			//�V�����v�f�̒ǉ���.insert(std::make_pair(�^,�@�l))�����l.
			CInputKeyManager manager;
			manager.SetKey(Inkey);
			m_Key.emplace(Inkey, manager);
		}
	}
}

//�����ꂽ�u��.
bool CMultiInputKeyManager::NowInputKey(char key)
{
	//�o�^�ς�?.
	auto It = m_Key.find(key);

	//�S�ēo�^�ł��Ă�H.
	if (It != m_Key.end())
	{
		//�S�{�^���𔻒肳����.
		return It->second.NowInputKey();
	}

	//���o�^��false�ŕԂ�.
	return false;
}

//������Ă����.
bool CMultiInputKeyManager::InputKey(char key)
{
	//�o�^�ς�?.
	auto It = m_Key.find(key);

	//�S�ēo�^�ł��Ă�H.
	if (It != m_Key.end())
	{
		//�S�{�^���𔻒肳����.
		return It->second.InputKey();
	}
	//���o�^��false�ŕԂ�.
	return false;
}

//�������u��.
bool CMultiInputKeyManager::ReleaseInputKey(char key)
{
	//�o�^�ς�?.
	auto It = m_Key.find(key);

	//�S�ēo�^�ł��Ă�H.
	if (It != m_Key.end())
	{
		//�S�{�^���𔻒肳����.
		return It->second.ReleseInputKey();
	}
	//���o�^��false�ŕԂ�.
	return false;
}
