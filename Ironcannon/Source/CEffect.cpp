#include "CEffect.h"

//�`��X�v���C�g�ő吔
constexpr int RENDER_SPRITE_MAX = 8000;
//�G�t�F�N�g�Ǘ��p�C���X�^���X�ő吔
constexpr int EFFECT_INSTANCE_MAX = 1000;

//DirectX Vector3 �� Effekseer Vector3 �ɕϊ�����
::EsVec3 CEffect::ToEfkVector3(const D3DXVECTOR3* pSrcVec3Dx)
{
	return ::EsVec3(pSrcVec3Dx->x, pSrcVec3Dx->y, pSrcVec3Dx->z);
}

//Effekseer Vector3 �� DirectX Vector3 �ɕϊ�����
D3DXVECTOR3 CEffect::ToDxVector3(const::EsVec3* pSrcVec3Efk)
{
	return D3DXVECTOR3(pSrcVec3Efk->X, pSrcVec3Efk->Y, pSrcVec3Efk->Z);
}

//DirectX Matrix �� Effekseer Matrix �ɕϊ�����
::EsMatrix CEffect::ToEfkMatrix(const D3DXMATRIX* pSrcMatDx)
{
	::EsMatrix OutMatEfk;
#if 0
	OutMatEfk.Values[0][0] = pSrcMatDx->m[0][0];	//_11
	OutMatEfk.Values[0][1] = pSrcMatDx->m[0][1];	//_12
	OutMatEfk.Values[0][2] = pSrcMatDx->m[0][2];	//_13
	OutMatEfk.Values[0][3] = pSrcMatDx->m[0][3];	//_14

	OutMatEfk.Values[1][0] = pSrcMatDx->m[1][0];	//_21
	OutMatEfk.Values[1][1] = pSrcMatDx->m[1][1];	//_22
	OutMatEfk.Values[1][2] = pSrcMatDx->m[1][2];	//_23
	OutMatEfk.Values[1][3] = pSrcMatDx->m[1][3];	//_24

	OutMatEfk.Values[2][0] = pSrcMatDx->m[2][0];	//_31
	OutMatEfk.Values[2][1] = pSrcMatDx->m[2][1];	//_32
	OutMatEfk.Values[2][2] = pSrcMatDx->m[2][2];	//_33
	OutMatEfk.Values[2][3] = pSrcMatDx->m[2][3];	//_34

	OutMatEfk.Values[3][0] = pSrcMatDx->m[3][0];	//_41
	OutMatEfk.Values[3][1] = pSrcMatDx->m[3][1];	//_42
	OutMatEfk.Values[3][2] = pSrcMatDx->m[3][2];	//_43
	OutMatEfk.Values[3][3] = pSrcMatDx->m[3][3];	//_44
#else
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			OutMatEfk.Values[i][j] = pSrcMatDx->m[i][j];
		}
	}
#endif
	return OutMatEfk;
}

D3DXMATRIX CEffect::ToDxMatrix(const::EsMatrix* pSrcMatEfk)
{
	D3DXMATRIX OutMatDx;
#if 0
	OutMatDx.m[0][0] = pSrcMatEfk->Values[0][0];	//_11
	OutMatDx.m[0][1] = pSrcMatEfk->Values[0][1];	//_12
	OutMatDx.m[0][2] = pSrcMatEfk->Values[0][2];	//_13
	OutMatDx.m[0][3] = pSrcMatEfk->Values[0][3];	//_14

	OutMatDx.m[1][0] = pSrcMatEfk->Values[1][0];	//_21
	OutMatDx.m[1][1] = pSrcMatEfk->Values[1][1];	//_22
	OutMatDx.m[1][2] = pSrcMatEfk->Values[1][2];	//_23
	OutMatDx.m[1][3] = pSrcMatEfk->Values[1][3];	//_24

	OutMatDx.m[2][0] = pSrcMatEfk->Values[2][0];	//_31
	OutMatDx.m[2][1] = pSrcMatEfk->Values[2][1];	//_32
	OutMatDx.m[2][2] = pSrcMatEfk->Values[2][2];	//_33
	OutMatDx.m[2][3] = pSrcMatEfk->Values[2][3];	//_34

	OutMatDx.m[3][0] = pSrcMatEfk->Values[3][0];	//_41
	OutMatDx.m[3][1] = pSrcMatEfk->Values[3][1];	//_42
	OutMatDx.m[3][2] = pSrcMatEfk->Values[3][2];	//_43
	OutMatDx.m[3][3] = pSrcMatEfk->Values[3][3];	//_44
#else
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			OutMatDx.m[i][j] = pSrcMatEfk->Values[i][j];
		}
	}
#endif
	return OutMatDx;
}

CEffect::CEffect()
	: m_pManager	( nullptr )
	, m_pRenderer	( nullptr )

	, m_pEffect		()
{
}

//�f�[�^���
HRESULT CEffect::ReleaseData()
{
	return S_OK;
}

