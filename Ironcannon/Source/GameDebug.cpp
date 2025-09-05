#include "GameDebug.h"
#include "CSoundManager.h"

//�O���錾.
#include "CSprite2D.h"

CGameDebug::CGameDebug(HWND hWnd)
	: m_hWnd							( hWnd )

	, m_pSpriteDebugIcon				( nullptr )
	, m_pSpriteTimer					( nullptr )

	, m_pSpriteObj						( nullptr )
	, m_pSpriteTimerObj					( nullptr )

	, m_pStaticMeshGround				( nullptr )

	, m_pGround							( nullptr )

	, m_pCamera							( nullptr )

	, DrawFlag							( false )





	, m_pStaticMeshItemBox				( nullptr )

	, m_pItemBoxManager					( nullptr )

	, m_pStaticMesh_TankBodyRed			( nullptr )
	, m_pStaticMesh_TankCannonRed		( nullptr )

	, m_pStaticMesh_TankBodyBlue		( nullptr )
	, m_pStaticMesh_TankCannonBlue		( nullptr )

	//, m_pPlayerManager					( nullptr )

	, m_pTimer							( nullptr )

	, m_pDbgText						( nullptr )

{
	m_SceneType = CSceneType::Debug;
}

CGameDebug::~CGameDebug()
{
	m_hWnd = nullptr;
}

void CGameDebug::Update()
{
	//BGM�̃��[�v�Đ�.
	CSoundManager::PlayLoop(CSoundManager::BGM_Title);

	//�J�����̈ړ�.
	m_pCamera->FreeMove();
	//�A�C�e���̃}�l�[�W���[.
	m_pItemBoxManager->Update();

	////�v���C���[�̃}�l�[�W���[.
	//m_pPlayerManager->Update();

	//// C�L�[�����ꂽ�瑀��v���C���[�؂�ւ�
	//if (GetAsyncKeyState('C') & 0x0001)
	//{
	//	m_pPlayerManager->SwitchActivePlayer();
	//}

}

void CGameDebug::Draw()
{
	if (DrawFlag == true) {
		return;
	}

	//�J�����̕`��.
	m_pCamera->Draw();

	//�n�ʂ̕`��.
	m_pGround->Draw(m_pCamera->m_mView, m_pCamera->m_mProj, m_pCamera->m_Light, m_pCamera->m_Camera);

	//�A�C�e���{�b�N�X�̕`��.
	m_pItemBoxManager->Draw(m_pCamera->m_mView, m_pCamera->m_mProj, m_pCamera->m_Light, m_pCamera->m_Camera);

	////�v���C���[�̕`��.
	//m_pPlayerManager->Draw(m_pCamera->m_mView, m_pCamera->m_mProj, m_pCamera->m_Light, m_pCamera->m_Camera);

	//�^�C�}�[�`��.
	m_pTimer->Draw();

	//�O��֌W����.
	CDirectX11::GetInstance().SetDepth(false);
	//�f�o�b�O�A�C�R���̕`��.
	m_pSpriteObj->Draw();
	m_pSpriteTimerObj->Draw();
	CDirectX11::GetInstance().SetDepth(true);
}

void CGameDebug::Init()
{
	//�������Ԃ̒萔�錾.
	static constexpr float TIME = 90.f;


	//�n�ʂ̈ʒu�ݒ�.
	m_pGround->SetPosition(0.f, -1.f, 0.f);
	m_pGround->SetRotation(0.f, 0.f, 0.f);
	//�J�����̈ʒu.
	m_pCamera->SetCameraPos(30.f, 20.f, 50.f);
	m_pCamera->SetLightPos(-1.5f, 2.f, 5.f);

	//�^�C�g���摜�̑傫����ݒ�.
	m_pSpriteObj->SetPosition(0.f, -32.f, 0.f);
	m_pSpriteObj->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteObj->SetScale(1.f, 1.f, 0.f);


	//�^�C�g���摜�̑傫����ݒ�.
	m_pSpriteTimerObj->SetPosition(WND_W / 2 - 128, WND_H / 2 - 128, 0.f);
	m_pSpriteTimerObj->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteTimerObj->SetScale(0.3f, 0.3f, 0.f);








	//���ؗp.
	m_pItemBoxManager->SetPosition(0.f, 20.f, 0.f);
	m_pItemBoxManager->SetRotation(0.f, 0.f, 0.f);
	m_pItemBoxManager->SetScale(0.2f, 0.2f, 0.2f);
	m_pItemBoxManager->SetItemInfo();



	//�������Ԃ̕����T�C�Y.
	m_pDbgText->SetFontSize(5.0f);


	//�Q�[���ŗV�ׂ�(�N���A��ʂɑJ�ڂ���)���ԁ�����.
	m_pTimer->StartTimer(TIME);
	m_pTimer->SetDebugFont(m_pDbgText);
	m_pTimer->SetTimerPosition(WND_W / 2, 0);



}

void CGameDebug::Destroy()
{

}

