#pragma once
#include <iostream>

#include "CGameObject.h"
#include "CSprite2D.h"

//-----�摜�N���X.-----
//�Q�[���I�u�W�F�N�g���p��.
class CImageObject
	:public CGameObject
{
public:
	CImageObject();
	~CImageObject();

	//����֐�.
	void Update() override;
	//�`��֐�.
	void Draw();

	//�X�v���C�g��ڑ�����.
	void AttachSprite(std::shared_ptr<CSprite2D> pSprite) {
		m_pSprite = pSprite;
	}
	//�X�v���C�g��؂藣��.
	void DetachSprite() {
		m_pSprite = nullptr;
	}

	//�摜�̈ʒu��ݒ肷��.
	void SetPosition(float x, float y, float z)
	{
		//�ʒu��ݒ�.
		m_vPosition = D3DXVECTOR3(x, y, z);
	}

	//�摜�̓���.
	void ImageMove();


protected:
	//�`��֐���final�ł���ȏ�p������̂�h��.
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override final;




public:
	//�X�v���C�g�ϐ��̐錾.
	std::shared_ptr<CSprite2D>	 m_pSprite;

};