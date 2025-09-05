#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//���C�\����
struct RAY
{
	D3DXVECTOR3	Axis;		//��
	D3DXVECTOR3	Position;	//�ʒu
	float		Length;		//����
	float		RotationY;	//Y����]

	RAY() : Axis(), Position(), Length(), RotationY() {}
};

/**************************************************
*	���C�i�����j�`��N���X.
**/
class CRay
{
public:
	//======================================
	//	�\����.
	//======================================
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.	
		D3DXVECTOR4	vColor;		//�J���[�iRGBA�̌^�ɍ��킹��j.
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//���_���W.
	};

public:
	CRay();		//�R���X�g���N�^.
	~CRay();	//�f�X�g���N�^.

	//������.
	HRESULT Init(RAY& pRay);

	//���.
	void Release();

	//�V�F�[�_�쐬.
	HRESULT CreateShader();
	//���f���쐬.
	HRESULT CreateModel();

	//�����_�����O�p.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, RAY Ray);

private:
	ID3D11Device* m_pDevice11;
	ID3D11DeviceContext* m_pContext11;

	ID3D11VertexShader* m_pVertexShader;	//���_�V�F�[�_.
	ID3D11InputLayout* m_pVertexLayout;	//���_���C�A�E�g.
	ID3D11PixelShader* m_pPixelShader;		//�s�N�Z���V�F�[�_.
	ID3D11Buffer* m_pConstantBuffer;	//�R���X�^���g�o�b�t�@.

	ID3D11Buffer* m_pVertexBuffer;	//���_�o�b�t�@.

	D3DXVECTOR3		m_vPosition;	//���W.
	D3DXVECTOR3		m_vRotation;	//��].

	RAY				m_Ray;			//���C�\����
};