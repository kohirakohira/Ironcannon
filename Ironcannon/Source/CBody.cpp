#include "CBody.h"

CBody::CBody(int inputID)
	: m_TurnSpeed			( 0.01f )	// ���������肽���ꍇ�̓��W�A���l��ݒ肷�邱��(��ԂŎg����!)
	, m_MoveSpeed			( 0.1f )
	, m_MoveState			( enMoveState::Stop )
	, m_pInput				( nullptr )
{
	m_vPosition.y = -0.5f;

	// ���͎�t�C���X�^���X�̐����ƃZ�b�g
	m_Input = std::make_shared<CInputManager>(inputID);
	if (m_Input) {
		// �e�N���X(CCharacter)�� m_Input �ɂ����L
		CCharacter::m_Input = m_Input;
	}
}

CBody::~CBody()
{
}

void CBody::Update()
{
	if (m_Input)
	{
		m_Input->Update();
	}

	KeyInput();		// ���͏���
	RadioControl();	// ��]�E�ړ�����
	CCharacter::Update();
}

void CBody::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CCharacter::Draw(View, Proj, Light, Camera);
}

// ���W�I����
void CBody::RadioControl()
{
	// Z���x�N�g��(Z+�����ւ̒P�ʃx�N�g��)
	// ���傫��(����)��1�̃x�N�g����P�ʃx�N�g���Ƃ���
	D3DXVECTOR3 vecAxisZ(0.f, 0.f, 1.f);

	// Y�����̉�]�s��
	D3DXMATRIX mRotationY;
	// Y����]�s����쐬
	D3DXMatrixRotationY(
		&mRotationY,		// (out)�s��
		m_vRotation.y);		// �v���C���[��Y�����̉�]�l

	// Y����]�s����g����Z���x�N�g�������W�ω�����
	D3DXVec3TransformCoord(
		&vecAxisZ,		// (out)Z���x�N�g��
		&vecAxisZ,		// (in)Z���x�N�g��
		&mRotationY);	//  Y����]�s��

	// �ړ���Ԃɂ���ď����𕪂���
	switch (m_MoveState)
	{
	case enMoveState::Forward: 	// �O�i
		m_vPosition += vecAxisZ * m_MoveSpeed;
		break;
	case enMoveState::Backward: 	// ���
		m_vPosition -= vecAxisZ * m_MoveSpeed;
		break;
	default:
		break;
	}
	// ��L�̈ړ��������I���Β�~��Ԃɂ��Ă���
	m_MoveState = enMoveState::Stop;
}

void CBody::SetInputManager(const std::shared_ptr<CInputManager>& input)
{
	m_pInput = input;
}

void CBody::KeyInput()
{
	// ���͂�������Ώ������Ȃ�
	if (!m_Input) return;

	//------------------------------------------------
	// ���̓`�F�b�N
	//------------------------------------------------

	// ������̓��͌��m
	if (m_Input->GetWASDKeyDirection() == CInputManager::Direction::Up ||
		m_Input->GetLeftStickDirection() == CInputManager::Direction::Up)
	{
		m_MoveState = enMoveState::Forward;
	}

	// ��������̓��͌��m
	if (m_Input->GetWASDKeyDirection() == CInputManager::Direction::UpLeft ||
		m_Input->GetLeftStickDirection() == CInputManager::Direction::UpLeft)
	{
		m_vRotation.y -= m_TurnSpeed;
		m_MoveState = enMoveState::Forward;
	}

	// �E������̓��͌��m
	if (m_Input->GetWASDKeyDirection() == CInputManager::Direction::UpRight ||
		m_Input->GetLeftStickDirection() == CInputManager::Direction::UpRight)
	{
		m_vRotation.y += m_TurnSpeed;
		m_MoveState = enMoveState::Forward;
	}

	// �������̓��͌��m
	if (m_Input->GetWASDKeyDirection() == CInputManager::Direction::Down ||
		m_Input->GetLeftStickDirection() == CInputManager::Direction::Down)
	{
		m_MoveState = enMoveState::Backward;
	}

	// ���������̓��͌��m
	if (m_Input->GetWASDKeyDirection() == CInputManager::Direction::DownLeft ||
		m_Input->GetLeftStickDirection() == CInputManager::Direction::DownLeft)
	{
		m_vRotation.y -= m_TurnSpeed;
		m_MoveState = enMoveState::Backward;
	}

	// �E�������̓��͌��m
	if (m_Input->GetWASDKeyDirection() == CInputManager::Direction::DownRight ||
		m_Input->GetLeftStickDirection() == CInputManager::Direction::DownRight)
	{
		m_vRotation.y += m_TurnSpeed;
		m_MoveState = enMoveState::Backward;
	}

	// �������ɓ��͌��m
	if (m_Input->GetWASDKeyDirection() == CInputManager::Direction::Left ||
		m_Input->GetLeftStickDirection() == CInputManager::Direction::Left)
	{
		m_vRotation.y -= m_TurnSpeed;
	}

	// �E�����ɓ��͌��m
	if (m_Input->GetWASDKeyDirection() == CInputManager::Direction::Right ||
		m_Input->GetLeftStickDirection() == CInputManager::Direction::Right)
	{
		m_vRotation.y += m_TurnSpeed;
	}
	//------------------------------------------------
	//------------------------------------------------
}

