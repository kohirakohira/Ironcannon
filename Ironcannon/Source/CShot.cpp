#include "CShot.h"

CShot::CShot()
	: m_Shot()
{
}

CShot::~CShot()
{
}

void CShot::Initialize(int id)
{
	for (int i = 0; i < ShotMax; i++)
	{
		m_Shot[i].m_Display = false;
	}
}

void CShot::Update()
{
	for (int i = 0; i < ShotMax; i++)
	{
		if (m_Shot[i].m_Display == true) {
			// �ړ������Ɉړ����x���������킹�����̂����W�ɔ��f
			m_vPosition += m_Shot[i].m_MoveDirection * m_Shot[i].m_MoveSpeed;

			// �����x�ɏd�͂��^�����Ă���
			m_Shot[i].m_Velocity -= m_Shot[i].m_Gravity;
			// �����x��Y��^����
			m_vPosition.y += m_Shot[i].m_Velocity;

			m_Shot[i].m_DisplayTime--;
			if (m_Shot[i].m_DisplayTime < 0) {
				//�����Ȃ����ɒu���Ă���
				m_vPosition = D3DXVECTOR3(0.f, -10.f, 0.f);
				m_Shot[i].m_Display = false;
			}
		}
	}
}

void CShot::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	for (int i = 0; i < ShotMax; i++)
	{
		if (m_Shot[i].m_Display == true) {
			CStaticMeshObject::Draw(View, Proj, Light, Camera);
		}
	}
}

void CShot::Reload(const D3DXVECTOR3& Pos, float RotY)
{
	for (int i = 0; i < ShotMax; i++)
	{
		if (m_Shot[i].m_Display == true) return;

		m_vPosition = Pos;
		m_vRotation.y = RotY;		// �e�̌���(������)���ς���
		m_Shot[i].m_Display = true;
		m_Shot[i].m_Velocity = 0.f;
		m_Shot[i].m_DisplayTime = FPS * 1;


		// Z���x�N�g��
		m_Shot[i].m_MoveDirection = D3DXVECTOR3(0.f, 0.f, 1.f);

		// Y����]�s��
		D3DXMATRIX mRotationY;
		// Y����]�s����쐬
		D3DXMatrixRotationY(
			&mRotationY,	// (out)�s��
			m_vRotation.y);	// �v���C���[��Y�����̉�]�l

		// Y����]�s����g����Z���x�N�g�������W�ϊ�����
		D3DXVec3TransformCoord(
			&m_Shot[i].m_MoveDirection,	// (out)Z���x�N�g��
			&m_Shot[i].m_MoveDirection,	// (in) Z���x�N�g��
			&mRotationY);		// Y����]�s��
	}
}

bool CShot::IsActive() const
{
	for (int i = 0; i < ShotMax; i++)
	{
		if (m_Shot[i].m_Display) return true;
	}
	return false;
}
