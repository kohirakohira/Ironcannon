#include "CSelectIcon.h"

CSelectIcon::CSelectIcon()
{

}

CSelectIcon::~CSelectIcon()
{
	//CUIObject�̃A�^�b�`�������m��؂藣���֐�.
	DetachSprite();
}

//����֐�.
void CSelectIcon::Update()
{

}

//����ȏ�p�����Ȃ�.
void CSelectIcon::Draw()
{
	if (m_pSprite == nullptr) {
		return;
	}

	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
	m_pSprite->SetPosition(m_vPosition);
	m_pSprite->SetRotation(m_vRotation);
	m_pSprite->SetScale(m_vScale);

	//�����_�����O.
	m_pSprite->Render();
}