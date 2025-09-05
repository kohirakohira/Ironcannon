#include "CDebugText.h"
#include "CDirectX11.h"

//�V�F�[�_�t�@�C�����i�f�B���N�g�����܂ށj.
const TCHAR SHADER_NAME[] = _T( "Data\\Shader\\DebugText.hlsl" );

//�R���X�g���N�^.
CDebugText::CDebugText()
	: m_pDx11			( nullptr )
	, m_pDevice11		( nullptr )
	, m_pContext11		( nullptr )
	, m_pVertexShader	( nullptr )
	, m_pVertexLayout	( nullptr )
	, m_pPixelShader	( nullptr )
	, m_pConstantBuffer	( nullptr )
	, m_pVertexBuffer	()
	, m_pSampleLinear	( nullptr )
	, m_pTexture		( nullptr )
	, m_Alpha			( 1.0f )
	, m_Color			( 1.f, 1.f, 1.f )
	, m_Kerning			()
	, m_FontSize		( 0.f )
{
}

//�f�X�g���N�^.
CDebugText::~CDebugText()
{
	//����������Ăяo��.
	Release();

	//�ʂ̂Ƃ���ŊǗ����Ă���̂ł����ł�nullptr�����ď�����.
	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
	m_pDx11 = nullptr;
}

