#include "CCannon.h"
#include "CSoundManager.h"

CCannon::CCannon(int inputID)
	: m_TurnSpeed				( 0.01f )	// ���������肽���ꍇ�̓��W�A���l��ݒ肷�邱��(��ԂŎg����!)
	, m_ShotCoolTime			( 120 )
	, m_ShotInterval			( 120 )
	, m_pCamera					( nullptr )
	, m_pInput					( nullptr )
{
	// ���͎�t�C���X�^���X�̐����ƃZ�b�g
	m_Input = std::make_shared<CInputManager>(inputID);
	if (m_Input) {
		// �e�N���X(CCharacter)�� m_Input �ɂ����L
		CCharacter::m_Input = m_Input;
	}
}

CCannon::~CCannon()
{
}

void CCannon::Update()
{
	if (m_Input)
	{
		m_Input->Update();
	}

	KeyInput();

	CCharacter::Update();
}

void CCannon::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CCharacter::Draw(View, Proj, Light, Camera);
}

void CCannon::SetCannonPosition(const D3DXVECTOR3& Pos)
{
	m_vPosition = Pos;
}

void CCannon::SetInputManager(const std::shared_ptr<CInputManager>& input)
{
	m_pInput = input;
}

// �L�[���͎�t
void CCannon::KeyInput()
{
	// �������ɓ��͌��m
	if (m_Input->GetArrowKeyDirection() == CInputManager::Direction::Left ||
		m_Input->GetRightStickDirection() == CInputManager::Direction::Left)
	{
		m_vRotation.y -= m_TurnSpeed;
	}

	// �E�����ɓ��͌��m
	if (m_Input->GetArrowKeyDirection() == CInputManager::Direction::Right ||
		m_Input->GetRightStickDirection() == CInputManager::Direction::Right)
	{
		m_vRotation.y += m_TurnSpeed;
	}

	// �N�[���^�C�}�[�X�V
	if (m_ShotCoolTime < m_ShotInterval)
	{
		m_ShotCoolTime++;
		m_Shot = false;
	}
	else
	{
		if (m_Input->IsKeyboardRepeat('Z') ||
			m_Input->GetRightTrigger() == CInputManager::Trigger::RightTrigger)
		{
			m_Shot = true;		// �e�𔭎�
			m_ShotCoolTime = 0; // �N�[���_�E���ăX�^�[�g
		}
	}
}