void CGameDebug::Create()
{
	//�X�v���C�g�̐���.
	m_pSpriteDebugIcon	= std::make_shared<CSprite2D>();
	m_pSpriteTimer		= std::make_shared<CSprite2D>();

	//�X�v���C�g�I�u�W�F�N�g�̐���.
	m_pSpriteObj		= std::make_shared<CUIObject>();
	m_pSpriteTimerObj	= std::make_shared<CUIObject>();

	//�X�^�e�B�b�N���b�V���̃C���X�^���X�쐬
	m_pStaticMeshGround	= std::make_shared<CStaticMesh>();

	//�n�ʃN���X�̃C���X�^���X�쐬.
	m_pGround			= std::make_shared<CGround>();

	//�J�����N���X�̃C���X�^���X�쐬.
	m_pCamera			= std::make_shared<CCamera>();






	//���ؗp.
	//�X�^�e�B�b�N���b�V���̃C���X�^���X����.
	m_pStaticMeshItemBox	= std::make_shared<CStaticMesh>();
	//�A�C�e���{�b�N�X�̃C���X�^���X����.
	m_pItemBoxManager		= std::make_shared<CItemBoxManager>();
	m_pItemBoxManager->Create();

	//��Ԃ̃C���X�^���X����(�ԂƐ�).
	m_pStaticMesh_TankBodyRed	= std::make_shared<CStaticMesh>();
	m_pStaticMesh_TankCannonRed = std::make_shared<CStaticMesh>();

	m_pStaticMesh_TankBodyBlue		= std::make_shared<CStaticMesh>();
	m_pStaticMesh_TankCannonBlue	= std::make_shared<CStaticMesh>();

	////�v���C���[�}�l�[�W���[�̃C���X�^���X����.
	//m_pPlayerManager = std::make_shared<CPlayerManager>();
	//m_pPlayerManager->Initialize();


	//�f�o�b�O�e�L�X�g�̃C���X�^���X�쐬]
	m_pDbgText = std::make_unique<CDebugText>();

	//�^�C�}�[�̃C���X�^���X�쐬.
	m_pTimer = std::make_shared<CTimer>();

}

HRESULT CGameDebug::LoadData()
{
	//�f�o�b�O�e�L�X�g�̓ǂݍ���.
	if (FAILED(m_pDbgText->Init(CDirectX11::GetInstance())))
	{
		return E_FAIL;
	}
	//�f�o�b�O�摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE WH_SIZE = {
		128,128,		//�`�敝,����.
		128,128,		//���摜�̕�,����.
		128,128			//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};
	//�^�C�g���摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE TIMER_SIZE = {
		256,256,		//�`�敝,����.
		256,256,		//���摜�̕�,����.
		256,256			//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};

	//�X�^�e�B�b�N���b�V���̓ǂݍ���
	m_pStaticMeshGround	->Init(_T("Data\\Mesh\\Static\\Ground\\ground.x"));

	//�f�o�b�O�X�v���C�g�̓ǂݍ���.
	m_pSpriteDebugIcon->Init(_T("Data\\Texture\\Image\\InDebug.png"), WH_SIZE);
	//�^�C�}�[�X�v���C�g�̓ǂݍ���.
	m_pSpriteTimer->Init(_T("Data\\Texture\\Image\\Timer.png"), TIMER_SIZE);


	//�摜�̐ݒ�.
	m_pSpriteObj->AttachSprite(m_pSpriteDebugIcon);
	m_pSpriteTimerObj->AttachSprite(m_pSpriteTimer);



	//�n�ʂ̉摜�ݒ�.
	m_pGround->AttachMesh(m_pStaticMeshGround);








	//���ؗp.
	//�X�^�e�B�b�N���b�V���̓ǂݍ���.
	m_pStaticMeshItemBox->Init(_T("Data\\Mesh\\Static\\ItemBox\\ItemBox.x"));
	//�A�C�e���{�b�N�X�̉摜�ݒ�.
	m_pItemBoxManager->AttachMesh(m_pStaticMeshItemBox);


	//�f�o�b�N���ɂ���Ԃ����؂ł���悤�ɂ��Ă�������
	m_pStaticMesh_TankBodyRed->Init(_T("Data\\Mesh\\Static\\Tank\\Red\\Body\\Body.x"));
	m_pStaticMesh_TankCannonRed->Init(_T("Data\\Mesh\\Static\\Tank\\Red\\Cannon\\Cannon.x"));

	// ���(��)
	m_pStaticMesh_TankBodyBlue->Init(_T("Data\\Mesh\\Static\\Tank\\Blue\\Body\\Body.x"));
	m_pStaticMesh_TankCannonBlue->Init(_T("Data\\Mesh\\Static\\Tank\\Blue\\Cannon\\Cannon.x"));
	////�v���C���[�}�i�[�W���[�ɃA�^�b�`.
	//m_pPlayerManager->AttachMeshesToPlayer(0, m_pStaticMesh_TankBodyRed,  m_pStaticMesh_TankCannonRed);
	//m_pPlayerManager->AttachMeshesToPlayer(1, m_pStaticMesh_TankBodyBlue, m_pStaticMesh_TankCannonBlue);












	return S_OK;
}