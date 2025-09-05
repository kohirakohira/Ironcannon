#include "MyMacro.h"
#include "CDirectX11.h"

//�R���X�g���N�^.
CDirectX11::CDirectX11()
	: m_pDevice11				( nullptr )
	, m_pContext11				( nullptr )
	, m_pSwapChain				( nullptr )
	, m_pBackBuffer_TexRTV		( nullptr )
	, m_pBackBuffer_DSTex		( nullptr )
	, m_pBackBuffer_DSTexDSV	( nullptr )

	, m_pDepthStencilStateOn	( nullptr )
	, m_pDepthStencilStateOff	( nullptr )

	, m_pAlphaBlendOn			( nullptr )
	, m_pAlphaBlendOff			( nullptr )
{
}


//�f�X�g���N�^.
CDirectX11::~CDirectX11()
{
	Release();
}

//DirectX�\�z�֐�.
HRESULT CDirectX11::Create(HWND hWnd)
{
	//�f�o�C�X�ƃX���b�v�`�F�C�����쐬.
	if( FAILED(
		CreateDeviceAndSwapChain(
			hWnd,
			static_cast<UINT>(FPS),
			static_cast<UINT>(WND_W),
			static_cast<UINT>(WND_H) )))
	{
		return E_FAIL;
	}

	//�e��e�N�X�`���Ƃ���ɕt�т���e��r���[�i��ʁj���쐬.
	//	�o�b�N�o�b�t�@�����F�J���[�o�b�t�@�����_�[�^�[�Q�b�g�r���[.


	if( FAILED(
		CreateColorBackBufferRTV() ) )
	{
		return E_FAIL;
	}
	
	// �o�b�N�o�b�t�@�����F�f�v�X�i�[�x�j�X�e���V�������_�[�^�[�Q�b�g�r���[.
	if( FAILED(
		CreateDepthStencilBackBufferRTV() ) )
	{
		return E_FAIL;
	}

	//�����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[���p�C�v���C���ɃZ�b�g.
	m_pContext11->OMSetRenderTargets(
		1,
		&m_pBackBuffer_TexRTV,
		m_pBackBuffer_DSTexDSV );

	//�f�v�X�X�e���V���ݒ�̍쐬.
	if( FAILED( CreateDepthStencilState() ) ){
		return E_FAIL;
	}

	//�A���t�@�u�����h�X�e�[�g�̍쐬.
	if( FAILED( CreateAlphaBlendState() ) ){
		return E_FAIL;
	}

	//------------------------------------------------
	//	�r���[�|�[�g�ݒ�.
	//------------------------------------------------
	D3D11_VIEWPORT vp;
	vp.Width	= WND_W;	//��.
	vp.Height	= WND_H;	//����.
	vp.MinDepth = 0.0f;		//�ŏ��[�x�i��O�j.
	vp.MaxDepth = 1.0f;		//�ő�[�x�i���j.
	vp.TopLeftX = 0.0f;		//����ʒux.
	vp.TopLeftY = 0.0f;		//����ʒuy.

	m_pContext11->RSSetViewports( 1, &vp );


	//���X�^���C�Y�i�ʂ̓h��Ԃ����j�̐ݒ�.
	if( FAILED( CreateRasterizer() ) ){
		return E_FAIL;
	}

	return S_OK;
}

//�������.
// �������Ƃ��́A��������Ƌt�̏��ŊJ������.
void CDirectX11::Release()
{
	SAFE_RELEASE( m_pAlphaBlendOff );
	SAFE_RELEASE( m_pAlphaBlendOn );

	SAFE_RELEASE( m_pDepthStencilStateOff );
	SAFE_RELEASE( m_pDepthStencilStateOn );

	SAFE_RELEASE( m_pBackBuffer_DSTexDSV );
	SAFE_RELEASE( m_pBackBuffer_DSTex );
	SAFE_RELEASE( m_pBackBuffer_TexRTV );

	SAFE_RELEASE( m_pSwapChain );
	SAFE_RELEASE( m_pContext11 );
	SAFE_RELEASE( m_pDevice11 );
}


