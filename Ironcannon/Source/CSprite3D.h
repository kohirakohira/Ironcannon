#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//�O���錾.
class CDirectX11;

/**************************************************
*	�X�v���C�g3D�N���X.
**/
class CSprite3D
{
public:
	//======================================
	//	�\����.
	//======================================
	//�������\����
	struct WHSIZE
	{
		float w;
		float h;
	};
	//�X�v���C�g�\����
	struct SPRITE_STATE
	{
		WHSIZE Disp;	//�`�敝����
		WHSIZE Base;	//���摜������
		WHSIZE Stride;	//1�R�}������̕�����
	};

	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.	
		D3DXVECTOR4	vColor;		//�J���[�iRGBA�̌^�ɍ��킹��j.
		D3DXVECTOR4	vUV;		//UV���W�ix,y�̂ݎg�p�j.
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//���_���W.
		D3DXVECTOR2	Tex;	//�e�N�X�`�����W.
	};

public:
	CSprite3D();	//�R���X�g���N�^.
	~CSprite3D();	//�f�X�g���N�^.

	//������.
	HRESULT Init(CDirectX11& pDx11, LPCTSTR lpFileName, SPRITE_STATE& pSs );

	//���.
	void Release();

	//�V�F�[�_�쐬.
	HRESULT CreateShader();
	//���f���쐬.
	HRESULT CreateModel();
	//�e�N�X�`���쐬.
	HRESULT CreateTexture( LPCTSTR lpFileName );
	//�T���v���쐬.
	HRESULT CreateSampler();

	//�����_�����O�p.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj);

	//���W����ݒ�.
	void SetPosition(const D3DXVECTOR3& vPos) {	m_vPosition = vPos;	}
	//���Wx��ݒ�.
	void SetPositionX( float x ){ m_vPosition.x = x; }
	//���Wy��ݒ�.
	void SetPositionY( float y ){ m_vPosition.y = y; }
	//���Wz��ݒ�.
	void SetPositionZ( float z ){ m_vPosition.z = z; }

	//��]����ݒ�.
	void SetRotation(const D3DXVECTOR3& vRot){	m_vRotation = vRot;	}
	//��]��Y��ݒ�(Yaw).
	void SetRotationY(float y){	m_vRotation.y = y;	}
	//��]��X��ݒ�(Pitch).
	void SetRotationX(float x){	m_vRotation.x = x;	}
	//��]��Z��ݒ�(Roll).
	void SetRotationZ(float z){	m_vRotation.z = z;	}

	//�g��k������ݒ�.
	void SetScale(const D3DXVECTOR3& vScale) { m_vScale = vScale; }

	//���l��ݒ�.
	void SetAlpha(float alpha) { m_Alpha = alpha; }

	//�p�^�[���ԍ�(�}�X��)��ݒ�
	void SetPatternNo(SHORT x, SHORT y)
	{
		m_PatternNo.x = x;
		m_PatternNo.y = y;
	}
	//�ő�p�^�[����(�}�X��)���擾
	POINTS GetPatternMax() const { return m_PatternMax; }

	//�r���{�[�h�@�\��ON/OFF�؂�ւ�
	void SetBillboard(bool flag) { m_Billboard = flag; }

private:
	CDirectX11*				m_pDx11;
	ID3D11Device*			m_pDevice11;
	ID3D11DeviceContext*	m_pContext11;

	ID3D11VertexShader*		m_pVertexShader;	//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;	//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;		//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;	//�R���X�^���g�o�b�t�@.

	ID3D11Buffer*			m_pVertexBuffer;	//���_�o�b�t�@.

	ID3D11ShaderResourceView*	m_pTexture;			//�e�N�X�`��.
	ID3D11SamplerState*			m_pSampleLinear;	//�T���v��:�e�N�X�`���Ɋe��t�B���^��������.

	D3DXVECTOR3		m_vPosition;	//���W.
	D3DXVECTOR3		m_vRotation;	//��].
	D3DXVECTOR3		m_vScale;		//�g�k.

	D3DXVECTOR2		m_UV;		//�e�N�X�`��UV���W.

	float			m_Alpha;	//���l(0:�����A1:���S�s����).

	SPRITE_STATE	m_SpriteState;	//�X�v���C�g���
	POINTS			m_PatternNo;	//�p�^�[���ԍ�(�}�X��)
	POINTS			m_PatternMax;	//�ő�p�^�[��(�}�X�̍ő�l)

	bool			m_Billboard;	//�r���{�[�h�L������
};