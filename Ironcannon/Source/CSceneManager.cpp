#include "CSceneManager.h"

CSceneManager::CSceneManager(HWND hWnd )
	: m_pScene				( nullptr )

	, m_hWnd				( hWnd )

	, m_Flag				( false )
	
	, m_CurrentSceneType	()
	, m_NextType			()
{
	//���g���Ȃ�������^�C�g������X�^�[�g.
	if (m_pScene == nullptr)
	{
		m_CurrentSceneType = CSceneType::Title;
		Change(std::make_shared<CGameTitle>(m_hWnd));
	}
}

CSceneManager::~CSceneManager()
{
	m_hWnd	= nullptr;
}

//���쏈��.
void CSceneManager::Update()
{
	//�V�[���؂�ւ�.
	m_NextType = m_pScene->GetSceneType();
	if (m_NextType != m_CurrentSceneType)
	{
		m_CurrentSceneType = m_NextType;
		switch (m_NextType)
		{
		case CSceneType::Title:		//�^�C�g��.
			Change(std::make_shared<CGameTitle>(m_hWnd));
			break;
		case CSceneType::Setting:	//�Q�[���ݒ�.
			Change(std::make_shared<CGameSettings>(m_hWnd));
			break;
		case CSceneType::Main:		//�Q�[�����C��.
			Change(std::make_shared<CGameMain>(m_hWnd));
			break;
		case CSceneType::Result:
		case CSceneType::ResultWin:	//���U���g(����)
		case CSceneType::ResultDraw://���U���g(��������)
			Change(std::make_shared<CGameResult>(m_hWnd));
			break;
		case CSceneType::Debug:		//�f�o�b�O�p.
			Change(std::make_shared<CGameDebug>(m_hWnd));
			break;
		case CSceneType::None:
			//�����Ȃ�.
			break;
		}
	}
	//���ɃV�[���������Ă�����A����Update��ǂݍ���.
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}

}

//�`�揈��.
void CSceneManager::Draw()
{
	//���ɃV�[���������Ă�����A����Draw��ǂݍ���.
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
}

//�f�[�^�̃��[�h����.
HRESULT CSceneManager::LoadData()
{
	if (m_pScene != nullptr)
	{
		m_pScene->LoadData();
	}
	return S_OK;
}

//�C���X�^���X����.
void CSceneManager::Create()
{
	if (m_pScene != nullptr)
	{
		m_pScene->Create();
	}
}

//�V�[���̕ύX����.
void CSceneManager::Change(std::shared_ptr<CSceneBase> InScene)
{
	if (m_pScene != nullptr)
	{
		//���g���폜.
		m_pScene->Destroy();
	}

	//�V�[����ݒ肷��.
	m_pScene = InScene;

	//�C���X�^���X����.
	m_pScene->Create();

	//�f�[�^�̓ǂݍ���.
	m_pScene->LoadData();

	//�V�[���̏���ǂݍ���.
	m_pScene->Init();
}
