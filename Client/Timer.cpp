#include "Common.h"
#include "Timer.h"

Timer::Timer()
	: m_frequency{}
	, m_startingTime{}
	, m_endingTime{}
	, m_deltaTime(0)
	, m_frameCount(0)
	, m_runningTime(0)
	, m_fps(0)
{

}

Timer::~Timer()
{
}

void Timer::init()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_startingTime);
}

void Timer::update()
{
	QueryPerformanceCounter(&m_endingTime);

	m_deltaTime = (double)(m_endingTime.QuadPart - m_startingTime.QuadPart) / (double)m_frequency.QuadPart;

	m_startingTime = m_endingTime;

#ifdef _DEBUG
	if (m_deltaTime > (1. / 60.))
		m_deltaTime = (1. / 60.);
#endif

	m_frameCount++;
	m_runningTime += m_deltaTime;

	if (m_runningTime >= 1.)
	{
		m_fps = m_frameCount;
		m_runningTime = 0;
		m_frameCount = 0;
	}
}