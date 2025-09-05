#include "CGameSettings.h"
#include "CSoundManager.h"

//�O���錾.
#include "CSprite2D.h"

//�萔�錾.
constexpr float UV_SPEED = 0.001f;


CGameSettings::CGameSettings(HWND hWnd)
	: m_hWnd(hWnd)

	, m_pSpriteSetting				( nullptr )
	, m_pSpriteSettingBackGround	( nullptr )
	, m_pSpriteStart				( nullptr )
	, m_SpriteChoice				( nullptr )

	, m_SpriteYesSelect				( nullptr )
	, m_SpriteNoSelect				( nullptr )

	, m_pSpriteSettingImg			( nullptr )
	, m_pSpriteSettingBackGroundImg ( nullptr )

	, m_pSpriteStartImg				( nullptr )

	, m_pSpriteChoiceImg			( nullptr )
	, m_pSpriteYesSelectImg			( nullptr )
	, m_pSpriteNoSelectImg			( nullptr )

	, DrawFlag						( false )

	, m_InputKey					( nullptr )

{
	m_SceneType = CSceneType::Setting;
	m_UV = { 0.1f, 0.1f };
}

CGameSettings::~CGameSettings()
{
	m_hWnd = nullptr;
}

//����֐�.
void CGameSettings::Update()
{
	//�萔�錾.
	constexpr float UV_SPEED = 0.001f;



	//BGM�̃��[�v�Đ�.
	CSoundManager::PlayLoop(CSoundManager::BGM_Title);

	//�w�i�̓��������x.
	m_UV.x += UV_SPEED;
	m_UV.y -= UV_SPEED;
	//�w�i�̖͗l�𓮂����l��ݒ�.
	m_pSpriteSettingBackGround->SetUVInfomation(m_UV, true);

	//�L�[���͎�t.
	m_InputKey->Update();

	//�w�i�̓��������x.
	MoveBackGround();

	//�w�i�̎s���͗l�𓮂����p���摜�̕ҏW�K�{!!.
	m_pSpriteSettingBackGroundImg->Update();

	//�I�����̈ړ�����.
	m_pSpriteChoiceImg->Update();

	//�V�[���̑J��.
	if (m_InputKey->ReleaseInputKey('Z') == true)
	{
		if (m_pSpriteChoiceImg->GetSelectedFlag() == false)
		{
			//BGM�̒�~.
			CSoundManager::Stop(CSoundManager::BGM_Title);

			m_SceneType = CSceneType::Title;
			
			return;
		}
		else
		{
			//BGM�̒�~.
			CSoundManager::Stop(CSoundManager::BGM_Title);

			m_SceneType = CSceneType::Main;

			return;
		}
	}
}

//�`��֐�.
void CGameSettings::Draw()
{
	if (DrawFlag == true) {
		return;
	}

	//�O��֌W����.
	CDirectX11::GetInstance().SetDepth(false);
	//�w�i�̕`��.
	m_pSpriteSettingImg->Draw();
	m_pSpriteSettingBackGroundImg->Draw();
	m_pSpriteStartImg->Draw();
	m_pSpriteYesSelectImg->Draw();
	m_pSpriteNoSelectImg->Draw();
	CDirectX11::GetInstance().SetDepth(true);

	//�I�����̕`��.
	m_pSpriteChoiceImg->Draw();
}

//�������֐�.
void CGameSettings::Init()
{
	//�萔�錾.
	const float windowYW	= WND_W / 4;			//�z�u������̂ɂ��傤�ǂ����ʒu��4�̓}�W�b�N�i���o�[.
	const float windowNW	= WND_W - (32 * 23);	//�z�u������̂ɂ��傤�ǂ����ʒu��32(�T�C�Y) * 23���̈ʒu�ɂ���.
	const float POS_X		= WND_W / 1.37f;		//�z�u������̂ɂ��傤�ǂ����ʒu�ɐݒ聦�I�����̈ʒu���u�������v�̈ʒu�ɒ�������.
	const float POS_Y		= WND_H / 1.2f;			//�z�u������̂ɂ��傤�ǂ����ʒu�ɐݒ聦���������傤�ǂ悩����.
	const float IMG_POS_X	= WND_W / 4.f;
	const float IMG_POS_Y	= WND_H / 14.f;

	//�^�C�g���摜�̑傫���E�ʒu�E��]��ݒ�.
	m_pSpriteSettingImg->SetPosition(0.f, 0.f, 0.f);
	m_pSpriteSettingImg->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteSettingImg->SetScale(1.f, 1.f, 0.f);
	//�^�C�g���摜�̔w�i�̑傫���E�ʒu�E��]��ݒ�.
	m_pSpriteSettingBackGroundImg->SetPosition(0.f, 0.f, 0.f);
	m_pSpriteSettingBackGroundImg->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteSettingBackGroundImg->SetScale(1.f, 1.f, 0.f);
	//�^�C�g���摜�̔w�i�̑傫���E�ʒu�E��]��ݒ�.
	m_pSpriteStartImg->SetPosition(IMG_POS_X, IMG_POS_Y, 0.f);
	m_pSpriteStartImg->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteStartImg->SetScale(1.f, 1.f, 0.f);
	//�I�����摜�̑傫���E�ʒu�E��]��ݒ�.
	//�����ʒu�́u�������v�̈ʒu.
	m_pSpriteChoiceImg->SetPosition(POS_X, POS_Y, 0.f);
	m_pSpriteChoiceImg->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteChoiceImg->SetScale(1.f, 1.f, 0.f);
	//�I���摜�̑傫���E�ʒu�E��]��ݒ�.
	m_pSpriteYesSelectImg->SetPosition(windowYW, POS_Y, 0.f);
	m_pSpriteYesSelectImg->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteYesSelectImg->SetScale(1.f, 1.f, 0.f);
	//�I���摜�̑傫���E�ʒu�E��]��ݒ�.
	m_pSpriteNoSelectImg->SetPosition(windowNW, POS_Y, 0.f);
	m_pSpriteNoSelectImg->SetRotation(0.f, 0.f, 0.f);
	m_pSpriteNoSelectImg->SetScale(1.f, 1.f, 0.f);

	//�L�[����.
	m_InputKey->Init();
	//�g�������L�[�������ɐݒ�.
	m_InputKey->SetKey({'Z'});

}

