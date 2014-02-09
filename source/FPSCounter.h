#pragma once
#include "stdfx.h"
class CFPSCounter{
public:
	CFPSCounter();
	CFPSCounter(const CFPSCounter &){}
	CFPSCounter& operator=(const CFPSCounter&){}
	~CFPSCounter(){};

	void Start();
	void Stop();
	void Update(); 
	static CFPSCounter& GetInstance(){ 
		static CFPSCounter inst;
		return inst; 
	}

	BOOL IsStopped() { return m_timerStopped; }
	float GetFPS() { return m_fps; }
	float GetRunningTime() { return m_runningTime; }
	float GetElapsedTime() { return m_timerStopped ? 0.0f : m_timeElapsed; } 
	float GetCurrentTime() { return (float)m_currentTime/ (float)m_ticksPerSecond; }

private:
	INT64 m_ticksPerSecond;
	INT64 m_currentTime;
	INT64 m_lastTime;
	INT64 m_lastFPSUpdate;
	INT64 m_FPSUpdateInterval;
	UINT m_numFrames;
	float m_runningTime;
	float m_timeElapsed;
	float m_fps;
	BOOL m_timerStopped;
};

#define FPSCounter CFPSCounter::GetInstance()