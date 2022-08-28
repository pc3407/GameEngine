#include "Common.h"
#include "TimeMgr.h"

#include "Core.h"

TimeMgr::TimeMgr()
	: m_frequency{}
	, m_startingTime{}
	, m_endingTime{}
	, m_deltaTime(0.)
	, m_frameCount(0)
	, m_runningTime(0)
	, m_fps(0)
{

}

TimeMgr::~TimeMgr()
{
}

void TimeMgr::init()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_startingTime);
}

void TimeMgr::update()
{
	QueryPerformanceCounter(&m_endingTime);

	m_deltaTime = (double)(m_endingTime.QuadPart - m_startingTime.QuadPart) / (double)m_frequency.QuadPart;

	m_startingTime = m_endingTime;

#ifdef _DEBUG
	if (m_deltaTime > (1. / 60.))
		m_deltaTime = (1. / 60.);
#endif
}

void TimeMgr::render()
{
	m_frameCount++;
	m_runningTime += m_deltaTime;

	if (m_runningTime >= 1.)
	{
		m_fps = m_frameCount;
		m_runningTime = 0;
		m_frameCount = 0;
	}

	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_fps, m_deltaTime);
	SetWindowText(Core::Get()->GetHandle(), szBuffer);
}
