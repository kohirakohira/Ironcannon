#pragma once

#include "CStaticMesh.h"

/**************************************************
*	�o�E���f�B���O�X�t�B�A�N���X
**/
class CBoundingSphere
{
public:
	CBoundingSphere();
	~CBoundingSphere();

	//���f���ɍ��킹���o�E���f�B���O�X�t�B�A���쐬
	HRESULT CreateSphereForMesh(const CStaticMesh& pMesh);

	//���̋��̂Ƃ̓����蔻��
	bool IsHit(const CBoundingSphere& pBSphere);

	//���S���W���擾����
	const D3DXVECTOR3& GetPosition() const { return m_Position; }
	//���a(����)���擾����
	float GetRadius() const { return m_Radius; }

	//���S���W��ݒ肷��
	void SetPosition(const D3DXVECTOR3& Pos) { m_Position = Pos; }
	//���a(����)��ݒ肷��
	void SetRadius(float Radius) { m_Radius = Radius; }

private:
	D3DXVECTOR3		m_Position;	//���S���W
	float			m_Radius;	//���a(����)
};
