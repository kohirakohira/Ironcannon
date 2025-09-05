#include "CGame.h"
#include "CSoundManager.h"

//�R���X�g���N�^.
CGame::CGame(HWND hWnd )
	: m_hWnd			( hWnd )
	, m_pSceneManager	( nullptr )
{
	//�C���X�^���X�̍쐬.
	m_pSceneManager = std::make_shared<CSceneManager>(m_hWnd);
}


//�f�X�g���N�^.
CGame::~CGame()
{

}

//�\�z.
void CGame::Create()
{
	//�e�V�[����Create�֐�.
	m_pSceneManager->Create();
}

//���[�h�f�[�^�֐�.
HRESULT CGame::LoadData()
{
	//�T�E���h�f�[�^�̓ǂݍ���
	if (CSoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}

	//�e�V�[���ł̃��[�h�f�[�^�֐�.
	m_pSceneManager->LoadData();

	return S_OK;
}

//����֐�.
void CGame::Release()
{

}


//�X�V����.
void CGame::Update()
{
	//�e�V�[����Update�֐�.
	m_pSceneManager->Update();
}

//�`�揈��.
void CGame::Draw()
{
	//�e�V�[����Draw�֐�.
	m_pSceneManager->Draw();
}

//GitHub�m�F�p