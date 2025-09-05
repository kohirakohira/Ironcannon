#include "CImageObject.h"

CImageObject::CImageObject()
	: m_pSprite				( nullptr )
{
}

CImageObject::~CImageObject()
{
}

void CImageObject::Update()
{
	//����.
	ImageMove();
}

void CImageObject::Draw()
{
	//���������Ə������΂�.
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

void CImageObject::ImageMove()
{
	//m_vPosition.x -= 1.0;
	//m_vPosition.y += 0.5;
	if (m_vPosition.x < -WND_W)
	{
		m_vPosition.x += WND_W * 3;
	}
	if (m_vPosition.y > WND_H)
	{
		m_vPosition.y -= WND_H * 3;
	}
}

void CImageObject::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	Draw();
}
