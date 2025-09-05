#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//�w�b�_�Ǎ�.
#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>	//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>


//���C�u�����ǂݍ���.
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx10.lib")	//�uD3DX�`�v�̒�`�g�p���ɕK�v.


/**************************************************
*	DirectX11 �Z�b�g�A�b�v.
**/
class CDirectX11
{
public:
	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
	static CDirectX11& GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
		static CDirectX11 s_Instance;	//s_:static�̈Ӗ�.
		return s_Instance;
	}

	~CDirectX11();

	//DirectX11�\�z.
	HRESULT Create(HWND hWnd);
	//DirectX11���.
	void Release();

	//�[�x�i�y�j�e�X�gON/OFF�؂�ւ�.
	void SetDepth( bool flag );
	//�A���t�@�u�����hON/OFF�؂�ւ�.
	void SetAlphaBlend( bool flag );

	//�o�b�N�o�b�t�@�N���A�֐�.
	void ClearBackBuffer();
	//�`��.
	void Present();

	//�f�o�C�X���擾.
	ID3D11Device* GetDevice() const { return m_pDevice11; }
	//�f�o�C�X�R���e�L�X�g���擾.
	ID3D11DeviceContext* GetContext() const { return m_pContext11; }

private://�O������A�N�Z�X�s�\.
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	CDirectX11();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	CDirectX11(const CDirectX11& rhs) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	CDirectX11& operator = (const CDirectX11& rhs) = delete;

	//�f�o�C�X�ƃX���b�v�`�F�C���쐬.
	HRESULT CreateDeviceAndSwapChain(
		HWND hWnd, UINT uFPS, UINT uWidth, UINT uHeight );

	//�o�b�N�o�b�t�@�쐬:�J���[�p�����_�[�^�[�Q�b�g�r���[�쐬.
	HRESULT CreateColorBackBufferRTV();

	//�o�b�N�o�b�t�@�쐬:�f�v�X�X�e���V���p�����_�[�^�[�Q�b�g�r���[�쐬.
	HRESULT CreateDepthStencilBackBufferRTV();

	//���X�^���C�U�쐬.
	HRESULT CreateRasterizer();

	//�f�v�X�X�e���V���X�e�[�g�쐬.
	HRESULT CreateDepthStencilState();

	//�A���t�@�u�����h�X�e�[�g�쐬.
	HRESULT CreateAlphaBlendState();

private:
	ID3D11Device*				m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*		m_pContext11;			//�f�o�C�X�R���e�L�X�g.
	IDXGISwapChain*				m_pSwapChain;			//�X���b�v�`�F�[��.
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;	//�����_�[�^�[�Q�b�g�r���[.
	ID3D11Texture2D*			m_pBackBuffer_DSTex;	//�f�v�X�X�e���V���p�e�N�X�`��.
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;	//�f�v�X�X�e���V���r���[.

	//�[�x�i�y�j�e�X�g�ݒ�.
	ID3D11DepthStencilState*	m_pDepthStencilStateOn;		//�L���ݒ�.
	ID3D11DepthStencilState*	m_pDepthStencilStateOff;	//�����ݒ�.

	//�A���t�@�u�����h.
	ID3D11BlendState*		m_pAlphaBlendOn;	//�L���ݒ�.
	ID3D11BlendState*		m_pAlphaBlendOff;	//�����ݒ�.
};