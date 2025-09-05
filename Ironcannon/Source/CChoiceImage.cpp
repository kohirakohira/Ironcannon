//�錾���ĒZ�����Ă���.
#define GetKey(KEY) (GetAsyncKeyState(KEY))

#include "CChoiceImage.h"

CChoiceImage::CChoiceImage(CSceneType typ)
	:m_SceneType		( typ )

	, m_IsSelected		( false )
{

}

CChoiceImage::~CChoiceImage()
{

}

//����֐�.
void CChoiceImage::Update()
{
	//�I�����̈ړ��֐�.
	MoveChoiceImg();
}

//�`��֐�.
void CChoiceImage::Draw()
{
	//�`�揈��.
	CUIObject::Draw();
}

//�I�����̈ړ��֐�.
void CChoiceImage::MoveChoiceImg()
{
	//�萔�錾.
	//�ʒu�̒����p.
	const float posAdjustment_1 = 1.5f;
	const float posAdjustment_2 = 1.2f;
	const float posAdjustment_3 = 1.37f;
	const float posAdjustment_4 = 2.75f;

	switch (m_SceneType)
	{
	case CSceneType::Title:
		//��ړ�(�v���C).
		if (GetKey('W') & 0x0001)
		{
			//�߂鏈��.
			m_vPosition.y = WND_H / posAdjustment_1;
			//�Z�b�e�B���O.
			m_IsSelected = false;
		}
		//���ړ�(�G���h).
		if (GetKey('S') & 0x0001)
		{
			//�Q�[���X�^�[�g����.
			m_vPosition.y = WND_H / posAdjustment_2;
			//����.
			m_IsSelected = true;
		}
		break;
	case CSceneType::Debug:
		//���������������Ȃ�.
		break;
	case CSceneType::Setting:
		//�E�ړ�(�X�^�[�g).
		if (GetKey('D') & 0x0001)
		{
			//�^�C�g���ɖ߂鏈��.
			m_vPosition.x = WND_W / posAdjustment_3;
			//�߂�.
			m_IsSelected = false;
		}
		//���ړ�(�߂�).
		if (GetKey('A') & 0x0001)
		{
			//�Q�[�����C������.
			m_vPosition.x = WND_W / posAdjustment_4;
			//���C��.
			m_IsSelected = true;
		}
		break;
	case CSceneType::Main:
		//���������������Ȃ�.
		break;
	case CSceneType::Result:
	case CSceneType::ResultWin:
	case CSceneType::ResultDraw:

		break;
	default:
		break;
	}
}
