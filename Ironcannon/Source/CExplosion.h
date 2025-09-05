#pragma once
#include "CSpriteObject.h"

/**************************************************
*	�����N���X
**/
class CExplosion
	: public CSpriteObject	//�X�v���C�g�I�u�W�F�N�g�N���X���p��
{
public:
	CExplosion();
	virtual ~CExplosion() override;

	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj ) override;

	void ResetAnimation() {
		m_PatternNo.x = 0;
		m_PatternNo.y = 0;
		m_AnimCount = 0;
	}

protected:
	POINTS	m_PatternNo;	//�p�^�[���ԍ�(�}�X��)
	int		m_AnimCount;	//�A�j���[�V�����J�E���g
};
