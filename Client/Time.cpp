#include "Time.h"

Time::Time()
	: m_StartingTime(0)
	, m_EndingTime(0)
	, m_DeltaTime(0.)
	, m_FrameCount(0)
	, m_RunningTime(0)
	, m_FPS(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_Frequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_StartingTime);
}

Time::~Time()
{
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_EndingTime);

	m_DeltaTime = (double)(m_EndingTime - m_StartingTime) / (double)m_Frequency;

	m_StartingTime = m_EndingTime;

	m_FrameCount++;
	m_RunningTime += m_DeltaTime;

	if (m_RunningTime >= 1.)
	{
		m_FPS = m_FrameCount;
		m_RunningTime = 0;
		m_FrameCount = 0;
	}
}