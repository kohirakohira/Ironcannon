#include "CPlayer.h"

CPlayer::CPlayer()
	: m_pBody	( nullptr )
	, m_pCannon	( nullptr )
	, m_Hp		( 2 )
	, m_PlayerID()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(int id)
{
	m_PlayerID = id;

	//�C���X�^���X�𐶐�
	m_pBody = std::make_shared<CBody>(id);
	m_pCannon = std::make_shared<CCannon>(id);
}

void CPlayer::AttachMeshse(std::shared_ptr<CStaticMesh> pBody, std::shared_ptr<CStaticMesh> pCannon)
{
	m_pBody->AttachMesh(pBody);
	m_pCannon->AttachMesh(pCannon);
}

void CPlayer::SetTankPosition(const D3DXVECTOR3& pos)
{
	m_pBody->SetPosition(pos);		// �ԑ̍��W�w��
	m_pCannon->SetPosition(pos);	// �C�����W�w��
}

void CPlayer::SetTankRotation(const D3DXVECTOR3& pos)
{
	m_pBody->SetRotation(pos);		// �ԑ̉�]�w��
	m_pCannon->SetRotation(pos);	// �C����]�w��
}
   
void CPlayer::Update()
{
	m_pBody->Update();

	// �C���̈ʒu���X�V
	D3DXVECTOR3 pos = m_pBody->GetPosition();
	pos.y += 0.3f; // �C���̍��W�����킹��
	m_pCannon->SetPosition(pos); // �C�����W�X�V

	m_pCannon->Update();
}

void CPlayer::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pBody->Draw(View, Proj, Light, Camera);
	m_pCannon->Draw(View, Proj, Light, Camera);
}

D3DXVECTOR3 CPlayer::GetCannonPosition() const
{
	if (m_pCannon)
	{
		return m_pCannon->GetPosition();
	}
	else
	{
		return GetPosition();
	}
}

float CPlayer::GetCannonYaw() const
{
	if (m_pCannon)
	{
		return m_pCannon->GetRotation().y;
	}
	else
	{
		return GetRotation().y;
	}
}

D3DXVECTOR3 CPlayer::GetPosition() const
{
	if (m_pBody)return m_pBody->GetPosition();	//���body�̎��ʒu��Ԃ�
	return CCharacter::GetPosition();
}

D3DXVECTOR3 CPlayer::GetRotation() const
{
	if (m_pBody)return m_pBody->GetPosition();
	return CCharacter::GetRotation();
}


