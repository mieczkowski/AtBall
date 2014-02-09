#pragma once
#include <string>
#include <map>
#include <ctime>
#include <iostream>
using namespace std;
class CTimer;
class CTimerMgr{
public:
	CTimerMgr(){}
	CTimerMgr(const CTimerMgr &){}
	CTimerMgr& operator=(const CTimerMgr&){}
	~CTimerMgr(){}
	static CTimerMgr& GetInstance(){
		static CTimerMgr inst;
		return inst;
	}
	void Clear();
	void Update();
	void Pause();
	void Resume();
	bool AddTimer(string name, CTimer* object);
	CTimer* GetTimer(string name);
	void RemoveTimer(string name);
protected:
	map<string, class CTimer*> timerList;
};

#define TimerMgr CTimerMgr::GetInstance()

class CCallback;

class CTimer{
public:
	virtual void Pause(){
		if(paused) return;
		paused = true;
		pauseTime = clock();
	}
	~CTimer();
	virtual void Resume() = 0;
	virtual void Check() = 0;
	void Stop(){finished = true;}
	bool IsFinished(){ return finished; }
	void SetCallback(CCallback *tmpCallback){ callback = tmpCallback; }
protected:
	bool finished;
	bool paused;
	clock_t pauseTime;
	clock_t start;
	CCallback *callback;
};

//prosty timer z czasem startu i konca
class CTimerSimple : public CTimer{
public:
	CTimerSimple(float seconds);
	void Check();
	void Resume();
protected:
	clock_t end;
};

//to samo co simple ale wykonuje caly czas callback
class CTimerCounting : public CTimerSimple{
public:
	CTimerCounting(float seconds) : CTimerSimple(seconds){}
	void Check();
};

class CCallback{
public:
	virtual void Execute(clock_t time) = 0;
};
enum CallbackFunctionType{
	CFT_NEXTSTATUS, CFT_COUNTER
};
class CCallbackEngine : public CCallback{
public:
	CCallbackEngine(CallbackFunctionType tmpType){ type = tmpType; }
	virtual void Execute(clock_t time);
protected:
	CallbackFunctionType type;
};

class CCallbackLua : public CCallback{
public:
	CCallbackLua(string tmpName){ name = tmpName; }
	virtual void Execute(clock_t time);
protected:
	string name;
};






/*
clock_t begin, now;
begin = clock();
int seconds = 1;
clock_t end = begin + seconds * CLOCKS_PER_SEC;
int i = 1;
while(true){
now = clock();
if(now > end){
cout << "TICK!" << endl;
end = begin + seconds * (++i) * CLOCKS_PER_SEC;
}
}

// variable definitions on to calculate time taken
elapTicks = EndTimer(begin);    // stop the timer, and calculete the time taken
elapMilli = elapTicks/1000;     // milliseconds from Begin to End
elapSeconds = elapMilli/1000;   // seconds from Begin to End
elapMinutes = elapSeconds/60;   // minutes from Begin to End

printf ("Milliseconds passed: %.2f\n", elapMilli);
printf ("Seconds passed: %.2f\n", elapSeconds);
printf ("Minutes passed: %.2f", elapMinutes);

// hold the window open
char dummy;
scanf ("%c", &dummy);
return 0;
}
*/