//������.
//	ID3D11Device* pDevice11 �O���ō쐬���Ď����Ă���B
//	ID3D11DeviceContext* pContext11 �O���ō쐬���Ď����Ă���B
HRESULT CDebugText::Init( CDirectX11& pDx11 )
{
	m_pDx11 = &pDx11;
	m_pDevice11 = m_pDx11->GetDevice();		//���Ԃ͕ʂ̂Ƃ���ɂ���.���Ƃ����L���Ă���.
	m_pContext11 = m_pDx11->GetContext();	//���Ԃ͕ʂ̂Ƃ���ɂ���.���Ƃ����L���Ă���.

	//�V�F�[�_�쐬.
	if( FAILED( CreateShader() ))
	{
		return E_FAIL;
	}
	//�|���S���쐬.
	if( FAILED( CreateModel() ))
	{
		return E_FAIL;
	}
	//�e�N�X�`���쐬.
	if( FAILED( CreateTexture( _T("Data\\DebugText\\ascii.png") )))
	{
		return E_FAIL;
	}
	//�T���v���쐬.
	if( FAILED( CreateSampler() ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//���.
void CDebugText::Release()
{
	SAFE_RELEASE( m_pSampleLinear );
	SAFE_RELEASE( m_pTexture );
	for (int i = SPRITE_MAX - 1; i >= 0; i--) {
		SAFE_RELEASE( m_pVertexBuffer[i] );
	}
	SAFE_RELEASE( m_pConstantBuffer );
	SAFE_RELEASE( m_pPixelShader );
	SAFE_RELEASE( m_pVertexLayout );
	SAFE_RELEASE( m_pVertexShader );

	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
}

//===========================================================
//	HLSL�t�@�C����ǂݍ��݃V�F�[�_���쐬����.
//	HLSL: High Level Shading Language �̗�.
//===========================================================
HRESULT CDebugText::CreateShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif//#ifdef _DEBUG

	//HLSL����o�[�e�b�N�X�V�F�[�_�̃u���u���쐬.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�V�F�[�_�t�@�C�����iHLSL�t�@�C���j.
			nullptr,		//�}�N����`�̔z��ւ̃|�C���^�i���g�p�j.
			nullptr,		//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^�i���g�p�j.
			"VS_Main",		//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.
			"vs_5_0",		//�V�F�[�_�̃��f�����w�肷�镶����i�v���t�@�C���j.
			uCompileFlag,	//�V�F�[�_�R���p�C���t���O.
			0,				//�G�t�F�N�g�R���p�C���t���O�i���g�p�j.
			nullptr,		//�X���b�h �|���v �C���^�[�t�F�C�X�ւ̃|�C���^�i���g�p�j.
			&pCompiledShader,//�u���u���i�[���郁�����ւ̃|�C���^.
			&pErrors,		//�G���[�ƌx���ꗗ���i�[���郁�����ւ̃|�C���^.
			nullptr)))		//�߂�l�ւ̃|�C���^�i���g�p�j.
	{
		_ASSERT_EXPR( false, _T( "hlsl�ǂݍ��ݎ��s" ) );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬�����u���u����u�o�[�e�b�N�X�V�F�[�_�v���쐬.
	if (FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShader )))	//(out)�o�[�e�b�N�X�V�F�[�_.
	{
		_ASSERT_EXPR( false, _T( "�o�[�e�b�N�X�V�F�[�_�쐬���s" ));
		return E_FAIL;
	}

	//���_�C���v�b�g���C�A�E�g���`.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//�ʒu.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGI�̃t�H�[�}�b�g(32bit float�^*3).
			0,
			0,								//�f�[�^�̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD",						//�e�N�X�`���ʒu.
			0,
			DXGI_FORMAT_R32G32_FLOAT,		//DXGI�̃t�H�[�}�b�g(32bit float�^*2).
			0,
			12,								//�f�[�^�̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};
	//���_�C���v�b�g���C�A�E�g�̔z��v�f�����Z�o.
	UINT numElements = sizeof( layout) / sizeof(layout[0] );

	//���_�C���v�b�g���C�A�E�g���쐬.
	if (FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout )))	//(out)���_�C���v�b�g���C�A�E�g.
	{
		_ASSERT_EXPR( false, _T( "���_�C���v�b�g���C�A�E�g�쐬���s" ) );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );

	//HLSL����s�N�Z���V�F�[�_�̃u���u���쐬.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//�V�F�[�_�t�@�C�����iHLSL�t�@�C���j.
			nullptr,			//�}�N����`�̔z��ւ̃|�C���^�i���g�p�j.
			nullptr,			//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^�i���g�p�j.
			"PS_Main",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.
			"ps_5_0",			//�V�F�[�_�̃��f�����w�肷�镶����i�v���t�@�C���j.
			uCompileFlag,		//�V�F�[�_�R���p�C���t���O.
			0,					//�G�t�F�N�g�R���p�C���t���O�i���g�p�j.
			nullptr,			//�X���b�h �|���v �C���^�[�t�F�C�X�ւ̃|�C���^�i���g�p�j.
			&pCompiledShader,	//�u���u���i�[���郁�����ւ̃|�C���^.
			&pErrors,			//�G���[�ƌx���ꗗ���i�[���郁�����ւ̃|�C���^.
			nullptr )))			//�߂�l�ւ̃|�C���^�i���g�p�j.
	{
		_ASSERT_EXPR( false, _T( "hlsl�ǂݍ��ݎ��s" ) );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬�����u���u����u�s�N�Z���V�F�[�_�v���쐬.
	if (FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pPixelShader )))	//(out)�s�N�Z���V�F�[�_.
	{
		_ASSERT_EXPR( false, _T( "�s�N�Z���V�F�[�_�쐬���s" ) );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );

	//�R���X�^���g�i�萔�j�o�b�t�@�쐬.
	//�V�F�[�_�ɓ���̐��l�𑗂�o�b�t�@.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//�R���X�^���g�o�b�t�@���w��.
	cb.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);	//�R���X�^���g�o�b�t�@�̃T�C�Y.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//�������݂ŃA�N�Z�X.
	cb.MiscFlags = 0;	//���̑��̃t���O�i���g�p�j.
	cb.StructureByteStride = 0;	//�\���̂̃T�C�Y�i���g�p�j.
	cb.Usage = D3D11_USAGE_DYNAMIC;	//�g�p���@�F���ڏ�������.

	//�R���X�^���g�o�b�t�@�̍쐬.
	if (FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			nullptr,
			&m_pConstantBuffer )))
	{
		_ASSERT_EXPR( false, _T( "�R���X�^���g�o�b�t�@�쐬���s" ) );
		return E_FAIL;
	}


	return S_OK;
}


