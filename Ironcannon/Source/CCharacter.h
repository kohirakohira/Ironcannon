#pragma once
#include <iostream>

#include "CStaticMeshObject.h" // �X�^�e�B�b�N���b�V���I�u�W�F�N�g���p��
#include <memory>

/**************************************************
*   �L�����N�^�[�N���X
**/

// �O���錾
class CInputManager;		// ���͎�t�N���X.

class CCharacter
	: public CStaticMeshObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//�e���΂��������m�F
	bool IsShot() const { return m_Shot; }

	//Y�������֐L�΂������C���擾.
	std::shared_ptr<RAY> GetRayY() const { return m_pRayY; }

	// ���͎�t���擾.
	std::shared_ptr<CInputManager> GetInput() const
	{
		return m_Input;
	}
	
	void SetInput(const std::shared_ptr<CInputManager> input) { m_Input = input; }

protected:
	bool	m_Shot;		//�e���΂��t���O

	std::shared_ptr<RAY>	m_pRayY;	//Y�����֐L�΂������C.

	std::shared_ptr<CInputManager> m_Input;	// ���͎�t�N���X.
};