//����֐�.
void CGameSettings::Destroy()
{

}

//�C���X�^���X�쐬�֐�.
void CGameSettings::Create()
{
	//�X�v���C�g�̐���.
	m_pSpriteSetting			= std::make_shared<CSprite2D>();
	m_pSpriteSettingBackGround	= std::make_shared<CSprite2D>();
	m_pSpriteStart				= std::make_shared<CSprite2D>();
	m_SpriteChoice				= std::make_shared<CSprite2D>();
	m_SpriteYesSelect			= std::make_shared<CSprite2D>();
	m_SpriteNoSelect			= std::make_shared<CSprite2D>();

	//�X�v���C�g�I�u�W�F�N�g�̐���.
	m_pSpriteSettingImg = std::make_shared<CImageObject>();

	//�X�v���C�g�I�u�W�F�N�g�̐���.
	m_pSpriteSettingBackGroundImg = std::make_shared<CImageObject>();

	//�X�v���C�g�I�u�W�F�N�g�̐���.
	m_pSpriteStartImg = std::make_shared<CImageObject>();

	//�X�v���C�g�I�u�W�F�N�g�̐���.
	m_pSpriteStartImg			  = std::make_shared<CImageObject>();

	//�I�����̃X�v���C�g�I�u�W�F�N�g�̐���.
	m_pSpriteChoiceImg		= std::make_shared<CChoiceImage>(m_SceneType);
	m_pSpriteYesSelectImg	= std::make_shared<CSelectIcon>();
	m_pSpriteNoSelectImg	= std::make_shared<CSelectIcon>();

	//�L�[����.
	m_InputKey = std::make_shared<CMultiInputKeyManager>();


}

//�f�[�^�̓ǂݍ���.
HRESULT CGameSettings::LoadData()
{
	//�^�C�g���摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE WH_SIZE = {
		WND_W,WND_W,		//�`�敝,����.
		WND_W,WND_W,		//���摜�̕�,����.
		WND_W,WND_W			//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};
	//�J�n����H�摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE ST_SIZE = {
		960,160,			//�`�敝,����.
		960,160,			//���摜�̕�,����.
		960,160,			//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};
	//�I�����摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE C_SIZE = {
		16,32,				//�`�敝,����.
		16,32,				//���摜�̕�,����.
		16,32,				//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};
	//�I�����摜�̃X�v���C�g�ݒ�.
	CSprite2D::SPRITE_STATE S_SIZE = {
		256,96,				//�`�敝,����.
		256,96,				//���摜�̕�,����.
		256,96,				//�A�j���[�V���������Ȃ��̂ŁA0�ł���.
	};

	//�萔�錾.
	constexpr float ALPHA_TOP = 1.f;
	constexpr float ALPHA_BACK = 0.3f;


	//�^�C�g���X�v���C�g�̓ǂݍ���.
	m_pSpriteSetting->Init(_T("Data\\Texture\\Image\\Setting.png"), WH_SIZE);
	m_pSpriteSetting->SetAlpha(ALPHA_TOP);
	//�^�C�g���͗l�X�v���C�g�̓ǂݍ���.
	m_pSpriteSettingBackGround->Init(_T("Data\\Texture\\Image\\BackGroundImage.png"), WH_SIZE);
	m_pSpriteSettingBackGround->SetAlpha(ALPHA_BACK);
	//�J�n����H�X�v���C�g�̓ǂݍ���.
	m_pSpriteStart->Init(_T("Data\\Texture\\UI\\Message.png"), ST_SIZE);
	//�I�����X�v���C�g�̓ǂݍ���.
	m_SpriteChoice->Init(_T("Data\\Texture\\UI\\Choice.png"), C_SIZE);
	//�I���X�v���C�g�̓ǂݍ���.
	m_SpriteYesSelect->Init(_T("Data\\Texture\\UI\\Yes.png"), S_SIZE);
	m_SpriteNoSelect->Init(_T("Data\\Texture\\UI\\No.png"), S_SIZE);

	//�摜�̐ݒ�(�ݒ�摜).
	m_pSpriteSettingImg->AttachSprite(m_pSpriteSetting);
	//�摜�̐ݒ�(�ݒ�摜�̔w�i).
	m_pSpriteSettingBackGroundImg->AttachSprite(m_pSpriteSettingBackGround);
	//�摜�̐ݒ�(�J�n����H�摜).
	m_pSpriteStartImg->AttachSprite(m_pSpriteStart);
	//�摜�̐ݒ�(�I����).
	m_pSpriteChoiceImg->AttachSprite(m_SpriteChoice);
	//�摜�̐ݒ�(�I����Yes&No).
	m_pSpriteYesSelectImg->AttachSprite(m_SpriteYesSelect);
	m_pSpriteNoSelectImg->AttachSprite(m_SpriteNoSelect);



	return S_OK;
}

//�w�i�𓮂����֐�.
void CGameSettings::MoveBackGround()
{
	m_UV.x += UV_SPEED;
	m_UV.y -= UV_SPEED;
	//�w�i�̖͗l�𓮂����l��ݒ�.
	m_pSpriteSettingBackGround->SetUVInfomation(m_UV, true);
}