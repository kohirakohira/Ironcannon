#pragma once
#include <iostream>
#include <windows.h>

#include "Global.h"

#include "CDirectX9.h"
#include "CDirectX11.h"

#include "CSceneBase.h"
#include "CUIObject.h"


//���o�p.
#include "CSprite3D.h"
#include "CStaticMesh.h"

#include "CCamera.h"

#include "CPlayerManager.h"
#include "CGround.h"

//�L�[�o�C���h.
#include "CMultiInputKeyManager.h"

//�I���摜.
#include "CSelectIcon.h"
//�I����.
#include "CChoiceImage.h"


//�O���錾.
class CSprite2D;

class CGameResult
	:public CSceneBase
{
public:
	CGameResult(HWND hWnd);
	~CGameResult()override;


	//����֐�.
	void Update()override;
	//�`��֐�.
	void Draw()override;
	//�������֐�.
	void Init()override;
	//����֐�.
	void Destroy()override;
	//�C���X�^���X�쐬�֐�.
	void Create()override;
	//�f�[�^�̓ǂݍ���.
	HRESULT LoadData()override;

	//���������������̔���N���X.
	CSceneType WinOrDrawFunction();

	//�V�[���̎��.
	CSceneType GetSceneType() const override { return m_SceneType; }

public:
	//�E�B���h�E�n���h��.
	HWND		m_hWnd;

	//�^�C�g���摜.
	std::shared_ptr<CSprite2D>			m_pSpriteResult;
	std::shared_ptr<CSprite2D>			m_pSpriteSelect;
	//�I�����摜.
	std::shared_ptr<CSprite2D>			m_SpriteChoice;

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	std::shared_ptr<CUIObject>			m_pSpriteObj;
	//�X�^�e�B�b�N���b�V��(�g���܂킷����)
	std::shared_ptr<CStaticMesh>		m_pStaticMeshFighter;		//���@
	std::shared_ptr<CStaticMesh>		m_pStaticMeshGround;		//�n��
	std::shared_ptr<CStaticMesh>		m_pStaticMeshCloud;			//�_

	//�V�[���^�C�v�ϐ�.
	CSceneType m_SceneType;


	//���o.
	std::shared_ptr<CPlayerManager>		m_pPlayerManager;
	std::shared_ptr<CGround>			m_pGround;
	//�J����.
	std::shared_ptr<CCamera>			m_pCamera;

	//�I���A�C�R��.
	std::shared_ptr<CSelectIcon>		m_pSelectIcon;
	//�I����.
	std::shared_ptr<CChoiceImage>		m_pChoiceIcon;

	//�`��t���O.
	bool DrawFlag;

private:
	//�m�F�p.
	int NoMajic = 0;
	//�L�[�o�C���h.
	std::shared_ptr<CMultiInputKeyManager>	m_Key;
};