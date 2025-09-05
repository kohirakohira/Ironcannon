#pragma once
#include <d3dx9.h>
#include <iostream>
#include "CDirectX11.h"

class CCamera
{
public:
	CCamera();
	~CCamera() = default;	//���ʂȏ����͂Ȃ��̂Ńf�t�H���g�ɂ��Ă���

	void Update();	//�A�b�v�f�[�g����U�O�l�̃J�����Ƃ��Ďg��
	void Draw();
	void Init();
	////�J�����֐�.
	void SetCamera();
	//�J�����̈ʒu�ݒ�.
	void SetCameraPos(float x, float y, float z);
	//���C�g�̈ʒu�ݒ�.
	void SetLightPos(float x, float y, float z);
	//���C�g�̉�]�ݒ�.
	void SetLightRot(float x, float y, float z);

	//�v���W�F�N�V�����֐�.
	void Projection();

	//�O�l�̃J����
	void ThirdPersonCamera(
		CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY);

	//�r���[�s��̎擾
	D3DXMATRIX GetViewMatrix() const { return m_mView; }

	//�^�[�Q�b�g�ʒu�Ɖ�]�̐ݒ�
	void SetTargetPos(const D3DXVECTOR3& pos);
	void SetTargetRotY(float rotY);

	D3DXVECTOR3& GetCameraPosition() { return m_Camera.vPosition; }
	
	D3DXVECTOR3& GetLookPosition() { return m_Camera.vLook; }

public:
	//���R�ړ�.
	void FreeMove();



public:
	//�\���̐ݒ�ϐ�.
	CAMERA			m_Camera;
	LIGHT			m_Light;
	//�s��.
	D3DXMATRIX		m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX		m_mProj;	//�ˉe�i�v���W�F�N�V�����j�s��.
private:
	D3DXVECTOR3		m_TargetPos;		//�^�[�Q�b�g�̈ʒu
	float			m_TargetRotY;		//�^�[�Q�b�g��Y����]
	D3DXVECTOR3		m_Position;			//�J�����̈ʒu
	float			m_Distance;			//�J�����ƃ^�[�Q�b�g�̋���
	float			m_HeightOffset;		//�^�[�Q�b�g����̍���
	D3DXVECTOR3		m_Up;				//�����
	D3DXVECTOR3		m_LookAt;			//�����_



};