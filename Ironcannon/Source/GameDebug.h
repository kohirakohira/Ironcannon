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

#include "CGround.h"




//���ؗp.
#include "CPlayerManager.h"

//�A�C�e��.
#include "CItemBoxManager.h"


//���ԗp.
#include "CTimer.h"
//�t�H���g�p(��).
#include "CDebugText.h"



//�O���錾.
class CSprite2D;

class CGameDebug
	:public CSceneBase
{
public:
	CGameDebug(HWND hWnd);
	~CGameDebug()override;


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

	//�f�o�b�O�摜.
	std::shared_ptr<CSprite2D>			m_pSpriteDebugIcon;
	//�^�C�}�[�摜.
	std::shared_ptr<CSprite2D>			m_pSpriteTimer;

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	std::shared_ptr<CUIObject>			m_pSpriteObj;
	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X(�^�C�}�[).
	std::shared_ptr<CUIObject>			m_pSpriteTimerObj;

	//�X�^�e�B�b�N���b�V��(�g���܂킷����)
	std::shared_ptr<CStaticMesh>		m_pStaticMeshGround;		//�n��

	//�V�[���^�C�v�ϐ�.
	CSceneType m_SceneType;


	//���o.
	//�n��.
	std::shared_ptr<CGround>			m_pGround;
	//�J����.
	std::shared_ptr<CCamera>			m_pCamera;

	//�`��t���O.
	bool DrawFlag;





//-----------------------------------------------------------
//--------------------------���ؗp.--------------------------
//-----------------------------------------------------------
	//�X�^�e�B�b�N���b�V��(�A�C�e���̔�).
	std::shared_ptr<CStaticMesh>		m_pStaticMeshItemBox;	//�A�C�e���{�b�N�X.

	//�A�C�e���N���X.
	std::shared_ptr<CItemBoxManager>	m_pItemBoxManager;


	//��Ԃ̃��b�V��(�ԂƐ�)
	std::shared_ptr<CStaticMesh>		m_pStaticMesh_TankBodyRed;
	std::shared_ptr<CStaticMesh>		m_pStaticMesh_TankCannonRed;
	
	std::shared_ptr<CStaticMesh>		m_pStaticMesh_TankBodyBlue;
	std::shared_ptr<CStaticMesh>		m_pStaticMesh_TankCannonBlue;

	//�v���C���[�}�l�[�W���[.
	//std::shared_ptr<CPlayerManager> 	m_pPlayerManager;


	//�^�C�}�[�N���X.
	std::shared_ptr<CTimer>				m_pTimer;
	//�f�o�b�O�e�L�X�g.
	std::shared_ptr<CDebugText>			m_pDbgText;




private:


};