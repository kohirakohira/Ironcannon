#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//_declspec()	:DLL����(�֐��A�N���X�A�N���X�̃����o�֐���)�G�N�X�|�[�g����
//align()		:(�����I��)16byte�Ŏg�p����
#define ALIGN16 _declspec( align(16) )

//�O���錾.
class CDirectX11;

/**************************************************
*	�f�o�b�O�e�L�X�g�N���X.
**/
class CDebugText
{
public:
	//�萔�錾
	static constexpr int SPRITE_MAX_W = 10;
	static constexpr int SPRITE_MAX_H = 10;
	static constexpr int SPRITE_MAX = SPRITE_MAX_W * SPRITE_MAX_H;

	//======================================
	//	�\����.
	//======================================
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		ALIGN16 D3DXMATRIX	mWorld;		//���[���h�s��.
		ALIGN16 D3DXVECTOR4	vColor;		//�J���[�iRGBA�̌^�ɍ��킹��j.
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
	CDebugText();	//�R���X�g���N�^.
	~CDebugText();	//�f�X�g���N�^.

	//������.
	HRESULT Init( CDirectX11& pDx11 );



	//�����_�����O�p.
	void Render(LPCTSTR text, int x, int y);

	//���l��ݒ�.
	void SetAlpha(float alpha) { m_Alpha = alpha; }

	//�F��ݒ�
	void SetColor(float r, float g, float b)
	{
		m_Color.x = r;
		m_Color.y = g;
		m_Color.z = b;
	}

	//�t�H���g�̃T�C�Y�ݒ�.
	void SetFontSize(float size)
	{
		m_FontSize = size;
	}

private:
	//�V�F�[�_�쐬.
	HRESULT CreateShader();
	//���f���쐬.
	HRESULT CreateModel();
	//�e�N�X�`���쐬.
	HRESULT CreateTexture( LPCTSTR lpFileName );
	//�T���v���쐬.
	HRESULT CreateSampler();

	//�t�H���g�����_�����O
	void RenderFont(int FontIndex, float x, float y);

	//���.
	void Release();


private:
	CDirectX11*				m_pDx11;
	ID3D11Device*			m_pDevice11;
	ID3D11DeviceContext*	m_pContext11;

	ID3D11VertexShader*		m_pVertexShader;	//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;	//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;		//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;	//�R���X�^���g�o�b�t�@.

	ID3D11Buffer*			m_pVertexBuffer[SPRITE_MAX];	//���_�o�b�t�@.

	ID3D11ShaderResourceView*	m_pTexture;			//�e�N�X�`��.
	ID3D11SamplerState*			m_pSampleLinear;	//�T���v��:�e�N�X�`���Ɋe��t�B���^��������.

	float			m_Alpha;	//���l(0:�����A1:���S�s����).
	float			m_FontSize;	//�t�H���g�̑傫��.

	D3DXVECTOR3		m_Color;	//�F(RGB)
	float			m_Kerning[SPRITE_MAX];	//�J�[�j���O
};