//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬.
HRESULT CDirectX11::CreateDeviceAndSwapChain(
	HWND hWnd, UINT uFPS, UINT uWidth, UINT uHeight )
{
	//�X���b�v�`�F�[���\����.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );	//0�ŏ�����.
	sd.BufferCount			= 1;		//�o�b�N�o�b�t�@�̐�.
	sd.BufferDesc.Width		= uWidth;	//�o�b�N�o�b�t�@�̕�.
	sd.BufferDesc.Height	= uHeight;	//�o�b�N�o�b�t�@�̍���.
	sd.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;		//�t�H�[�}�b�g�i32�r�b�g�J���[�j.
	sd.BufferDesc.RefreshRate.Numerator		= uFPS;				//���t���b�V�����[�g�i����j ��FPS:60.
	sd.BufferDesc.RefreshRate.Denominator	= 1;				//���t���b�V�����[�g�i���q�j.
	sd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�g�����i�`���j.
	sd.OutputWindow			= hWnd;		//�E�B���h�E�n���h��.
	sd.SampleDesc.Count		= 1;		//�}���`�T���v���̐�.
	sd.SampleDesc.Quality	= 0;		//�}���`�T���v���̃N�I���e�B.
	sd.Windowed				= TRUE;		//�E�B���h�E���[�h�i�t���X�N���[������FALSE�j.

	//�쐬�����݂�@�\���x���̗D����w��.
	// (GPU���T�|�[�g����@�\�Z�b�g�̒�`).
	// D3D_FEATURE_LEVEL�񋓌^�̔z��.
	// D3D_FEATURE_LEVEL_11_0:Direct3D 11.0 �� GPU���x��.
	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;//�z��̗v�f��.

	//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬.
	//�n�[�h�E�F�A�iGPU�j�f�o�C�X�ł̍쐬.
	if( FAILED(
		D3D11CreateDeviceAndSwapChain(
			nullptr,					//�r�f�I�A�_�v�^�ւ̃|�C���^.
			D3D_DRIVER_TYPE_HARDWARE,	//�쐬����f�o�C�X�̎��.
			nullptr,					//�\�t�g�E�F�A ���X�^���C�U����������DLL�̃n���h��.
			0,							//�L���ɂ��郉���^�C�����C���[.
			&pFeatureLevels,			//�쐬�����݂�@�\���x���̏������w�肷��z��ւ̃|�C���^.
			1,							//���̗v�f��.
			D3D11_SDK_VERSION,			//SDK�̃o�[�W����.
			&sd,						//�X���b�v�`�F�[���̏������p�����[�^�̃|�C���^.
			&m_pSwapChain,				//(out)�����_�����O�Ɏg�p����X���b�v�`�F�[��.
			&m_pDevice11,				//(out)�쐬���ꂽ�f�o�C�X.
			pFeatureLevel,				//�@�\���x���̔z��ɂ���ŏ��̗v�f��\���|�C���^.
			&m_pContext11 ) ) )			//(out)�f�o�C�X�@�R���e�L�X�g.
	{
		//WARP�f�o�C�X�̍쐬.
		// D3D_FEATURE_LEVEL_9_1�`D3D_FEATURE_LEVEL_10_1.
		if( FAILED(
			D3D11CreateDeviceAndSwapChain(
				nullptr, D3D_DRIVER_TYPE_WARP, nullptr,
				0, &pFeatureLevels, 1, D3D11_SDK_VERSION,
				&sd, &m_pSwapChain, &m_pDevice11,
				pFeatureLevel, &m_pContext11 ) ) )
		{
			//���t�@�����X�f�o�C�X�̍쐬.
			// DirectX SDK���C���X�g�[������Ă��Ȃ��Ǝg���Ȃ�.
			if( FAILED(
				D3D11CreateDeviceAndSwapChain(
					nullptr, D3D_DRIVER_TYPE_REFERENCE, nullptr,
					0, &pFeatureLevels, 1, D3D11_SDK_VERSION,
					&sd, &m_pSwapChain, &m_pDevice11,
					pFeatureLevel, &m_pContext11 ) ) )
			{
				MessageBox( nullptr,
					_T( "�f�o�C�X�ƃX���b�v�`�F�[���쐬���s" ),
					_T( "Error" ), MB_OK );
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

//���X�^���C�U�쐬.
//���X�^���C�Y�i�ʂ̓h��Ԃ����j�̐ݒ���s��.
//�X�e�[�^�X�̍쐬����ݒ�܂ōs���Ă���ŏ��Ɉ�x�����Ăяo���΂悢.
//�����_�����O�Œ��ɓh��Ԃ�����ύX�������ꍇ�́A���L�̊֐��𕪉�����K�v������.
HRESULT CDirectX11::CreateRasterizer()
{
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory( &rdc, sizeof( rdc ) );
	rdc.FillMode = D3D11_FILL_SOLID;//�h��Ԃ��i�\���b�h�j.

	//�J�����O�̐ݒ�.
	//D3D11_CULL_BACK	:�w�ʂ�`�悵�Ȃ�.
	//D3D11_CULL_FRONT	:���ʂ�`�悵�Ȃ�.
	//D3D11_CULL_NONE	:�J�����O��؂�i���w�ʂ�`�悷��j.
	rdc.CullMode = D3D11_CULL_NONE;

	//�|���S���̕\�������肷��t���O.
	//TRUE	:�����Ȃ�O�����B�E���Ȃ�������B
	//FALSE	:�t�ɂȂ�.
	rdc.FrontCounterClockwise = FALSE;

	//�����ɂ��ẴN���b�s���O�L��.
	rdc.DepthClipEnable = FALSE;

	ID3D11RasterizerState* pRs = nullptr;
	m_pDevice11->CreateRasterizerState( &rdc, &pRs );
	m_pContext11->RSSetState( pRs );
	SAFE_RELEASE( pRs );

	return S_OK;
}

//�f�v�X�X�e���V���ݒ�.
//���̊֐��P��ON/OFF��2��ނ��쐬����.
HRESULT CDirectX11::CreateDepthStencilState()
{
	//�[�x�e�X�g�i�y�e�X�g�j�̐ݒ�.
	//��ON/OFF�̋��ʕ����̂ݐݒ�.
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	dsDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc		= D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable	= FALSE;
	dsDesc.StencilReadMask	= D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask	= D3D11_DEFAULT_STENCIL_WRITE_MASK;

	//�[�x�e�X�g�i�y�e�X�g�j��L���ɂ���.
	dsDesc.DepthEnable = TRUE;//�L��.
	//�[�x�ݒ�쐬.
	if( FAILED(
		m_pDevice11->CreateDepthStencilState(
			&dsDesc, &m_pDepthStencilStateOn ) ) )
	{
		_ASSERT_EXPR( false, _T("�[�xON�ݒ�쐬���s") );
		return E_FAIL;
	}

	//�[�x�e�X�g�i�y�j�e�X�g�𖳌��ɂ���.
	dsDesc.DepthEnable = FALSE;//����.
	//�[�x�ݒ�쐬.
	if( FAILED(
		m_pDevice11->CreateDepthStencilState(
			&dsDesc, &m_pDepthStencilStateOff ) ) )
	{
		_ASSERT_EXPR( false, _T( "�[�xOFF�ݒ�쐬���s" ) );
		return E_FAIL;
	}

	return S_OK;
}


//�u�����h�X�e�[�g�쐬.
//�A���t�@�u�����h��ON/OFF�̂Q��ނ��쐬.
HRESULT CDirectX11::CreateAlphaBlendState()
{
	//�A���t�@�u�����h�p�u�����h�X�e�[�g�\����.
	//png�t�@�C�����ɃA���t�@��񂪂���̂ŁA���߂���悤�Ƀu�����h�X�e�[�g�Őݒ肷��.
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory( &BlendDesc, sizeof( BlendDesc ) );	//������.

	BlendDesc.IndependentBlendEnable = false;	//false	:RenderTarget[0]�̃����o�̂ݎg�p����.
												//true	:RenderTarget[0�`7]���g�p�ł���.
												//�i�����_�[�^�[�Q�b�g���ɓƗ������u�����h�����j.
	//�A���t�@�g�D�J�o���[�W���g�p����.
	// �A���t�@�΃J�o���b�W�̓}���`�T���v�����O��@�ł���A
	// �A���t�@�����x���g�p���ăT�[�t�F�X���̃G�b�W���`����d������|���S�����������݂��鍂���x�̗t�Ȃǂ̏󋵂ōł��𗧂�.
	// �����l��0.51�ȉ��ɂ���Ɗ��S�����ɂȂ�̂Œ��ӂ��K�v.
	BlendDesc.AlphaToCoverageEnable = false;
	//���f�ނɑ΂���ݒ�.
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;		//�A���t�@�u�����h���w��.
	//�d�˂�f�ނɑ΂���ݒ�.
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;//�A���t�@�u�����h�̔��]���w��.
	//�u�����h�I�v�V����.
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;		//ADD:���Z����.
	//���f�ނ̃A���t�@�ɑ΂���w��.
	BlendDesc.RenderTarget[0].SrcBlendAlpha	= D3D11_BLEND_ONE;	//���̂܂܎g�p.
	//�d�˂�f�ނ̃A���t�@�ɑ΂���ݒ�.
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;//�������Ȃ��B
	//�A���t�@�̃u�����h�I�v�V����.
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;//ADD:���Z����.
	//�s�N�Z�����̏������݃}�X�N.
	BlendDesc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;	//�S�Ă̐����iRGBA�j�ւ̃f�[�^�̊i�[��������.

	//�A���t�@�u�����h���g�p����.
	BlendDesc.RenderTarget[0].BlendEnable = true;	//�L��.
	//�u�����h�X�e�[�g�쐬.
	if( FAILED(
		m_pDevice11->CreateBlendState( &BlendDesc, &m_pAlphaBlendOn ) ) )
	{
		_ASSERT_EXPR( false, _T( "�A���t�@�u�����h�X�e�[�g(ON)�쐬���s" ) );
		return E_FAIL;
	}

	//�A���t�@�u�����h���g�p����.
	BlendDesc.RenderTarget[0].BlendEnable = false;	//����.
	//�u�����h�X�e�[�g�쐬.
	if( FAILED(
		m_pDevice11->CreateBlendState( &BlendDesc, &m_pAlphaBlendOff ) ) )
	{
		_ASSERT_EXPR( false, _T( "�A���t�@�u�����h�X�e�[�g(OFF)�쐬���s" ) );
		return E_FAIL;
	}

	return S_OK;
}


//���ߐݒ�̐؂�ւ�.
void CDirectX11::SetAlphaBlend( bool flag )
{
	UINT mask = 0xffffffff;	//�}�X�N�l.
	ID3D11BlendState* pTmp
		= ( flag == true ) ? m_pAlphaBlendOn : m_pAlphaBlendOff;

	//�A���t�@�u�����h�ݒ���Z�b�g.
	m_pContext11->OMSetBlendState( pTmp, nullptr, mask );
}


//�[�x�i�y�j�e�X�gON/OFF�؂�ւ�.
void CDirectX11::SetDepth(bool flag)
{
	ID3D11DepthStencilState* pTmp
		= ( flag == true ) ? m_pDepthStencilStateOn : m_pDepthStencilStateOff;

	//�[�x�ݒ���Z�b�g.
	m_pContext11->OMSetDepthStencilState( pTmp, 1 );
}


//�o�b�N�o�b�t�@�N���A�֐�.
//���̊֐����Ăяo������Ƀ����_�����O�����邱��.
void CDirectX11::ClearBackBuffer()
{
	//��ʂ̃N���A.
	float ClearColor[4] = { 0.0f, 0.0f, 0.6f, 1.0f };	//�N���A�F�iRGBA�̏��j.
	//�J���[�o�b�N�o�b�t�@.
	m_pContext11->ClearRenderTargetView(
		m_pBackBuffer_TexRTV, ClearColor );
	//�f�v�X�X�e���V���o�b�N�o�b�t�@.
	m_pContext11->ClearDepthStencilView(
		m_pBackBuffer_DSTexDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0 );
}


//�`��.
void CDirectX11::Present()
{
	m_pSwapChain->Present( 0, 0 );
}


//�o�b�N�o�b�t�@�쐬:�J���[�p�����_�[�^�[�Q�b�g�r���[�쐬.
HRESULT CDirectX11::CreateColorBackBufferRTV()
{
	//�o�b�N�o�b�t�@�e�N�X�`�����擾�i���ɂ���̂ō쐬�ł͂Ȃ��j.
	ID3D11Texture2D* pBackBuffer_Tex = nullptr;
	if( FAILED(
		m_pSwapChain->GetBuffer(
			0,
			__uuidof( ID3D11Texture2D ),	//__uuidof:���Ɋ֘A�t�����ꂽGUID���擾
											//         Texture2D�̗B��̕��Ƃ��Ĉ���
			(LPVOID*)&pBackBuffer_Tex ) ) )	//(out)�o�b�N�o�b�t�@�e�N�X�`��.
	{
		_ASSERT_EXPR( false, _T( "�X���b�v�`�F�C������o�b�N�o�b�t�@�擾���s" ) );
		return E_FAIL;
	}

	//���̃e�N�X�`���ɑ΂��ă����_�[�^�[�Q�b�g�r���[�iRTV�j���쐬.
	if( FAILED(
		m_pDevice11->CreateRenderTargetView(
			pBackBuffer_Tex,
			nullptr,
			&m_pBackBuffer_TexRTV ) ) )	//(out)RTV.
	{
		_ASSERT_EXPR( false, _T( "�����_�[�^�C�Q�b�g�r���[�쐬���s" ) );
		return E_FAIL;
	}
	//�o�b�N�o�b�t�@�e�N�X�`�������.
	SAFE_RELEASE( pBackBuffer_Tex );

	return S_OK;
}


//�o�b�N�o�b�t�@�쐬:�f�v�X�X�e���V���p�����_�[�^�[�Q�b�g�r���[�쐬.
HRESULT CDirectX11::CreateDepthStencilBackBufferRTV()
{

	//�f�v�X�i�[��or�[�x�j�X�e���V���r���[�p�̃e�N�X�`�����쐬.
	D3D11_TEXTURE2D_DESC	descDepth;
	descDepth.Width = WND_W;		//��.
	descDepth.Height = WND_H;		//����.
	descDepth.MipLevels = 1;		//�~�b�v�}�b�v���x���F1.
	descDepth.ArraySize	= 1;		//�z�񐔁F1.
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;	//32�r�b�g�t�H�[�}�b�g.
	descDepth.SampleDesc.Count = 1;				//�}���`�T���v���̐�.
	descDepth.SampleDesc.Quality = 0;			//�}���`�T���v���̃N�I���e�B.
	descDepth.Usage = D3D11_USAGE_DEFAULT;		//�g�p���@�F�f�t�H���g.
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//�[�x�i�X�e���V���Ƃ��Ďg�p�j.
	descDepth.CPUAccessFlags = 0;				//CPU����̓A�N�Z�X���Ȃ�.
	descDepth.MiscFlags = 0;					//���̑��̐ݒ�Ȃ�.

	if( FAILED(
		m_pDevice11->CreateTexture2D(
			&descDepth,
			nullptr,
			&m_pBackBuffer_DSTex ) ) )	//(out)�f�v�X�X�e���V���p�e�N�X�`��.
	{
		return E_FAIL;
	}

	//���̃e�N�X�`���ɑ΂��ăf�v�X�X�e���V���r���[�iDSV�j���쐬.
	if( FAILED( m_pDevice11->CreateDepthStencilView(
		m_pBackBuffer_DSTex,
		nullptr,
		&m_pBackBuffer_DSTexDSV ) ) )	//(out)DSV.
	{
		_ASSERT_EXPR( false, _T( "�f�v�X�X�e���V���r���[�쐬���s." ) );
		return E_FAIL;
	}

	return S_OK;
}
