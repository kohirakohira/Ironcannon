#pragma once
#include <iostream>
#include <windows.h>

#include "CSceneBase.h"		//���N���X.
#include "CGameMain.h"		//�Q�[�����C���N���X.
#include "CGameTitle.h"		//�^�C�g��.
#include "CGameResult.h"	//���U���g�N���X(�����E������������).
#include "CGameSettings.h"	//�Q�[���ݒ�N���X.

#include "GameDebug.h"		//�f�o�b�O�p�N���X.

class CSceneManager
{
public:
	CSceneManager(HWND hWnd );
	~CSceneManager();

	//����֐�.
	void Update();
	//�`��֐�.
	void Draw();

	//�ǂݍ���.
	HRESULT LoadData();

	//�C���X�^���X����.
	void Create();

	//�V�[���J�ڊ֐�.
	void Change(std::shared_ptr<CSceneBase> InScene);
	
	
public:
	//�m�F�p�̕ϐ�.
	bool			m_Flag;

	//�E�B���h�E�n���h��.
	HWND			m_hWnd;

private:
	//�V�[����ۑ�����悤�̕ϐ�.
	std::shared_ptr<CSceneBase> m_pScene;

	//�V�[����ۑ����Ă������m.
	CSceneType					m_CurrentSceneType;
	//���̃V�[��.
	CSceneType					m_NextType;

};