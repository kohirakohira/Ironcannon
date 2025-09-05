#include "CSound.h"
#include <stdio.h>  //sprintf_s�֐����g�p����̂ɕK�v.

//�R���X�g���N�^.
CSound::CSound()
	//�������q���X�g.
	: m_hWnd( nullptr )
	, m_sAlias()
	, m_iVolume( 1000 )
{
}

//�f�X�g���N�^.
CSound::~CSound()
{
}

//================================================================================
//  �����t�@�C�����J���֐�.
//================================================================================
bool CSound::Open( LPCTSTR sFileName, LPCTSTR sAlias, HWND hWnd )
{
	//�����ݒ�.
	SetInitParam( sAlias, hWnd );

	//�R�}���h.
	TCHAR cmd[STR_BUFF_MAX] = _T("");

	wsprintf( cmd, _T("open %s alias %s"), sFileName, m_sAlias );

	if( mciSendString( cmd, nullptr, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}


//================================================================================
//  �����t�@�C�������֐�.
//================================================================================
bool CSound::Close()
{
	//�R�}���h.
	TCHAR cmd[STR_BUFF_MAX] = _T("");

	wsprintf( cmd, _T("close %s"), m_sAlias );

	if( mciSendString( cmd, nullptr, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}


//==============================================================================
//  �������Đ�����֐�.
//==============================================================================
bool CSound::Play( bool bNotify )
{
	//�R�}���h.
	TCHAR cmd[STR_BUFF_MAX] = _T("");

	if( bNotify == true ){
		wsprintf( cmd, _T("play %s notify"), m_sAlias ); //notify:�����̏�Ԏ擾�ŕK�v.
	}
	else{
		wsprintf( cmd, _T("play %s"), m_sAlias );
	}

	if( mciSendString( cmd, nullptr, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}


//==============================================================================
//  �������Đ�����(SE�Ŏg��).
//==============================================================================
bool CSound::PlaySE()
{
	SeekToStart();
	if( Play() == true ){
		return true;
	}
	return false;
}


//==============================================================================
//  �������Đ�����(���[�v).
//==============================================================================
bool CSound::PlayLoop()
{
	if( IsStopped() == true ){
		SeekToStart();
		if( Play( true ) == true ){
			return true;
		}
	}
	return false;
}


//==============================================================================
//  �������~����֐�.
//==============================================================================
bool CSound::Stop()
{
	//�R�}���h.
	TCHAR cmd[STR_BUFF_MAX] = _T("");

	wsprintf( cmd, _T("stop %s"), m_sAlias );

	if( mciSendString( cmd, nullptr, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}


//==============================================================================
//  �����̏�Ԃ��擾����֐�.
//      sStatus �� �z�񐔂� 256 �ȉ��ɂ��邱��.
//  ���������A��Ԃ��擾����ꍇ�́A�Đ����Ɂunotify�v��ݒ肵�A
//    �E�B���h�E�n���h���Ƀ��b�Z�[�W�𑗂��Ă����K�v������.
//==============================================================================
bool CSound::GetStatus( LPTSTR sStatus )
{
	//�R�}���h.
	TCHAR cmd[STR_BUFF_MAX] = _T("");

	wsprintf( cmd, _T("status %s mode"), m_sAlias );

	if( mciSendString( cmd, sStatus, STR_BUFF_MAX, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}


//==============================================================================
//  �����̒�~���m�F����֐�.
//==============================================================================
bool CSound::IsStopped()
{
	TCHAR sStatus[STR_BUFF_MAX] = _T("");

	// ��Ԃ̎擾.
	if( GetStatus( sStatus ) ){
		// �������r.
		if( lstrcmp( sStatus, _T("stopped") ) == 0 ){
			return true;
		}
	}
	return false;
}


//==============================================================================
//  �����̍Đ��ʒu���ŏ��ɂ���֐�.
//==============================================================================
bool CSound::SeekToStart()
{
	//�R�}���h.
	TCHAR cmd[STR_BUFF_MAX] = _T("");

	wsprintf( cmd, _T("seek %s to start"), m_sAlias );

	if( mciSendString( cmd, nullptr, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}


//==============================================================================
//  �����̉��ʂ�ݒ肷��֐�.
//==============================================================================
bool CSound::SetVolume( int iVolume )
{
	//�͈͓��Ɋۂ߂�.
	if( iVolume < 0 )       { iVolume = 0; }
	if( iVolume > 1000 )    { iVolume = 1000; }

	//�����o�ϐ��ɐݒ�.
	m_iVolume = iVolume;

	//�R�}���h.
	TCHAR cmd[STR_BUFF_MAX] = _T("");

	wsprintf( cmd, _T("setaudio %s volume to %d"), m_sAlias, m_iVolume );

	if( mciSendString( cmd, nullptr, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//==============================================================================
//	�����l�̐ݒ肷��֐�.
//==============================================================================
void CSound::SetInitParam( LPCTSTR sAlias, HWND hWnd )
{
	//�E�B���h�E�n���h����o�^.
	m_hWnd = hWnd;

	//�G�C���A�X��o�^(������̃R�s�[).
	lstrcpy( m_sAlias, sAlias );
}