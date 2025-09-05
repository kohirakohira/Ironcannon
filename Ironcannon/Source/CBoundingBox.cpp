#include "CBoundingBox.h"

CBoundingBox::CBoundingBox()
{
}

CBoundingBox::~CBoundingBox()
{
}

HRESULT CBoundingBox::CreateBoxForMesh(const CStaticMesh& pMesh)
{
    LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
    void* pVertices = nullptr;
    D3DXVECTOR3 vMin, vMax;

    if (FAILED(pMesh.GetMesh()->GetVertexBuffer(&pVB)))
        return E_FAIL;
    if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
    {
        SAFE_RELEASE(pVB);
        return E_FAIL;
    }

    // AABB���܂��v�Z����i�ŏ��ƍő�j
    D3DXComputeBoundingBox(
        static_cast<D3DXVECTOR3*>(pVertices),
        pMesh.GetMesh()->GetNumVertices(),
        D3DXGetFVFVertexSize(pMesh.GetMesh()->GetFVF()),
        &vMin,
        &vMax);

    pVB->Unlock();
    SAFE_RELEASE(pVB);

    // ���S
    m_OBB.m_Pos = (vMin + vMax) * 0.5f;

    // ���F�ŏ��̓��[���h���W���ƈ�v
    m_OBB.m_Axis[0] = D3DXVECTOR3(1, 0, 0);  // X��
    m_OBB.m_Axis[1] = D3DXVECTOR3(0, 1, 0);  // Y��
    m_OBB.m_Axis[2] = D3DXVECTOR3(0, 0, 1);  // Z��

    // �e���̒����i�����j
    D3DXVECTOR3 halfSize = (vMax - vMin) * 0.5f;
    m_OBB.m_Length[0] = halfSize.x;
    m_OBB.m_Length[1] = halfSize.y;
    m_OBB.m_Length[2] = halfSize.z;

    return S_OK;
}

// 2��OBB�̏Փ˔���iSeparating Axis Theorem�Ɋ�Â��j
bool CBoundingBox::IsHitOBB(OBB& obb1, OBB& obb2)
{
    // obb1�̊e�������i���K���x�N�g���j�Ƃ��̒������g���Ď��x�N�g�����v�Z
    D3DXVECTOR3 NAe1 = obb1.m_Axis[0], Ae1 = NAe1 * obb1.m_Length[0];
    D3DXVECTOR3 NAe2 = obb1.m_Axis[1], Ae2 = NAe2 * obb1.m_Length[1];
    D3DXVECTOR3 NAe3 = obb1.m_Axis[2], Ae3 = NAe3 * obb1.m_Length[2];

    // obb2�̊e�������i���K���x�N�g���j�Ƃ��̒������g���Ď��x�N�g�����v�Z
    D3DXVECTOR3 NBe1 = obb2.m_Axis[0], Be1 = NBe1 * obb2.m_Length[0];
    D3DXVECTOR3 NBe2 = obb2.m_Axis[1], Be2 = NBe2 * obb2.m_Length[1];
    D3DXVECTOR3 NBe3 = obb2.m_Axis[2], Be3 = NBe3 * obb2.m_Length[2];

    // OBB���m�̒��S�_�Ԃ̃x�N�g���i���S�ԋ����j
    D3DXVECTOR3 Interval = obb1.m_Pos - obb2.m_Pos;

    // �������ɓ��e���ꂽ�Ƃ��́u���v���v�Z���郉���_��
    auto LenSegOnSeparateAxis = [](const D3DXVECTOR3& Sep, const D3DXVECTOR3& e1, const D3DXVECTOR3& e2, const D3DXVECTOR3& e3)
    {
        // ���ꂼ��̎��x�N�g���𕪗����ɓ��e���A��Βl�̍��v�����i�X�J���[���j
        float r1 = fabs(D3DXVec3Dot(&Sep, &e1));
        float r2 = fabs(D3DXVec3Dot(&Sep, &e2));
        float r3 = fabs(D3DXVec3Dot(&Sep, &e3));
        return r1 + r2 + r3;  // ���v�����̃I�u�W�F�N�g�̕�������̔����ɂȂ�
    };

    float rA, rB, L;

    // �C�ӂ̕������ɑ΂��ďՓ˂��Ă��Ȃ����m�F���郉���_��
    auto checkAxis = [&](const D3DXVECTOR3& axis) -> bool
    {
        // obb1�𕪗����ɓ��e�����Ƃ��̔���
        rA = LenSegOnSeparateAxis(axis, Ae1, Ae2, Ae3);
        // obb2�𕪗����ɓ��e�����Ƃ��̔���
        rB = LenSegOnSeparateAxis(axis, Be1, Be2, Be3);
        // ���S�ԋ����𕪗����ɓ��e�����X�J���[����
        L = fabs(D3DXVec3Dot(&Interval, &axis));
        // L > rA + rB �ł���Ε����������� �� �Փ˂��Ă��Ȃ�
        return L > rA + rB;
    };

    // ����Ɏg��15�̎��i3+3+9�j���i�[����z��
    D3DXVECTOR3 axes[] = {
        NAe1, NAe2, NAe3,    // obb1�̃��[�J�����i3�j
        NBe1, NBe2, NBe3,    // obb2�̃��[�J�����i3�j
        D3DXVECTOR3(), D3DXVECTOR3(), D3DXVECTOR3(),  // �N���X���i�ȉ��A9�j
        D3DXVECTOR3(), D3DXVECTOR3(), D3DXVECTOR3(),
        D3DXVECTOR3(), D3DXVECTOR3(), D3DXVECTOR3()
    };

    // obb1��obb2�̎��x�N�g���̊O�ρi�N���X�ρj���v�Z
    // �e���̑g�ݍ��킹�ɑ΂��Ē����x�N�g���𐶐�
    D3DXVec3Cross(&axes[6], &NAe1, &NBe1);
    D3DXVec3Cross(&axes[7], &NAe1, &NBe2);
    D3DXVec3Cross(&axes[8], &NAe1, &NBe3);
    D3DXVec3Cross(&axes[9], &NAe2, &NBe1);
    D3DXVec3Cross(&axes[10], &NAe2, &NBe2);
    D3DXVec3Cross(&axes[11], &NAe2, &NBe3);
    D3DXVec3Cross(&axes[12], &NAe3, &NBe1);
    D3DXVec3Cross(&axes[13], &NAe3, &NBe2);
    D3DXVec3Cross(&axes[14], &NAe3, &NBe3);

    // 15�����ׂĂɂ��ĕ����������݂��邩���`�F�b�N
    for (int i = 0; i < 15; ++i)
    {
        // �����Ȏ��i�������قڃ[���j�̓X�L�b�v�i�O�ς�0�x�N�g���̏ꍇ�j
        if (D3DXVec3LengthSq(&axes[i]) < 1e-6f) continue;

        // ���𐳋K���i�P�ʃx�N�g�����j
        D3DXVec3Normalize(&axes[i], &axes[i]);

        // ���̎��ŕ����ł���ΏՓ˂��Ă��Ȃ��Ɣ���
        if (checkAxis(axes[i]))
            return false;
    }

    // ���ׂĂ̎��ŕ����ł��Ȃ����� �� �Փ˂��Ă���
    return true;
}

void CBoundingBox::SetRotation(const D3DXMATRIX& matRot)
{
    for (int i = 0; i < 3; i++)
    {
		D3DXVec3TransformNormal(&m_OBB.m_Axis[i], &m_OBB.m_Axis[i], &matRot);
    }
}
