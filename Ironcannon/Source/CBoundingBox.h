#pragma once

#include <d3dx9.h>
#include "CStaticMesh.h" // �X�^�e�B�b�N���b�V���N���X

/**************************************************
*	�o�E���f�B���O�{�b�N�X�N���X (OBB)
**************************************************/
class CBoundingBox
{
public:
    struct OBB
    {
        D3DXVECTOR3 m_Pos;     // ���S���W
        D3DXVECTOR3 m_Axis[3]; // ���[�J��X, Y, Z���i�P�ʃx�N�g���j
        float       m_Length[3]; // �e�������̔������ix, y, z�j
    };

public:
    CBoundingBox();
    ~CBoundingBox();

    // ���f���ɍ��킹���o�E���f�B���O�{�b�N�X���쐬
    HRESULT CreateBoxForMesh(const CStaticMesh& pMesh);

    // ����OBB�Ƃ̓����蔻��
    bool IsHitOBB(OBB& obb1, OBB& obb2);

    // OBB�̉�]��ݒ�
    void SetRotation(const D3DXMATRIX& matRot);

    // ���݂�OBB���擾
    const OBB& GetOBB() const { return m_OBB; }

private:
    OBB m_OBB; // ���̃I�u�W�F�N�g��OBB
};