//���f���쐬.
HRESULT CDebugText::CreateModel()
{
	//�萔
	constexpr float CHAR_W = 10.f;		//�P����������̕�
	constexpr float CHAR_H = 12.f;		//�P����������̍���
	constexpr float TEXTURE_W = 128.f;	//�e�N�X�`���̕�
	constexpr float TEXTURE_H = 128.f;	//�e�N�X�`���̍���

	//�t�H���g���ɋ�`�쐬
	float left	= 0.f;
	float top	= 0.f;
	float right	= 0.f;
	float bottom= 0.f;

	//�쐬�ς݃J�E���^
	int count = 0;

	//�Q�d���[�v�łP�������w�肷��
	for (int x = 0; x < SPRITE_MAX_W; x++)
	{
		for (int y = 0; y < SPRITE_MAX_H; y++)
		{
			//�J�[�j���O�i�������m�̊Ԋu�j�̐ݒ�
			m_Kerning[count] = 10.f;	//�������ƂŒ����\

			//�P������̑傫��
			left	= x * CHAR_W;
			top		= y * CHAR_H;
			right	= left + m_Kerning[count];
			bottom	= top + CHAR_H;

			//�e�N�X�`���̑傫������䗦�v�Z
			left	/= TEXTURE_W;
			top		/= TEXTURE_H;
			right	/= TEXTURE_W;
			bottom	/= TEXTURE_H;

			//�|��(�l�p�`)�̒��_���쐬.
			VERTEX vertices[] =
			{
				//���_���W(x,y,z)				 UV���W(u,v)
				D3DXVECTOR3(   0.0f, CHAR_H, 0.0f), D3DXVECTOR2(  left, bottom ),	//���_�P(����).
				D3DXVECTOR3(   0.0f,   0.0f, 0.0f), D3DXVECTOR2(  left, top    ),	//���_�Q(����).
				D3DXVECTOR3( CHAR_W, CHAR_H, 0.0f), D3DXVECTOR2( right, bottom ),	//���_�R(�E��).
				D3DXVECTOR3( CHAR_W,   0.0f, 0.0f), D3DXVECTOR2( right, top    )	//���_�S(�E��).
			};
			//�ő�v�f�����Z�o����.
			UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

			//�o�b�t�@�\����.
			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DEFAULT;		//�g�p���@�i�f�t�H���g�j.
			bd.ByteWidth = sizeof(VERTEX) * uVerMax;	//���_�̃T�C�Y.
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���_�o�b�t�@�Ƃ��Ĉ���.
			bd.CPUAccessFlags = 0;	//CPU����̓A�N�Z�X���Ȃ�.
			bd.MiscFlags = 0;	//���̑��̃t���O�i���g�p�j.
			bd.StructureByteStride = 0;	//�\���̂̃T�C�Y�i���g�p�j.

			//�T�u���\�[�X�f�[�^�\����.
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = vertices;	//�|���̒��_���Z�b�g.

			//���_�o�b�t�@�̍쐬.
			if (FAILED(m_pDevice11->CreateBuffer(
				&bd, &InitData, &m_pVertexBuffer[count])))
			{
				_ASSERT_EXPR(false, _T("���_�o�b�t�@�쐬���s"));
				return E_FAIL;
			}

			count++;	//�P�����쐬�����̂Ŏ���
		}
	}
	return S_OK;
}

//�e�N�X�`���쐬.
HRESULT CDebugText::CreateTexture( LPCTSTR lpFileName )
{
	//�e�N�X�`���쐬.
	if( FAILED( D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,		//���\�[�X���g�p����f�o�C�X�̃|�C���^.
		lpFileName,			//�t�@�C����.
		nullptr, nullptr,
		&m_pTexture,		//(out)�e�N�X�`��.
		nullptr ) ) )
	{
		_ASSERT_EXPR( false, _T( "�e�N�X�`���쐬���s" ) );
		return E_FAIL;
	}

	return S_OK;
}


