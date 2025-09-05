#include "CPlayerManager.h"


CPlayerManager::CPlayerManager()
	: m_pPlayers()
	, m_ActivePlayerIndex(0)
{
}
//Player��CComPlayer�Ȃ炻�̃|�C���^�ɃL���X�g���ĕԂ�.�����łȂ����nullptr
static inline bool IsCom(const std::shared_ptr<CPlayer>& player) 
{
	return std::dynamic_pointer_cast< const CComPlayer>(player) != nullptr;
}

CPlayerManager::~CPlayerManager()
{
}

//�C���X�^���X����.
void CPlayerManager::Initialize()
{
	//��UCOM�̉�����
	m_pPlayers.clear();
	m_pPlayers.reserve(PLAYER_MAX);

	for (int i = 0; i < PLAYER_MAX; ++i)
	{

		if (i == 0)
		{
			auto player = std::make_shared<CPlayer>();
			player->Initialize(i);
			m_pPlayers.push_back(std::move(player));
		}
		else
		{
			auto com = std::make_shared<CComPlayer>();
			com->Initialize(i);
			m_pPlayers.push_back(std::move(com));
		}

		//// �������R�[�h
		//m_pPlayers.push_back(std::make_shared<CPlayer>());
		//m_pPlayers[i]->Initialize(i);
	}

}

void CPlayerManager::AttachMeshesToPlayer(int index, std::shared_ptr<CStaticMesh> pBody, std::shared_ptr<CStaticMesh> pCannon)
{
	m_pPlayers[index]->AttachMeshse(pBody, pCannon);
}

void CPlayerManager::SetPlayerPosition(int index, const D3DXVECTOR3& pos)
{
	if (index < m_pPlayers.size())
	{
		m_pPlayers[index]->SetTankPosition(pos);
	}
}

void CPlayerManager::SetPlayerRotation(int index, const D3DXVECTOR3& rad)
{
	if (index < m_pPlayers.size())
	{
		m_pPlayers[index]->SetTankRotation(rad);
	}
}

void CPlayerManager::Update()
{
	const int count = static_cast<int>(m_pPlayers.size());
	if (count <= 0)return;

	//����v���C���[���X�V
	if (m_ActivePlayerIndex >= 0 && m_ActivePlayerIndex < count) {
		m_pPlayers[m_ActivePlayerIndex]->Update();
	}

	//��{�^�[�Q�b�g�����߂�
	//�����_��[&]�ŊO���̕ϐ����Q�Ƃł���.->int�߂�l�̂����w��
	auto pickHumanTargetIndex = [&]()->int {
		auto isValidHuman = [&](int idx) {
			return(idx >= 0 && idx < count) && !IsCom(m_pPlayers[idx]);
			};
		if (isValidHuman(m_LockTargetIndex)) return m_LockTargetIndex;
		if (isValidHuman(m_ActivePlayerIndex)) return m_ActivePlayerIndex;
		for (int i = 0; i < count; ++i) {
			if (isValidHuman(i)) return i;
		}
		return -1;	//�v���C���[�����Ȃ�
		};


	//������.
	const int tgtIdx = pickHumanTargetIndex();
	std::shared_ptr<CPlayer> target = (tgtIdx >= 0) ? m_pPlayers[tgtIdx] : nullptr;

	for (int i = 0; i < count; ++i)
	{
		std::shared_ptr<CPlayer> self = m_pPlayers[i];

		if (auto com = std::dynamic_pointer_cast<CComPlayer>(self))
		{
			if (target && !IsCom(target) && target != self) 
			{
				com->SetTarget(target);
			}
			else
			{
				com->ClearTarget();
			}
			com->Update();
		}
	}

}

void CPlayerManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	for (auto& player : m_pPlayers)
	{
		player->Draw(View, Proj, Light, Camera);
	}
}

D3DXVECTOR3 CPlayerManager::GetPosition()
{
	if (m_pPlayers.empty()) return D3DXVECTOR3(0, 0, 0);
	return m_pPlayers[m_ActivePlayerIndex]->GetPosition();
}

//������.
std::shared_ptr<CPlayer> CPlayerManager::GetControlPlayer(int index)
{
	if (index >= 0 && index < (int)m_pPlayers.size()) {
		return m_pPlayers[index];
	}
	return nullptr;
}

//���M���R�[�h.
//std::vector<std::shared_ptr<CPlayer>> CPlayerManager::GetControlPlayer(int index)
//{
//	if (index >= 0 && index < (int)m_pPlayers.size()) {
//		return m_pPlayers[index].get();
//	}
//	return nullptr;
//}

void CPlayerManager::SwitchActivePlayer()
{
	m_ActivePlayerIndex = (m_ActivePlayerIndex + 1) % m_pPlayers.size();
}

D3DXVECTOR3 CPlayerManager::GetPosition(int index) const
{
	if (index >= 0 && index < static_cast<int>(m_pPlayers.size()))
	{
		return m_pPlayers[index]->GetPosition();
	}
	return D3DXVECTOR3(0, 0, 0);
}

D3DXVECTOR3 CPlayerManager::GetRotation(int idx) const
{
	if (idx >= 0 && idx < static_cast<int>(m_pPlayers.size()))
	{
		return m_pPlayers[idx]->GetRotation();
	}
	return D3DXVECTOR3(0, 0, 0);
}

void CPlayerManager::SetBodyAndCannon(std::shared_ptr<CBody> body, std::shared_ptr<CCannon> cannon)
{
	//���̃N���X���Ŏg����悤�ɂ���.
	m_pBody = body;
	m_pCannon = cannon;

	for (auto player : m_pPlayers)
	{
		player->SetCBody(body);
		player->SetCCannon(cannon);
	}
}


