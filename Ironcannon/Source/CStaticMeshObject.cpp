#include "CStaticMeshObject.h"

CStaticMeshObject::CStaticMeshObject()
	: m_pMesh			( nullptr )
	, m_pBSphere		( nullptr )
{
	m_pBSphere = std::make_shared<CBoundingSphere>();
}

CStaticMeshObject::~CStaticMeshObject()
{
	DetachMesh();
}

void CStaticMeshObject::Update()
{
	if( m_pMesh == nullptr ){
		return;
	}
}

void CStaticMeshObject::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	if( m_pMesh == nullptr ){
		return;
	}

	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
	m_pMesh->SetPosition( m_vPosition );
	m_pMesh->SetRotation( m_vRotation );
	m_pMesh->SetScale( m_vScale );

	//�����_�����O.
	m_pMesh->Render( View, Proj, Light, Camera.vPosition );
}

//���C�ƃ��b�V���̓����蔻��
bool CStaticMeshObject::IsHitForRay(
	const RAY& pRay,
	float* pDistance,
	D3DXVECTOR3* pIntersect)
{
	D3DXVECTOR3 vAxis;		//���x�N�g��
	D3DXMATRIX	mRotationY;	//Y����]�s��

	//Y����]�s����쐬
	D3DXMatrixRotationY(&mRotationY, pRay.RotationY);
	//���x�N�g�������݂̉�]��Ԃɕϊ�����
	D3DXVec3TransformCoord(&vAxis, &pRay.Axis, &mRotationY);

	//���C�̎n�_�ƏI�_
	D3DXVECTOR3 StartPoint, EndPoint;
	StartPoint	= pRay.Position;	//���C�̎n�_��ݒ�
	EndPoint	= pRay.Position + (vAxis * pRay.Length);	//���C�̏I�_��ݒ�

	//���C�𓖂Ă������b�V�����ړ����Ă���ꍇ�ł��A
	//�Ώۂ�World�s��̋t�s���p����ΐ��������C��������
	D3DXMATRIX mWorld, mInverseWorld;
	D3DXMATRIX mTran;
	//�ړ�����
	D3DXMatrixTranslation(
		&mTran, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	//��]����
	//�����̍s��v�Z�́uCStaticMesh::Render()�֐��v�Ɠ����ɂ���K�v����
	D3DXMATRIX mRot, mYaw, mPitch, mRoll;
	//Y����]�s��쐬
	D3DXMatrixRotationY(&mYaw, m_vRotation.y);
	//X����]�s��쐬
	D3DXMatrixRotationX(&mPitch, m_vRotation.x);
	//Z����]�s��쐬
	D3DXMatrixRotationZ(&mRoll, m_vRotation.z);
	//��]�s����쐬
	mRot = mYaw * mPitch * mRoll;

	//�g�k����
	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, m_vScale.x, m_vScale.y, m_vScale.z);

	//���[���h�s��v�Z
	//�g�k�~��]�~�ړ��@�����Ԃ��ƂĂ���؁I�I
	mWorld = mScale * mRot * mTran;

	//�t�s������߂�.
	D3DXMatrixInverse(&mInverseWorld, nullptr, &mWorld);
	//���C�̎n�_�A�I�_�ɔ��f.
	D3DXVec3TransformCoord(&StartPoint, &StartPoint, &mInverseWorld);
	D3DXVec3TransformCoord(&EndPoint, &EndPoint, &mInverseWorld);

	//�����ƒ���(�傫��)�����߂�.
	D3DXVECTOR3 vDirection = EndPoint - StartPoint;

	BOOL bHit = FALSE;		//�����t���O.
	DWORD dwIndex = 0;		//�C���f�b�N�X�ԍ�.
	D3DXVECTOR3 Vertex[3];	//���_���W.
	FLOAT U = 0, V = 0;		//�d�S�q�b�g���W.

	//���b�V���ƃ��C�̌����𒲂ׂ�.
	D3DXIntersect(
		m_pMesh->GetMeshForRay(),	//�Ώۃ��b�V��.
		&StartPoint,				//���C�̎n�_.
		&vDirection,				//���C�̌����ƒ���(�傫��).
		&bHit,						//(out)���茋��.
		&dwIndex,	//(out)bHit��TRUE�̎��A���C�̎n�_�ɍł��߂��ʂ̃C���f�b�N�X�l�ւ̃|�C���^.
		&U, &V,						//(out)�d�S�q�b�g���W.
		pDistance,					//(out)���b�V���Ƃ̋���.
		nullptr, nullptr );

	//�����ɐL�т郌�C�̂ǂ����Ń��b�V�����������Ă�����.
	if (bHit == TRUE)
	{
		//���������Ƃ�.
		FindVerticesOnPoly(
			m_pMesh->GetMeshForRay(), dwIndex, Vertex );

		//�d�S���W�����_���Z�o.
		//���[�J����_�� v0 + U*(v1 - v0) + V*(v2 - v0) �ŋ��܂�.
		*pIntersect = Vertex[0] + U * (Vertex[1] - Vertex[0]) + V * (Vertex[2] - Vertex[0]);

		//���f���f�[�^���u�g�k�v�u��]�v�u�ړ��v���Ă���΍s�񂪕K�v.
		D3DXVec3TransformCoord(pIntersect, pIntersect, &mWorld);

		//EndPoint���猩��������1.f��菬������Γ������Ă���.
		if (*pDistance < 1.f)
		{
			return true;	//�������Ă���.
		}
	}
	return false;	//�O��Ă���.
}

