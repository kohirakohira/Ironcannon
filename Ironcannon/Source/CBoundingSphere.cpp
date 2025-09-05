#include "CBoundingSphere.h"

CBoundingSphere::CBoundingSphere()
	: m_Position	()
	, m_Radius		()
{
}

CBoundingSphere::~CBoundingSphere()
{
}

//���f���ɍ��킹���o�E���f�B���O�X�t�B�A���쐬
HRESULT CBoundingSphere::CreateSphereForMesh(const CStaticMesh& pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;	//���_�o�b�t�@
	void* pVertices = nullptr;				//���_
	D3DXVECTOR3 Center(0.f, 0.f, 0.f);		//���S���W
	float Radius = 0.f;						//���a

	//���_�o�b�t�@���擾
	if (FAILED(
		pMesh.GetMesh()->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}

	//���b�V���̒��_�o�b�t�@�����b�N����
	if (FAILED(
		pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>(pVertices),
		pMesh.GetMesh()->GetNumVertices(),					//���_�̐�
		D3DXGetFVFVertexSize(pMesh.GetMesh()->GetFVF()),	//���_�̏��
		&Center,											//(out)���S���W
		&Radius);											//(out)���a

	//���b�V���̒��_�o�b�t�@���A�����b�N����
	if (pVB != nullptr) {
		pVB->Unlock();
		SAFE_RELEASE(pVB);
	}

	//���S���W�Ɣ��a�̐ݒ�
	m_Position = Center;
	m_Radius = Radius;

	return S_OK;
}

//���̋��̂Ƃ̓����蔻��
bool CBoundingSphere::IsHit(const CBoundingSphere& pBSphere)
{
	//�Q�̋��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = m_Position - pBSphere.GetPosition();
	//��L�̃x�N�g�����璷���ɕϊ�
	float Length = D3DXVec3Length( &vLength );

	//�u�Q�̋��̂̋����v���u�Q�̋��̂̂��ꂼ��̔��a�𑫂������́v���A
	//�������Ƃ������Ƃ́A���̓��m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������
	if (Length <= m_Radius + pBSphere.GetRadius())
	{
		return true;	//�Փ˂��Ă���
	}
	return false;	//�Փ˂��Ă��Ȃ�
}
