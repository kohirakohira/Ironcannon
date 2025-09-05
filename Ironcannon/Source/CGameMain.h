#pragma once
#include <algorithm>
#include <vector>
#include <array>	

#include "CDebugText.h"			//��.
#include "CSprite3D.h"
#include "CSprite2D.h"

#include "CSpriteObject.h"
#include "CUIObject.h"

#include "CExplosion.h"

#include "CStaticMesh.h"
#include "CStaticMeshObject.h"

#include "CCharacter.h"
#include "CPlayerManager.h"
#include "CShotManager.h"
#include "CGround.h"
#include "CCannon.h"

#include "CCamera.h"

#include "CTimer.h"				//���ԗp.

#include "CSceneBase.h"

#include "Global.h"

class CGameMain
	:public CSceneBase
{
public:

	CGameMain(HWND hWnd);
	~CGameMain()override;


	//����֐�.
	void Update()override;
	//�`��֐�.
	void Draw()override;
	//�������֐�.
	void Init()override;
	//����֐�.
	void Destroy()override;
	//�C���X�^���X�쐬.
	void Create()override;
	//�f�[�^�̓ǂݍ���.
	HRESULT LoadData()override;


	//��ʂ��O���b�h�ɕ��������Ƃ��Aidx�Ԗڂ̃}�X�ɑΉ�����
	//D3D11_VIEWPORT���쐬���ĕԂ��֐�
	static D3D11_VIEWPORT MakeGridViewport(int idx, int cols, int rows, float totalW, float totalH);

	//�V�[���̎��.
	CSceneType GetSceneType() const override;

public:
	//�E�B���h�E�n���h��.
	HWND		m_hWnd;

	//�J����.
	//std::vector<std::shared_ptr<CCamera>> m_pCameras;
	std::array<std::shared_ptr<CCamera>, PLAYER_MAX> m_pCameras;

	//�f�o�b�O�e�L�X�g.
	std::shared_ptr<CDebugText>		m_pDbgText;

	//�Q�[�����ň���UI�n.
	std::shared_ptr<CSprite2D>		m_pSprite2DTimerFrame;	//�������Ԃ̘g.
	std::shared_ptr<CSprite2D>		m_pSprite2DTimer;		//�������Ԃ̎��v�g.

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	std::shared_ptr<CUIObject>		m_pSpriteTimerFrame;
	std::shared_ptr<CUIObject>		m_pSpriteTimer;

	//�Q�[���ň����X�v���C�g�f�[�^(�g���܂킷����).
	std::unique_ptr<CSprite3D>		m_pSpriteGround;
	std::unique_ptr<CSprite3D>		m_pSpritePlayer;
	std::shared_ptr<CSprite3D>		m_pSpriteExplosion;

	//�X�^�e�B�b�N���b�V��(�g���܂킷����)
	std::shared_ptr<CStaticMesh>	m_pStaticMeshGround;		//�n��
	std::shared_ptr<CStaticMesh>	m_pStaticMeshBSphere;		//�o�E���f�B���O�X�t�B�A(�����蔻��p).



	// ���
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_TankBodyRed;		// �ԑ̐�
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_TankCannonRed;	// �C����
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_TankBodyYellow;	// �ԑ̉�
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_TankCannonYellow;	// �C����
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_TankBodyBlue;		// �ԑ̐�
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_TankCannonBlue;	// �C����
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_TankBodyGreen;	// �ԑ̗�
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_TankCannonGreen;	// �C����

	// �e
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_BulletRed;		// �e��
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_BulletYellow;		// �e��
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_BulletBlue;		// �e��
	std::shared_ptr<CStaticMesh>	m_pStaticMesh_BulletGreen;		// �e��

	// �X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X
	std::unique_ptr<CStaticMeshObject>			m_pStcMeshObj;

	// �v���C���[�}�l�[�W���[
	std::shared_ptr<CPlayerManager>				m_pPlayerManager;

	// �e�N���X�}�l�[�W���[
	std::shared_ptr<CShotManager>				m_pShotManager;

	// �n�ʃN���X.
	std::unique_ptr<CGround>					m_pGround;

	//�^�C�}�[�N���X.
	std::shared_ptr<CTimer>						m_Timer;

	// �V�[���񋓕ϐ�.
	CSceneType		m_SceneType;

	// �ȈՎ��Ԃ��~�߂�ϐ�.
	int m_StopTimeCount;

};