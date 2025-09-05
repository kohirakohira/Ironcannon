#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//_declspec()	:DLL����(�֐��A�N���X�A�N���X�̃����o�֐���)�G�N�X�|�[�g����
//align()		:(�����I��)16byte�Ŏg�p����
#define ALIGN16 _declspec( align(16) )

/**************************************************
*	�X�v���C�g2D�N���X.
**/
class CSprite2D
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
		ALIGN16 D3DXMATRIX	mWorld;		//���[���h�s��.
		ALIGN16 D3DXVECTOR4	vColor;		//�J���[�iRGBA�̌^�ɍ��킹��j.
		ALIGN16 D3DXVECTOR4	vUV;		//UV���W�ix,y�̂ݎg�p�j.
		ALIGN16 float fViewPortWidth;	//�r���[�|�[�g�̕�
		ALIGN16 float fViewPortHeight;	//�r���[�|�[�g�̍���
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//���_���W.
		D3DXVECTOR2	Tex;	//�e�N�X�`�����W.
	};

public:
	CSprite2D();	//�R���X�g���N�^.
	~CSprite2D();	//�f�X�g���N�^.

	//������.
	HRESULT Init(LPCTSTR lpFileName, SPRITE_STATE& pSs );

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
	void Render();

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

	//UV����ݒ�.
	void SetUVInfomation(D3DXVECTOR2 uv, bool flg) 
	{
		m_UV = uv; 
		m_MoveFlag = flg;
	}

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

	//�`�悲�ƂɃr���[�|�[�g�ݒ�
	void SetViewPortSize(float w, float h);

private:
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

	D3DXVECTOR2		m_UV;			//�e�N�X�`��UV���W���e�N�X�`���𓮂����p.

	bool			m_MoveFlag;		//�e�N�X�`���̓��������ۂ�.

	float			m_Alpha;		//���l(0:�����A1:���S�s����).

	SPRITE_STATE	m_SpriteState;	//�X�v���C�g���
	POINTS			m_PatternNo;	//�p�^�[���ԍ�(�}�X��)
	POINTS			m_PatternMax;	//�ő�p�^�[��(�}�X�̍ő�l)
};