#pragma once
#include <iostream>

#include "CCharacter.h"

#include <vector>
#include "CPlayer.h"
#include "CShot.h"
#include "Global.h"
#include "CComPlayer.h"

//������.
#include "CBody.h"
#include "CCannon.h"

class CPlayerManager
	: public CCharacter
{
public:
	CPlayerManager();
	~CPlayerManager();

	void Initialize();
	void AttachMeshesToPlayer(int index, std::shared_ptr<CStaticMesh> body, std::shared_ptr<CStaticMesh> cannon);
	void SetPlayerPosition(int index, const D3DXVECTOR3& pos);
	//������.
	void SetPlayerRotation(int index, const D3DXVECTOR3& rad);
	void Update() override;
	void Draw (D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;
	
	D3DXVECTOR3 GetPosition();
	std::shared_ptr<CPlayer> GetControlPlayer(int index);

	void SwitchActivePlayer();

	//�v���C���[�̈ʒu�Ɖ�]���擾.�����ɂ͊e�v���C���[������
	D3DXVECTOR3 GetPosition(int index)const;
	D3DXVECTOR3 GetRotation(int index)const;

	//�ǔ��̃f�o�b�N
	//���b�N�Ώۂ̃C���f�b�N�X�w��
	void SetLockTargetIndex(int index) { m_LockTargetIndex = index; }



	//������
	//�q�I�u�W�F�N�g�ɊeBody��Cannon��ݒ肵�Ă�����֐�.
	void SetBodyAndCannon(std::shared_ptr<CBody> body, std::shared_ptr<CCannon> cannon);





private:
	//������.
	std::shared_ptr<CBody>					m_pBody;
	std::shared_ptr<CCannon>				m_pCannon;



    std::vector<std::shared_ptr<CPlayer>>	m_pPlayers;
    std::vector<std::unique_ptr<CShot>>		m_pShots;
	int m_ActivePlayerIndex;	// ���ݑ��쒆�̃v���C���[(�f�o�b�O�p)

	int m_LockTargetIndex = -1;	//���b�N����(�f�o�b�N�p)
};


