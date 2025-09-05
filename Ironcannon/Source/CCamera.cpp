#include "CCamera.h"
#include <d3dx9math.h>	//�J�����̍��W�v�Z�p.
#include <d3d9.h>		//�`�悷��p.
#include <string>

CCamera::CCamera()
	: m_TargetPos	(0.f, 0.f, 0.f)
	, m_TargetRotY	(0.f)
	, m_Position	(0.f,2.f,0.f)	
	, m_Distance	(4.f)
	, m_HeightOffset(2.0f)
	, m_LookAt(0.0f, 2.0f, 0.0f)
	, m_Up(0.0f, 1.0f, 0.0f)


{
	//�J�������W.
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	//���C�g���
	m_Light.vDirection = D3DXVECTOR3(1.5f, 1.f, -1.f);	//���C�g����

	//Update();
}

//Update�ł͂Ȃ����ƃR�[�h�̎O�l�̃J�������x�[�X�ɂ���
void CCamera::Update()
{
	//��]����Z�����̃I�t�Z�b�g�����߂�
	D3DXVECTOR3 backward(0.f, 0.f, 1.f);
	D3DXMATRIX rotY;
	D3DXMatrixRotationY(&rotY, m_TargetRotY);
	//�^�[�Q�b�g���猩���J�����̈ʒu
	D3DXVec3TransformCoord(&backward, &backward, &rotY);

	//�v���C���[�̈ʒu���炍�������������������ꏊ�ɃJ����������
	m_Position = m_TargetPos - (backward * m_Distance);
	//�����낵���_�ɂ���
	m_Position.y += m_HeightOffset;

	//�����̐�.�^�[�Q�b�g�ʒu+�����O������悤�ɂ���
	D3DXVECTOR3 forward = backward * 3.0f;
	m_LookAt = m_TargetPos + forward;
	m_LookAt.y += 0.5f;	//�����̍���������

	//�r���[�s����v�Z
	D3DXMatrixLookAtLH(&m_mView, &m_Position, &m_LookAt, &m_Up);

	//�v���W�F�N�V�����������ōX�V���Ă���
	float fovY = D3DXToRadian(45.0f);
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	D3DXMatrixPerspectiveFovLH(&m_mProj, fovY, aspect, 0.1f, 100.0f);


	//SetCamera.Draw���Ŏg���\���̂�ǔ����ʂɂ��킹�čX�V
	m_Camera.vPosition = m_Position;
	m_Camera.vLook = m_LookAt;

}


void CCamera::Draw()
{
	//SetCamera();
	//Projection();
}

void CCamera::Init()
{

}

void CCamera::SetCamera()
{
	//�r���[�̐ݒ�.
	D3DXVECTOR3 cam_pos = m_Camera.vPosition;
	D3DXVECTOR3 cam_look = m_Camera.vLook;
	D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);	//����i�x�N�g���j.

	//�r���[�i�J�����j�ϊ�.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)�r���[�v�Z����.
		&cam_pos, &cam_look, &vUpVec);
}

void CCamera::SetCameraPos(float x, float y, float z)
{
	//�ʒu�̐ݒ�.
	m_Camera.vPosition = { x, y, z };
}

void CCamera::SetLightPos(float x, float y, float z)
{
	//�ʒu�̐ݒ�.
	m_Light.Position = { x, y, z };	//���C�g����
}

void CCamera::SetLightRot(float x, float y, float z)
{
	m_Light.vDirection = { x, y, z };
}

void CCamera::Projection()
{
	//y�����̎���p�B���l��傫�������王�삪�����Ȃ�.
	float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//���W�A���l.
	//�A�X�y�N�g�i���������j.
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	float near_z = 0.3f;
	float far_z = 300.0f;

	//�v���W�F�N�V�����i�ˉe�j�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,	//(out)�v���W�F�N�V�����v�Z����.
		fov_y,		//����p�iFOV�FField of View�j.
		aspect,		//�A�X�y�N�g.
		near_z,		//�߂��r���[���ʂ�z�l.
		far_z);	//�����r���[���ʂ�z�l.
}

//�O�l�̃J����
void CCamera::ThirdPersonCamera(
	CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY)
{
	//Z���x�N�g���iZ+�����̒P�ʃx�N�g���j
	D3DXVECTOR3 vecAxisZ(0.f, 0.f, 1.f);

	//Y�����̉�]�s��
	D3DXMATRIX mRotationY;
	//Y����]�s����쐬
	D3DXMatrixRotationY(
		&mRotationY,	//(out)�s��
		TargetRotY);	//�Ώۂ�Y�����̉�]�l

	//Y����]�s����g����Z���x�N�g�������W�ϊ�����
	D3DXVec3TransformCoord(
		&vecAxisZ,		//(out)Z���x�N�g��
		&vecAxisZ,		//(in)Z���x�N�g��
		&mRotationY);	//Y����]�s��

	//�J�����̈ʒu�A�����ʒu��Ώۂɂ��낦��
	pCamera->vPosition = TargetPos;
	pCamera->vLook = TargetPos;

	//�J�����̈ʒu�A�����ʒu��Z���x�N�g����p���Ē���
	pCamera->vPosition -= vecAxisZ * 4.f;	//�Ώۂ̔w����
	pCamera->vLook += vecAxisZ * 3.f;	//�Ώۂ�����Ō�������

	//�J�����̈ʒu�A�����ʒu�̍��������ꂼ�������
	pCamera->vPosition.y += 2.f;
	pCamera->vLook.y += 0.5f;
}

void CCamera::SetTargetPos(const D3DXVECTOR3& pos)
{
	m_TargetPos = pos;
}

void CCamera::SetTargetRotY(float rotY)
{
	m_TargetRotY = rotY;
}

void CCamera::FreeMove()
{
	//�J�������W�̃f�o�b�N�R�}���h.
	float add_value = 0.1f;
	if (GetAsyncKeyState('G') & 0x8000) {
		m_Camera.vPosition.y -= add_value;
	}
	if (GetAsyncKeyState('T') & 0x8000) {
		m_Camera.vPosition.y += add_value;
	}
	if (GetAsyncKeyState('H') & 0x8000) {
		m_Camera.vPosition.x -= add_value;
	}
	if (GetAsyncKeyState('F') & 0x8000) {
		m_Camera.vPosition.x += add_value;
	}
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_Camera.vPosition.z += add_value;
	}
	if (GetAsyncKeyState('E') & 0x8000) {
		m_Camera.vPosition.z -= add_value;
	}
}
