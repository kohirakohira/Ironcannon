#pragma once
#include <iostream>
#include "CSceneType.h"

#include "CDirectX9.h"
#include "CDirectX11.h"

class CSceneBase
{
public:
	CSceneBase() {};
	virtual~CSceneBase() {};

	//����֐�.
	virtual void Update()	= 0;
	//�`��֐�.
	virtual void Draw()		= 0;
	//�������֐�.
	virtual void Init()		= 0;
	//����֐�.
	virtual void Destroy()	= 0;
	//�C���X�^���X�쐬�֐�.
	virtual void Create()	= 0;
	//�f�[�^�̓ǂݍ���.
	virtual HRESULT LoadData() = 0;

	//�Ȃ�̃V�[���Ȃ̂��𔻒肷��֐�.
	virtual CSceneType GetSceneType() const = 0;
}; 

