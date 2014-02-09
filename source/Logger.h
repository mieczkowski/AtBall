#pragma once
#include "stdfx.h"
#include <vector>
using namespace std;
enum LOG_TYPE{
	L_INFO = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY,
	L_FATAL = BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY
};

class CLogger{
private:
	CLogger();
public:
	static CLogger& Instance(){
		static CLogger inst;
		return inst;
	}
	~CLogger(){
		if(consoleActivated == TRUE) FreeConsole();
	}
	void Log(string message);
	void Log(string cls, string method, string message);
	void Log(string message, bool error);
	void Log(string cls, string method, string message, bool error);
	vector<string> *GetMessages(){ return &messages; }
	vector<string> messages;

	void EnableConsole(bool state);
private:
	bool logToFile;
	bool logToConsole;
	BOOL consoleActivated;
	HANDLE consoleOut;
	DWORD byteSaved;
	string consoleTitle;
	LOG_TYPE defaultType;
};

#define LOGEX(message) CLogger::Instance().Log(message)
#define LOG(cls, method, message) CLogger::Instance().Log(cls, method, message)
#define ELOGEX(message) CLogger::Instance().Log(message, true)
#define ELOG(cls, method, message) CLogger::Instance().Log(cls, method, message, true)

#include <iostream>
#include <sstream>
#include <fstream>
template <typename T>
string Str( const T & t ) {
	ostringstream os;
	os << t;
	return os.str();
}