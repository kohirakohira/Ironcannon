#include "CItemBoxManager.h"

CItemBoxManager::CItemBoxManager()
	: m_Item			()
	, m_ItemInfo		()
{
}

CItemBoxManager::~CItemBoxManager()
{
}

void CItemBoxManager::Update()
{
	for (auto& item : m_Item)
	{
		item->Update();
	}
}

void CItemBoxManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	for (auto& item : m_Item)
	{
		item->Draw(View, Proj, Light, Camera);
	}
}

void CItemBoxManager::Create()
{
	//���g������.
	m_Item.clear();

	//�A�C�e���̃C���X�^���X����.
	for (int i = 0; i < ITEM_MAX; i++)
	{
		//�A�C�e���{�b�N�X�̃C���X�^���X����.
		m_Item.push_back(std::make_shared<CItemBox>());
	}
}

void CItemBoxManager::AttachMesh(std::shared_ptr<CStaticMesh> pMesh)
{
	//���b�V���ݒ�.
	for (auto& item : m_Item)
	{
		item->AttachMesh(pMesh);
	}
}

void CItemBoxManager::SetPosition(float x, float y, float z)
{
	for (auto& item : m_Item)
	{
		//���ɂ��炷����.
		x += 2;
		item->SetPosition(x, y, z);
	}
}

void CItemBoxManager::SetRotation(float x, float y, float z)
{
	for (auto& item : m_Item)
	{
		//��]�ݒ�.
		item->SetRotation(x, y, z);
	}
}

void CItemBoxManager::SetScale(float x, float y, float z)
{
	for (auto& item : m_Item)
	{
		//�傫���ݒ�.
		item->SetScale(x, y, z);
	}
}

void CItemBoxManager::SetItemInfo()
{
	for (auto& item : m_Item)
	{
		//���g�����Ԃɐݒ�.
		//�����_���Őݒ�.
		m_ItemInfo = ItemRandom();

		item->SetItemInfo(m_ItemInfo);
	}
}

CItemType CItemBoxManager::ItemRandom()
{
	//static��t����̂́A�������Ă���ƁA�������x���ቺ���邩��A��x�����쐬.
	
	//�V�[�h�l���쐬.
	//����Ⴄ�l�������.
	static std::random_device rd;
	//�����Z���k�E�c�C�X�^�Ƃ��������G���W��������.
	//gen�̓C���X�^���X.
	//rd()�͏����l�ɖ߂�.
	static std::mt19937 gen(rd());

	//�o�����₷�����d�݂Őݒ�.
	//(�����傫���قǏo�₷��).
	//�e�����͏d�݂ł���A���������őz������Ƃ킩��₷������.
	//��F�V�[���h30���A���t���N�V����5���̃`�P�b�g������A���v��35�������A
	//���̂���30���̓V�[���h��(30/35)�A�c��̓��t���N�V����(5/35)�Ƃ�������.
	std::discrete_distribution<> dist({
		20,			// Shield      �� �悭�o��.
		25,			// SpeedUp     �� �悭�o��.
		25,			// PowerUp     �� ��������.
		10,			// BlastUp     �� ������Əo�ɂ���.
		8,			// Reflection  �� �o�ɂ���.
		12			// Reload      �� ����.
		});

	return static_cast<CItemType>(dist(gen));
}
