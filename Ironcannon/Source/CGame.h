#pragma once
#include "CSceneManager.h"

/********************************************************************************
*	�Q�[���N���X.
**/
class CGame
{
public:
	static constexpr int ENEMY_MAX = 3;	//�G�l�~�[�̍ő吔

	CGame(HWND hWnd );
	~CGame();

	void Create();
	HRESULT LoadData();
	void Release();

	void Update();
	void Draw();

private:
	//�E�B���h�E�n���h��.
	HWND		m_hWnd;

	//�V�[���}�l�[�W���[.
	std::shared_ptr<CSceneManager>	m_pSceneManager;

private:
	//=delete�u�폜��`�v�ƌĂ΂��@�\.
	//�w�肳�ꂽ�ꍇ�A���̊֐��͌Ăяo���Ȃ��Ȃ�.
	CGame() = delete;	//�f�t�H���g�R���X�g���N�^�֎~.
	CGame( const CGame& ) = delete;
	CGame& operator = (const CGame& rhs ) = delete;
};