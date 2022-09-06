#pragma once
#include "Singleton.h"

class Timer : public Singleton<Timer>
{
	friend class Singleton<Timer>;

private:
	Timer();
	~Timer();

private:
	LARGE_INTEGER	m_frequency;
	LARGE_INTEGER	m_startingTime;
	LARGE_INTEGER	m_endingTime;

	double			m_deltaTime;

	UINT			m_frameCount;
	double			m_runningTime;
	UINT			m_fps;

public:
	void init();
	void update();

	float Delta() { return (float)m_deltaTime; }
	UINT FPS() { return m_fps; }
};