#include "CTimer.h"
#include <algorithm>	// std::max �p.

//std::max���g�p����ƃG���[���o�����ߎg�p.
using std::max;

CTimer::CTimer()
	: m_Time			( 0 )
	, m_HitTime			()

	, m_StartTimer		()
	, m_TotalTime		( 0.f )
	, m_TimerPosition	()
{
}

CTimer::~CTimer()
{
}

void CTimer::Draw()
{
	//�f�o�b�O�e�L�X�g(�X�R�A)�̕`��
	m_pDbgText->SetColor(1.f, 1.f, 1.f);
	m_Time = static_cast<int>(GetRemainingTime());
	TCHAR TimeText[16];
	_stprintf_s(TimeText, _T("%d"), m_Time);
	m_pDbgText->Render(TimeText, m_TimerPosition.x, m_TimerPosition.y);

}

void CTimer::StartTimer(float time)
{
	// �^�C�}�[�̊J�n���Ԃ��L�^����.
	m_StartTimer = std::chrono::steady_clock::now();

	//�Q�[�����Ԃ�ݒ肷��.
	m_TotalTime = std::chrono::duration<float>(time);
}

float CTimer::GetRemainingTime() const
{
	//���̎��Ԃ��L�^����ϐ�.
	//���̎��Ԃ��擾�E�ێ�.
	std::chrono::steady_clock::time_point m_NowTime = std::chrono::steady_clock::now();

	//�o�ߎ��Ԃ��L�^����ϐ�.
	//�o�ߎ��Ԃ����߂�.
	std::chrono::duration<float> m_ElapsedTime = m_NowTime - m_StartTimer;

	//�c�莞�Ԃ��L�^����ϐ�.
	//�c�莞�Ԃ����߂�.
	std::chrono::duration<float> m_RemainingTime = m_TotalTime - m_ElapsedTime;

	return max(0.f, m_RemainingTime.count()); // �c�莞�Ԃ����ɂȂ�Ȃ��悤�ɂ��邽�߁A0�Ɣ�r���đ傫������Ԃ�.
}

// �c�莞�Ԃ�0�b�ȉ����ǂ�����Ԃ��i���^�C�}�[���I���������j
bool CTimer::IsFinished() const
{
	return GetRemainingTime() <= 0.0f;
}

//���������Ƃ��ɕK�v�Ȋ֐�.
void CTimer::HitTimer()
{
	m_HitTime = std::chrono::steady_clock::now();
}

float CTimer::GetElapsed() const
{
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = now - m_HitTime;
	return elapsed.count();
}