//�T���v���쐬.
HRESULT CDebugText::CreateSampler()
{
	//�e�N�X�`���p�̃T���v���\����.
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory( &samDesc, sizeof( samDesc ) );
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;//���j�A�t�B���^�i���`��ԁj.
						//POINT:���������e��.
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;	//���b�s���O���[�h�iWRAP:�J��Ԃ��j.
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//MIRROR: ���]�J��Ԃ�.
	//CLAMP : �[�̖͗l�������L�΂�.
	//BORDER: �ʓr���E�F�����߂�.

	//�T���v���쐬.
	if( FAILED( m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear ) ) )//(out)�T���v��.
	{
		_ASSERT_EXPR( false, _T( "�T���v���쐬���s" ) );
		return E_FAIL;
	}

	return S_OK;
}

//�t�H���g�����_�����O
void CDebugText::RenderFont(int FontIndex, float x, float y)
{
	//���[���h�s��.
	D3DXMATRIX	mWorld;
	D3DXMATRIX	mTrans, mScale;

	//�g��k���s��.
	D3DXMatrixScaling( &mScale, m_FontSize, m_FontSize, 1.f );

	//���s�s��i���s�ړ��j.
	D3DXMatrixTranslation( &mTrans, x, y, 0.f );

	//���[���h���W�ϊ�.
	//�d�v: �g�k�s�� * ���s�s��.
	mWorld = mScale * mTrans;

	//�V�F�[�_�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	SHADER_CONSTANT_BUFFER cb;	//�R���X�^���g�o�b�t�@.
	//�o�b�t�@���̃f�[�^�̏��������J�n����map.
	if (SUCCEEDED(
		m_pContext11->Map( m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData )))
	{
		//���[���h�s���n��.
		D3DXMATRIX m = mWorld;
		D3DXMatrixTranspose( &m, &m );	//�s���]�u����.
		cb.mWorld = m;

		//�J���[.
		cb.vColor = D3DXVECTOR4(
			m_Color.x, m_Color.y, m_Color.z, m_Alpha );

		//�r���[�|�[�g�̕��A������n��
		cb.fViewPortWidth	= static_cast<float>( WND_W );
		cb.fViewPortHeight	= static_cast<float>( WND_H );

		memcpy_s(pData.pData, pData.RowPitch,
			(void*)( &cb ), sizeof( cb ) );

		m_pContext11->Unmap(m_pConstantBuffer, 0);
	}

	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof( VERTEX );	//�f�[�^�̊Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers( 0, 1,
		&m_pVertexBuffer[FontIndex], &stride, &offset);

	//�A���t�@�u�����h�L���ɂ���.
	m_pDx11->SetAlphaBlend( true );

	//�v���~�e�B�u�������_�����O.
	m_pContext11->Draw( 4, 0 );	//�|���i���_4���j.

	//�A���t�@�u�����h�����ɂ���.
	m_pDx11->SetAlphaBlend( false );

}

//�����_�����O�p.
void CDebugText::Render(LPCTSTR text, int x, int y)
{
	//�g�p����V�F�[�_�̓o�^.
	m_pContext11->VSSetShader( m_pVertexShader, nullptr, 0 );
	m_pContext11->PSSetShader( m_pPixelShader, nullptr, 0 );

	//���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg�����H.
	m_pContext11->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
	m_pContext11->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

	//���_�C���v�b�g���C�A�E�g���Z�b�g.
	m_pContext11->IASetInputLayout( m_pVertexLayout );
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//�e�N�X�`�����V�F�[�_�ɓn��.
	m_pContext11->PSSetSamplers( 0, 1, &m_pSampleLinear );
	m_pContext11->PSSetShaderResources( 0, 1, &m_pTexture );

	float fx = static_cast<float>(x);
	float fy = static_cast<float>(y);

	//�����������[�v
	for (int i = 0; i < lstrlen(text); i++)
	{
		TCHAR font = text[i];
		int index = font - 32;	//�t�H���g�C���f�b�N�X�쐬

		//�t�H���g�����_�����O
		RenderFont( index, fx, fy );

		fx += m_Kerning[index] * m_FontSize;
	}
}
