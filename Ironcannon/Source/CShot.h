#pragma once

#include "CStaticMeshObject.h"

/**************************************************
*	�e�N���X
**/
class CShot
	: public CStaticMeshObject
{
public:
	CShot();
	virtual ~CShot() override;

	void Initialize(int id);
	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//�e���Đݒ�
	void Reload(const D3DXVECTOR3& Pos, float RotY);

	void SetDisplay(bool disp) { m_Shot->m_Display = disp; }
	bool IsActive() const;
protected:
	struct Shot
	{
		bool		m_Display = false;			// �\���ؑ�
		D3DXVECTOR3 m_MoveDirection;			// �ړ�����
		float		m_MoveSpeed = 0.005f;		// �ړ����x�@���Ƃ肠����0.2f��ݒ�;		// �ړ����x
		int			m_DisplayTime;				// ��3�b���炢�\������
		float		m_Gravity = 0;			// �e�̏d��
		float		m_Velocity = 0.f;			// �����x
	};

private:
	Shot	m_Shot[ShotMax];
};