//�r���[�s���ݒ�
void CEffect::SetViewMatrix(const D3DXMATRIX& mView)
{
	::EsMatrix EsCamMat;	//�J�����s��
	EsCamMat = ToEfkMatrix(&mView);

	//�J�����s���ݒ�
	m_pRenderer->SetCameraMatrix(EsCamMat);
}

//�v���W�F�N�V�����s���ݒ�
void CEffect::SetProjectionMatrix(const D3DXMATRIX& mProj)
{
	::EsMatrix EsProjMat;	//�v���W�F�N�V�����s��
	EsProjMat = ToEfkMatrix(&mProj);

	//�v���W�F�N�V�����s���ݒ�
	m_pRenderer->SetProjectionMatrix(EsProjMat);
}

CEffect::~CEffect()
{
	//�G�t�F�N�g�f�[�^�̔j��
	ReleaseData();

	//�G�t�F�N�g�̃}�l�[�W���[��j��
	m_pManager.Reset();

	//�G�t�F�N�g�̃����_���[��j��
	m_pRenderer.Reset();
}

//�\�z
HRESULT CEffect::Create(
	ID3D11Device* pDevice,
	ID3D11DeviceContext* pContext)
{
	//�G�t�F�N�g�̃}�l�[�W���[�̍쐬
	m_pManager = ::EsManager::Create(RENDER_SPRITE_MAX);

	//�G�t�F�N�g�̃����_���[�̍쐬
	m_pRenderer = ::EsRenderer::Create(pDevice, pContext, EFFECT_INSTANCE_MAX);

	//�`�惂�W���[���̐ݒ�
	m_pManager->SetSpriteRenderer(m_pRenderer->CreateSpriteRenderer());
	m_pManager->SetRibbonRenderer(m_pRenderer->CreateRibbonRenderer());
	m_pManager->SetRingRenderer(m_pRenderer->CreateRingRenderer());
	m_pManager->SetTrackRenderer(m_pRenderer->CreateTrackRenderer());
	m_pManager->SetModelRenderer(m_pRenderer->CreateModelRenderer());

	//�e�N�X�`���A���f���A�}�e���A�����[�_�[�̐ݒ������B
	//���[�U�[���Ǝ��Ɋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
	m_pManager->SetTextureLoader(m_pRenderer->CreateTextureLoader());
	m_pManager->SetModelLoader(m_pRenderer->CreateModelLoader());
	m_pManager->SetMaterialLoader(m_pRenderer->CreateMaterialLoader());
	m_pManager->SetCurveLoader(::Es::MakeRefPtr<::Es::CurveLoader>());

	return S_OK;
}

//�f�[�^�ǂݍ���
HRESULT CEffect::LoadData()
{
	struct EffectList
	{
		enList listNo;				//enList�񋓌^��ݒ�
		const char16_t path[256];	//�t�@�C���̖��O(�p�X�t��)
	};
	EffectList EList[] =
	{
		//u""�́AUTF-16�G���R�[�f�B���O�̕����񃊃e�����ŁAconst char16_t* �ɑ���\
		{ enList::Test0,	u"Data\\Effekseer\\Laser01.efk"	},
		{ enList::Test1,	u"Data\\Effekseer\\Laser01.efk"	},
		{ enList::Test2,	u"Data\\Effekseer\\Laser01.efk"	},
	};
	//�z��̍ő�v�f�����Z�o�i�z��S�̂̃T�C�Y�^�z��P���̃T�C�Y�j
	int list_max = sizeof(EList) / sizeof(EList[0]);
	for (int i = 0; i < list_max; i++)
	{
		int listNo = EList[i].listNo;

		//�G�t�F�N�g�̓ǂݍ���
		m_pEffect[listNo] =
			::EsEffect::Create( m_pManager, EList[i].path);

		if (m_pEffect[listNo] == nullptr) {
			_ASSERT_EXPR(false, L"CEffect::LoadData()");
			return E_FAIL;
		}
	}

	return S_OK;
}

//�`��
void CEffect::Draw(
	const D3DXMATRIX& mView, const D3DXMATRIX& mProj,
	const LIGHT& Light, const CAMERA& Camera)
{
	//�r���[�s���ݒ�
	SetViewMatrix(mView);

	//�v���W�F�N�V�����s���ݒ�
	SetProjectionMatrix(mProj);

	//���C���[�p�����[�^�ݒ�
	::EsManager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = ToEfkVector3(&Camera.vPosition);
	m_pManager->SetLayerParameter(0, layerParameter);

	//�G�t�F�N�g�̍X�V����
	m_pManager->Update();

	//-------------------------
	// Effekseer�����_�����O
	//-------------------------
	//�G�t�F�N�g�̕`��J�n�������s��
	m_pRenderer->BeginRendering();

	//�G�t�F�N�g�̕`����s��
	m_pManager->Draw();

	//�G�t�F�N�g�̕`��I���������s��
	m_pRenderer->EndRendering();
}
