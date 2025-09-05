#pragma once

#include <iostream>


#include "CStaticMeshObject.h"
#include "ItemType.h"

///------------------------------------------------------
/// �A�C�e���{�b�N�X(�X�^�e�B�b�N���b�V���I�u�W�F���p��).
///------------------------------------------------------

class CItemBox
	:public CStaticMeshObject
{
public:
	CItemBox();
	~CItemBox()override;

	//����֐�.
	void Update() override;
	//�`��֐�.
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//�ǂꂾ�������Ȃ邩�A���x���擾.
	void GravityMath();

	//�A�C�e���̏���ݒ肷��.
	void SetItemInfo(CItemType item);

	//�A�C�e���̎�ނ��擾����֐�.
	CItemType GetItemInfo() { return m_ItemType; }





public:
	//�e�A�C�e�����Ƃ̌���.
	//�V�[���h����.
	void ShieldEffect();
	//���xUP����.
	void SpeedUpEffect();
	//�U��UP����.
	void PowerUpEffect();
	//�����͈͑�������.
	void BlastUpEffect();
	//���ˌ���.
	void ReflectionEffect();
	//�����[�h����.
	void ReloadEffect();

protected:
	//�������x.
	float InitialSpeed;
	//�d�͉����x(9.8m/s��2�悾���ǁA�������ɗ�����̂�-��t����).
	float GravitySpeed;
	//�P�t���[��(0.016 : 1/60FPS).
	float Framerate;
	
	//�A�C�e���̎��.
	CItemType m_ItemType;

	//�A�C�e�����ʂ̍\����.
	struct ItemEffect
	{
		bool	m_ShieldFlag = false;		//�V�[���h�𒣂��Ă��邩�ǂ���.
		float	m_Speed;					//�v���C���[�̑��x�ύX�p.
		float	m_Power;					//�v���C���[�̍U���ύX�p.
		float	m_Blast;					//�v���C���[�̔��������ύX�p.
		bool	m_Reflection = false;		//�v���C���[�̔��˕ύX�p.
		float	m_Reload;					//�v���C���[�̃����[�h�Ԋu�ύX�p.
	}m_Item;


};