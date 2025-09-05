#pragma once
#include <iostream>
#include <vector>
#include <random>

#include "CItemBox.h"		//�A�C�e���{�b�N�X.
#include "ItemType.h"		//�A�C�e���̎��.
#include "Global.h"

//�A�C�e���{�b�N�X�}�l�[�W���[.
class CItemBoxManager
{
public:
	CItemBoxManager();
	~CItemBoxManager();

	//����֐�.
	void Update();
	//�`��֐�.
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera);
	//�C���X�^���X����(����).
	void Create();
	//���b�V���̐ݒ�.
	void AttachMesh(std::shared_ptr<CStaticMesh> pMesh);


	//�ʒu�ݒ�.
	void SetPosition(float x, float y, float z);
	//��]�ݒ�.
	void SetRotation(float x, float y, float z);
	//�傫���ݒ�.
	void SetScale(float x, float y, float z);


	//�A�C�e���̒��g��ݒ肵�Ă�����.
	void SetItemInfo();

	//�A�C�e���̒��g�������_����.
	CItemType ItemRandom();

public:
	//�A�C�e���{�b�N�X.
	std::vector<std::shared_ptr<CItemBox>>	m_Item;
	//�A�C�e�����b�V��.
	std::shared_ptr<CStaticMesh>			m_ItemMesh;

	//�A�C�e���̎��.
	CItemType m_ItemInfo;

private:

};