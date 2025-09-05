#pragma once
#include "CCharacter.h" // �L�����N�^�[�N���X�p��
#include "CCamera.h"

#include "CInputManager.h" // ���͎�t�N���X

/**************************************************
*	�C���N���X.
**/
class CCannon
	: public CCharacter	//�L�����N�^�[�N���X���p��.
{
public:
	CCannon(int inputID);
	virtual ~CCannon() override;

	virtual void Update() override;
	virtual void Draw(
		D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void SetCannonPosition(const D3DXVECTOR3& Pos);

	D3DXVECTOR3 GetCannonPosition() const { return m_vPosition; }

	// ���̓N���X��ݒ�
	void SetInputManager(const std::shared_ptr<CInputManager>& input);

private:
	// �L�[���͎�t
	void KeyInput();

protected:
	float		m_TurnSpeed;	// ��]���x

	int			m_ShotCoolTime; // �V���b�g�̃N�[���^�C��
	const int	m_ShotInterval; // �V���b�g�̃C���^�[�o��
	CCamera*	m_pCamera;	

private:
	std::shared_ptr<CInputManager> m_pInput;
};