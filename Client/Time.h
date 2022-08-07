#pragma once
#include <windows.h>
#include <stdint.h>
#include <stdio.h>

class Time
{
public:
	Time();
	~Time();

public:
	void Update();

	uint32_t	GetFPS() { return m_FPS; }

private:
	int64_t		m_Frequency;
	int64_t		m_StartingTime;
	int64_t		m_EndingTime;

	double		m_DeltaTime;

	uint32_t	m_FrameCount;
	double		m_RunningTime;
	uint32_t	m_FPS;
};