#include "FPSCounter.h"

CFPSCounter::CFPSCounter(){
	QueryPerformanceFrequency( (LARGE_INTEGER *)&m_ticksPerSecond );
	m_currentTime = m_lastTime = m_lastFPSUpdate = 0;
	m_numFrames = 0;
	m_runningTime = m_timeElapsed = m_fps = 0.0f;
	m_FPSUpdateInterval = m_ticksPerSecond >> 1;
	m_timerStopped = TRUE;
}

void CFPSCounter::Start(){
	if ( !m_timerStopped ) return;
	QueryPerformanceCounter( (LARGE_INTEGER *)&m_lastTime );
	m_timerStopped = FALSE;
}

void CFPSCounter::Stop(){
	if ( m_timerStopped ) return;
	INT64 stopTime = 0;
	QueryPerformanceCounter( (LARGE_INTEGER *)&stopTime );
	m_runningTime += (float)(stopTime - m_lastTime) / (float)m_ticksPerSecond;
	m_timerStopped = TRUE;
}

void CFPSCounter::Update(){
	if ( m_timerStopped ){
		return;
	}
	QueryPerformanceCounter( (LARGE_INTEGER *)&m_currentTime );
	m_timeElapsed = (float)(m_currentTime - m_lastTime) / (float)m_ticksPerSecond;
	m_runningTime += m_timeElapsed;
	m_numFrames++;
	if ( m_currentTime - m_lastFPSUpdate >= m_FPSUpdateInterval ){
		float currentTime = (float)m_currentTime / (float)m_ticksPerSecond;
		float lastTime = (float)m_lastFPSUpdate / (float)m_ticksPerSecond;
		m_fps = (float)m_numFrames / (currentTime - lastTime);
		m_lastFPSUpdate = m_currentTime;
		m_numFrames = 0;
	}
	m_lastTime = m_currentTime;
}