//�����ʒu�̃|���S���̒��A��������.
HRESULT CStaticMeshObject::FindVerticesOnPoly(
	LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pVertices)
{
	//���_���Ƃ̃o�C�g�����擾.
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	//���_�����擾.
	DWORD dwVertexAmt = pMesh->GetNumVertices();
	//�ʐ����擾.
	DWORD dwPolyAmt = pMesh->GetNumFaces();

	WORD* pwPoly = nullptr;

	//�C���f�b�N�X�o�b�t�@�����b�N(�ǂݍ��݃��[�h).
	pMesh->LockIndexBuffer(
		D3DLOCK_READONLY,
		reinterpret_cast<VOID**>(&pwPoly));

	BYTE* pbVertices = nullptr;		//���_(�o�C�g�^).
	FLOAT* pfVertices = nullptr;	//���_(FLOAT�^).
	LPDIRECT3DVERTEXBUFFER9 VB = nullptr;	//���_�o�b�t�@.

	//���_���̎擾.
	pMesh->GetVertexBuffer(&VB);

	//���_�o�b�t�@�̃��b�N.
	if (SUCCEEDED(
		VB->Lock(0, 0, reinterpret_cast<VOID**>(&pbVertices), 0)))
	{
		//�|���S���̒��_1�ڂ��擾.
		pfVertices = reinterpret_cast<FLOAT*>(&pbVertices[dwStride * pwPoly[dwPolyIndex * 3]]);
		pVertices[0].x = pfVertices[0];
		pVertices[0].y = pfVertices[1];
		pVertices[0].z = pfVertices[2];
		//�|���S���̒��_2�ڂ��擾.
		pfVertices = reinterpret_cast<FLOAT*>(&pbVertices[dwStride * pwPoly[dwPolyIndex * 3 + 1]]);
		pVertices[1].x = pfVertices[0];
		pVertices[1].y = pfVertices[1];
		pVertices[1].z = pfVertices[2];
		//�|���S���̒��_3�ڂ��擾.
		pfVertices = reinterpret_cast<FLOAT*>(&pbVertices[dwStride * pwPoly[dwPolyIndex * 3 + 2]]);
		pVertices[2].x = pfVertices[0];
		pVertices[2].y = pfVertices[1];
		pVertices[2].z = pfVertices[2];

		pMesh->UnlockIndexBuffer();	//���b�N����.
		VB->Unlock();	//���b�N����.
	}
	VB->Release();	//�s�v�ɂȂ����̂ŉ��.

	return S_OK;
}
