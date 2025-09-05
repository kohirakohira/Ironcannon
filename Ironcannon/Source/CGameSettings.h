#pragma once
#include <iostream>
#include <windows.h>

#include "Global.h"

#include "CDirectX9.h"
#include "CDirectX11.h"

#include "CSceneBase.h"
#include "CImageObject.h"
#include "CUIObject.h"

#include "CChoiceImage.h"
#include "CSelectIcon.h"

#include "CSprite2D.h"
#include "CStaticMesh.h"

//�L�[���͗p.
#include "CMultiInputKeyManager.h"


//�O���錾.
class CSprite2D;

class CGameSettings
	:public CSceneBase
{
public:
	CGameSettings(HWND hWnd);
	~CGameSettings()override;


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
	//�w�i�𓮂����֐�.
	void MoveBackGround();

	//�V�[���̎��.
	CSceneType GetSceneType() const override { return m_SceneType; }
public:
	//�E�B���h�E�n���h��.
	HWND		m_hWnd;

	//�^�C�g���摜.
	std::shared_ptr<CSprite2D>			m_pSpriteSetting;
	//�^�C�g���摜�̔w�i.
	std::shared_ptr<CSprite2D>			m_pSpriteSettingBackGround;
	//�u�J�n����H�v�摜.
	std::shared_ptr<CSprite2D>			m_pSpriteStart;
	//�I�����摜.
	std::shared_ptr<CSprite2D>			m_SpriteChoice;
	//�I�����摜.
	std::shared_ptr<CSprite2D>			m_SpriteYesSelect;
	std::shared_ptr<CSprite2D>			m_SpriteNoSelect;



	//�^�C�g���\���p�|��.
	std::shared_ptr<CImageObject>				m_pSpriteSettingImg;
	//�w�i�͗l�\���p�|��.
	std::shared_ptr<CImageObject>				m_pSpriteSettingBackGroundImg;
	//�J�n����H�\���p�|��.
	std::shared_ptr<CImageObject>				m_pSpriteStartImg;
	//�I�����\���p�|��.
	std::shared_ptr<CChoiceImage>				m_pSpriteChoiceImg;
	//YES&NO�\���p�|��.
	std::shared_ptr<CSelectIcon>				m_pSpriteYesSelectImg;
	std::shared_ptr<CSelectIcon>				m_pSpriteNoSelectImg;

	//�V�[���^�C�v�ϐ�.
	CSceneType					m_SceneType;


	//����.
	D3DXVECTOR2 m_UV = { 1.f, 1.f };

	//�L�[����.
	std::shared_ptr<CMultiInputKeyManager>		m_InputKey;




	//�`��t���O.
	bool DrawFlag;

private:


};