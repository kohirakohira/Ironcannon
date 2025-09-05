#pragma once
#include <iostream>

#include "CUIObject.h"
#include "CSceneType.h"

//----------------�I�����p�N���X.----------------
//CUIObject���p�����Ă���.
class CChoiceImage
	:public CUIObject
{
public:
	CChoiceImage(CSceneType typ);
	~CChoiceImage() override;

	//����֐�.
	void Update() override;
	//�`��֐�.
	void Draw() override;

	//�I�����̈ړ��֐�.
	void MoveChoiceImg();

	//�I�����Ă��邩�ǂ������擾����֐�.
	bool GetSelectedFlag() const { return m_IsSelected; }


public:
	//�V�[���^�C�v�ϐ�.
	CSceneType		m_SceneType;

	//�I�����Ă�����̂����ʂ��邽�߂̃��m.
	bool 			m_IsSelected;


private:

};