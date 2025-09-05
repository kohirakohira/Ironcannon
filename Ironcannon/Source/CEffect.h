#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���B4005:�Ē�`
#pragma warning(disable:4005)

//---------------------------------------
// Effekseer�֌W�w�b�_�A���C�u����
//---------------------------------------
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

#ifdef _DEBUG
	#pragma comment(lib,"Effekseerd.lib")
	#pragma comment(lib,"EffekseerRendererDX11d.lib")
#else//#ifdef _DEBUG
	#pragma comment(lib,"Effekseer.lib")
	#pragma comment(lib,"EffekseerRendererDX11.lib")
#endif//#ifdef _DEBUG

//�G�C���A�X��p��
//���R�[�h�����ɒ����Ȃ��ēǂ݂Â炢����
namespace {
	namespace Es = ::Effekseer;
	using EsManagerRef	= ::Es::ManagerRef;
	using EsManager		= ::Es::Manager;
	using EsEffectRef	= ::Es::EffectRef;
	using EsEffect		= ::Es::Effect;
	using EsVec3		= ::Es::Vector3D;
	using EsMatrix		= ::Es::Matrix44;
	using EsHandle		= ::Es::Handle;
	using EsRendererRef = ::EffekseerRendererDX11::RendererRef;
	using EsRenderer	= ::EffekseerRendererDX11::Renderer;
};

/**************************************************
*	�t���[�\�t�g Effekseer�̃f�[�^���g�����߂̃N���X
*	singleton(�V���O���g���F�f�U�C���p�^�[���̂P��)�ō쐬
**/
class CEffect
{
public:
	//�G�t�F�N�g��ޗ񋓌^
	enum enList
	{
		Test0 = 0,	//���Őݒ�
		Test1,		//���Őݒ�
		Test2,		//���Őݒ�
		Max			//�ő吔
	};

	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H)
	static CEffect& GetInstance()
	{
		//�B��̃C���X�^���X���쐬����
		//��static�ō쐬���ꂽ�̂łQ��ڈȍ~�͉��̂P�s�͖��������
		static CEffect s_Instance;	//s_:static�̈Ӗ�
		return s_Instance;
	}
	~CEffect();

	//�\�z
	HRESULT Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	//�f�[�^�ǂݍ���
	HRESULT LoadData();
	//�`��
	void Draw( const D3DXMATRIX& mView, const D3DXMATRIX& mProj,
			const LIGHT& Light, const CAMERA& Camera);

	//-----------------------------------
	// �ϊ��n
	//-----------------------------------
	//�x�N�^�[
	::EsVec3 ToEfkVector3(const D3DXVECTOR3* pSrcVec3Dx);
	D3DXVECTOR3 ToDxVector3(const ::EsVec3* pSrcVec3Efk);
	//�s��
	::EsMatrix ToEfkMatrix(const D3DXMATRIX* pSrcMatDx);
	D3DXMATRIX ToDxMatrix(const ::EsMatrix* pSrcMatEfk);

	//-----------------------------------
	// ����n
	//-----------------------------------
	//�Đ�
	static ::EsHandle Play(enList listNo, const D3DXVECTOR3& pos) {
		CEffect& pE = CEffect::GetInstance();
		return pE.m_pManager->Play(pE.m_pEffect[listNo], pos.x, pos.y, pos.z);
	}
	//��~
	static void Stop(::EsHandle handle) {
		CEffect::GetInstance().m_pManager->StopEffect(handle);
	}
	//�S�Ē�~
	static void StopAll() {
		CEffect::GetInstance().m_pManager->StopAllEffects();
	}
	//�ꎞ��~
	static void Paused(::EsHandle handle, bool paused) {
		CEffect::GetInstance().m_pManager->SetPaused(handle, paused);
	}
	//�Đ����x�̐ݒ�
	static void SetSpeed(::EsHandle handle, float speed) {
		CEffect::GetInstance().m_pManager->SetSpeed(handle, speed);
	}
	//�ʒu���w�肷��
	static void SetLocation(::EsHandle handle, D3DXVECTOR3 pos) {
		CEffect::GetInstance().m_pManager->
			SetLocation(handle, ::EsVec3(pos.x, pos.y, pos.z));
	}
	//��]���w�肷��
	static void SetRotation(::EsHandle handle, D3DXVECTOR3 rot) {
		CEffect::GetInstance().m_pManager->
			SetRotation(handle, rot.x, rot.y, rot.z);
	}
	//��]���w�肷��i����]�j
	static void SetRotation(::EsHandle handle, D3DXVECTOR3 vAxis, float angle){
		CEffect::GetInstance().m_pManager->
			SetRotation(handle, ::EsVec3(vAxis.x, vAxis.y, vAxis.z), angle);
	}
	//�T�C�Y���w�肷��
	static void SetScale(::EsHandle handle, D3DXVECTOR3 scale) {
		CEffect::GetInstance().m_pManager->
			SetScale(handle, scale.x, scale.y, scale.z);
	}

private:
	//������R�s�[���֎~����
	CEffect();
	CEffect(const CEffect& rhs) = delete;
	CEffect& operator = (const CEffect& rhs) = delete;

	//�f�[�^���
	HRESULT ReleaseData();

	//�r���[�s���ݒ�
	void SetViewMatrix(const D3DXMATRIX& mView);
	//�v���W�F�N�V�����s���ݒ�
	void SetProjectionMatrix(const D3DXMATRIX& mProj);

private:
	//�G�t�F�N�g�𓮍삳���邽�߂ɕK�v
	::EsManagerRef		m_pManager;
	::EsRendererRef		m_pRenderer;

	//�G�t�F�N�g�̎�ނ��ƂɕK�v
	::EsEffectRef		m_pEffect[enList::Max];
};

