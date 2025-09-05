#include "CGameResult.h"
#include "CSoundManager.h"

//�O���錾.
#include "CSprite2D.h"

CGameResult::CGameResult(HWND hWnd)
	: m_hWnd				( hWnd )

	, m_pSpriteResult		( nullptr )
	, m_pSpriteSelect		( nullptr )
	, m_SpriteChoice		( nullptr )

	, m_pSpriteObj			( nullptr )

	, m_pStaticMeshFighter	( nullptr )
	, m_pStaticMeshGround	( nullptr )
	, m_pStaticMeshCloud	( nullptr )

	, m_pPlayerManager		( nullptr )
	, m_pGround				( nullptr )

	, m_pCamera				( nullptr )

	, m_pSelectIcon			( nullptr )

	, DrawFlag				( false )

	, m_Key					( nullptr )
{
	//���ʂ��ǂ���������.
	WinOrDrawFunction();
}

CGameResult::~CGameResult()
{
	m_hWnd = nullptr;
}

void CGameResult::Update()
{
	//BGM�̃��[�v�Đ�.
	CSoundManager::PlayLoop(CSoundManager::BGM_Title);


	//��-----�^�C�g���ł̉��o-----��.
	m_Key->Update();


	//��-----�^�C�g���ł̉��o-----��.


	if (m_Key->ReleaseInputKey('Z') == true)
	{
		//BGM�̃��[�v��~.
		CSoundManager::Stop(CSoundManager::BGM_Title);

		//SE�̍Đ�.
		CSoundManager::PlaySE(CSoundManager::SE_Click);

		DrawFlag = true;

		m_SceneType = CSceneType::Title;
	}
}

void CGameResult::Draw()
{
	if (DrawFlag == true) {
		return;
	}

	//�J�����̕`��.
	m_pCamera->Draw();

	//�v���C���[�̕`��.
	m_pPlayerManager->Draw(m_pCamera->m_mView, m_pCamera->m_mProj, m_pCamera->m_Light, m_pCamera->m_Camera);

	//�n�ʂ̕`��.
	m_pGround->Draw(m_pCamera->m_mView, m_pCamera->m_mProj, m_pCamera->m_Light, m_pCamera->m_Camera);


	//�O��֌W����.
	CDirectX11::GetInstance().SetDepth(false);
	//���U���g�摜�̕`��.
	m_pSpriteObj->Draw();
	//�I���摜�̕`��.
	m_pSelectIcon->Draw();
	CDirectX11::GetInstance().SetDepth(true);
}

void CGameResult::Init()
{
	//�J�����̈ʒu.
	m_pCamera->SetCameraPos(-1.5f, 1.5f, 14.f);
	m_pCamera->SetLightPos(-1.5f, 2.f, 5.f);
	//�ʒu�̐ݒ�.
	m_pPlayerManager->SetPosition(0.f, 1.f, 6.f);

	//�傫����ݒ�.
	m_pSpriteObj->SetPosition(WND_W / 2 - 640, 0.f, 0.f);
	m_pSpriteObj->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteObj->SetScale(0.7f, 0.7f, 0.f);

	//�傫����ݒ�.
	m_pSelectIcon->SetPosition(WND_W / 2 - 128, WND_H / 1.5 + 128, 0.f);
	m_pSelectIcon->SetRotation(0.f, 0.f, 0.f);
	m_pSelectIcon->SetScale(1.f, 1.f, 1.f);


	//�L�[�ݒ�.
	m_Key->Init();
	m_Key->SetKey({ 'Z' });


}

void CGameResult::Destroy()
{

}

