#pragma once
#include <iostream>
#include <windows.h>

#include "Global.h"

#include "CDirectX9.h"
#include "CDirectX11.h"

#include "CSceneBase.h"
#include "CUIObject.h"
#include "CChoiceImage.h"

//�L�[�̓���.
#include "CMultiInputKeyManager.h"

//���o�p.
#include "CSprite3D.h"
#include "CStaticMesh.h"

#include "CCamera.h"

//�n�ʃN���X.
#include "CGround.h"




//�O���錾.
class CSprite2D;

class CGameTitle
	:public CSceneBase
{
public:
	CGameTitle(HWND hWnd);
	~CGameTitle()override;


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


	//�V�[���̎��.
	CSceneType GetSceneType() const override { return m_SceneType; }
public:
	//�E�B���h�E�n���h��.
	HWND		m_hWnd;

	//�^�C�g���摜.
	std::shared_ptr<CSprite2D>			m_pSpriteTitle;
	//�I�����摜.
	std::shared_ptr<CSprite2D>			m_SpriteChoice;
	//�I���摜(�v���C&�G���h).
	std::shared_ptr<CSprite2D>			m_SpritePlaySelect;
	std::shared_ptr<CSprite2D>			m_SpriteEndSelect;

	//�^�C�g���摜.
	std::shared_ptr<CUIObject>			m_pSpriteTitleImg;
	//�I�����摜.
	std::shared_ptr<CChoiceImage>		m_pSpriteChoiceImg;	
	//�I���摜(�v���C&�G���h).
	std::shared_ptr<CUIObject>			m_pSpritePlaySelectImg;
	std::shared_ptr<CUIObject>			m_pSpriteEndSelectImg;


	//�V�[���^�C�v�ϐ�.
	CSceneType m_SceneType;

	//�L�[����.
	std::shared_ptr<CMultiInputKeyManager>	m_KeyInput;

	//�`��t���O.
	bool DrawFlag;



//------------------------------------------------------------------------------------------
//	���o.
//------------------------------------------------------------------------------------------
public:
	//�J�����N���X.
	std::shared_ptr<CCamera>			m_pCamera;

	//�n�ʃN���X.
	std::shared_ptr<CGround>			m_pGround;
	//�n�ʂ̃��b�V��.
	std::shared_ptr<CStaticMesh>		m_StaticMeshGround;

	
	
	float y = 0.f;

	float rad = 0.f;



};