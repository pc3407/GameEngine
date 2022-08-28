#pragma once
#include <windows.h>
#include <stdint.h>
#include <stdio.h>

class TimeMgr : public Singleton<TimeMgr>
{
	friend class Singleton<TimeMgr>;

private:
	TimeMgr();
	~TimeMgr();


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
	void render();

	float GetDelta() { return (float)m_deltaTime; }
};