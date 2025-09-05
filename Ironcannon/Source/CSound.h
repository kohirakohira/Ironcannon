#pragma once

#include <Windows.h>

//���C�u�����ǂݍ���.
#pragma comment( lib, "winmm.lib" ) //�����Đ��ŕK�v.

/**************************************************
*	�T�E���h�N���X.
*		midi,mp3,wav�`���t�@�C���̍Đ��E��~�����s��.
**/
class CSound
{
public://public:�O������A�N�Z�X�\.
	//�萔�錾.
	static constexpr int STR_BUFF_MAX = 256;//�����o�b�t�@.

	//�R���X�g���N�^.
	//�I�u�W�F�N�g�̐������Ɏ����I�ɌĂяo��������ȃ����o�֐�.
	CSound();

	//�f�X�g���N�^.
	//�I�u�W�F�N�g���j�����ꂽ�Ƃ��Ɏ����I�ɌĂяo��������ȃ����o�֐�.
	//�֐����̓N���X���Ɂu~(�`���_)�v��t����.
	~CSound();

	//�����t�@�C�����J��.
	bool Open( LPCTSTR sFName, LPCTSTR sAlias, HWND hWnd );

	//�����t�@�C�������.
	bool Close();

	//�������Đ�����֐�(��Ԓʒm�̗L���t���O).
	bool Play( bool bNotify = false );

	//�������Đ�����(SE�Ŏg��).
	bool PlaySE();

	//�������Đ�����(���[�v).
	bool PlayLoop();

	//�������~����֐�.
	bool Stop();

	//�����̏�Ԃ��擾����.
	bool GetStatus( LPTSTR sStatus );

	//�����̒�~���m�F����֐�.
	bool IsStopped();

	//�����̍Đ��ʒu���ŏ��ɂ���֐�.
	bool SeekToStart();

	//�����̉��ʂ�ݒ肷��֐�.
	bool SetVolume( int iVolume );
	//�����̉��ʂ��擾����֐�.
	int GetVolume() const { return m_iVolume; }

private://private:�O������A�N�Z�X�s�\.
		//���̃N���X���ł����g�p���Ȃ��֐��Ȃǂ������ɐ錾����.
	//�����l�̐ݒ肷��֐�.
	void SetInitParam( LPCTSTR sAlias, HWND hWnd );

private://private:�O������A�N�Z�X�s�\.
	//�����o�ϐ��͊�{�I�ɂ�private�Ő錾����.
	HWND	m_hWnd;					//�E�B���h�E�n���h��.
	TCHAR	m_sAlias[STR_BUFF_MAX];	//�G�C���A�X.
	int		m_iVolume;				//�{�����[��.
};

//�����K���ƃn���K���A���L�@.
//m_:member�i�����o�[�j.
//g_:global�i�O���[�o���j.
//s_:static�i�X�^�e�B�b�N�j.
//iNo:int�iint�^�̔ԍ��j.
//str:string�i�X�g�����O�F������j.