void CGameResult::Create()
{
	//�X�v���C�g�̐���.
	m_pSpriteResult = std::make_shared<CSprite2D>();
	m_pSpriteSelect = std::make_shared<CSprite2D>();
	m_SpriteChoice	= std::make_shared<CSprite2D>();

	//�X�v���C�g�I�u�W�F�N�g�̐���.
	m_pSpriteObj = std::make_shared<CUIObject>();

	//�X�^�e�B�b�N���b�V���̃C���X�^���X�쐬
	m_pStaticMeshFighter = std::make_shared<CStaticMesh>();
	m_pStaticMeshGround = std::make_shared<CStaticMesh>();
	m_pStaticMeshCloud = std::make_shared<CStaticMesh>();

	//�L�����N�^�[�N���X�̃C���X�^���X�쐬
	m_pPlayerManager = std::make_shared<CPlayerManager>();

	//�n�ʃN���X�̃C���X�^���X�쐬.
	m_pGround = std::make_shared<CGround>();
	//�n�ʂɐݒ肷��.
	m_pGround->SetPlayer(*m_pPlayerManager);

	//�J�����N���X�̃C���X�^���X�쐬.
	m_pCamera = std::make_shared<CCamera>();

	//�I���摜�̃C���X�^���X����.
	m_pSelectIcon = std::make_shared<CSelectIcon>();
	//�I�����̃C���X�^���X����.
	m_pChoiceIcon = std::make_shared<CChoiceImage>(m_SceneType);

	//�L�[�C���v�b�g.
	m_Key = std::make_shared<CMultiInputKeyManager>();



}

HRESULT CGameResult::LoadData()
{
	//�^�C�g���摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE WH_SIZE = {
		WND_W,WND_H,		//�`�敝,����.
		WND_W,WND_H,		//���摜�̕�,����.
		WND_W,WND_H			//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};
	//�I�����摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE C_SIZE = {
		16,32,		//�`�敝,����.
		16,32,		//���摜�̕�,����.
		16,32,		//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};
	//�^�C�g���摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE SELECT_SIZE = {
		256, 96,		//�`�敝,����.
		256, 96,		//���摜�̕�,����.
		256, 96			//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};

	//�I�����X�v���C�g�̓ǂݍ���.
	m_SpriteChoice->Init(_T("Data\\Texture\\UI\\Choice.png"), C_SIZE);

	//�X�^�e�B�b�N���b�V���̓ǂݍ���
	m_pStaticMeshFighter->Init(_T("Data\\Mesh\\Static\\Fighter\\Fighter.x"));
	m_pStaticMeshGround->Init(_T("Data\\Mesh\\Static\\Ground\\ground.x"));

	m_pStaticMeshCloud->Init(_T("Data\\Mesh\\Static\\Object\\cloud.x"));

	//���������������̉摜�ǂݍ���.
	if (m_SceneType == CSceneType::ResultWin)
	{
		//�Ƃ菟���X�v���C�g�̓ǂݍ���.
		m_pSpriteResult->Init(_T("Data\\Texture\\Image\\Clear.png"), WH_SIZE);
	}
	else if (m_SceneType == CSceneType::ResultDraw)
	{
		//���������X�v���C�g�̓ǂݍ���.
		m_pSpriteResult->Init(_T("Data\\Texture\\Image\\Over.png"), WH_SIZE);
	}

	//�I���摜�̃X�v���C�g�̓ǂݍ���.
	m_pSpriteSelect->Init(_T("Data\\Texture\\UI\\TitleSelectImg.png"), SELECT_SIZE);

	//�摜�̐ݒ�.
	m_pSpriteObj->AttachSprite(m_pSpriteResult);

	//�I���摜�̐ݒ�.
	m_pSelectIcon->AttachSprite(m_pSpriteSelect);
	//�I�����摜�̐ݒ�.
	m_pChoiceIcon->AttachSprite(m_SpriteChoice);

	//�L�����N�^�[�ɃA�^�b�`.
	m_pPlayerManager->AttachMesh(m_pStaticMeshFighter);
	m_pGround->AttachMesh(m_pStaticMeshGround);

	return S_OK;
}

CSceneType CGameResult::WinOrDrawFunction()
{
	//���ō���Ă݂�.
	//�����l���������ق�����������?

	//��l�ŏ����Ă�����.
	if (NoMajic <= 0)
	{
		m_SceneType = CSceneType::ResultWin;
	}
	//�����L�����Ȃ�.
	if (NoMajic > 0)
	{
		m_SceneType = CSceneType::ResultDraw;
	}
	return m_SceneType;
}
