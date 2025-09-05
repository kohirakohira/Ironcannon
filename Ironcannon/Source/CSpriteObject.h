#pragma once

#include "CGameObject.h"

#include "CSprite3D.h"

/************************************************************
*	�X�v���C�g�I�u�W�F�N�g�N���X.
**/
class CSpriteObject
	: public CGameObject
{
public:
	CSpriteObject();
	virtual ~CSpriteObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	//CSpriteObject�Ő錾�����֐��ŁA�ȍ~�͂����override������
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj );

	//�X�v���C�g��ڑ�����.
	void AttachSprite( CSprite3D& pSprite ){
		m_pSprite = &pSprite;
	}
	//�X�v���C�g��؂藣��.
	void DetachSprite(){
		m_pSprite = nullptr;
	}

protected:
	void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override final;

protected:
	CSprite3D*	m_pSprite;
};
