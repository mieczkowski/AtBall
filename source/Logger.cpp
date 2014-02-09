#include "Logger.h"
using namespace std;
CLogger::CLogger(){
	logToConsole = false;
	consoleActivated = false;
	logToFile = true;
	consoleTitle = "Logger";
	ofstream file("log.txt");
	if(file.is_open()){
		file << "Uruchomienie systemu logujacego..." << std::endl;
		file.close();
	}
	EnableConsole(false);
}
void CLogger::EnableConsole(bool state){
	logToConsole = state;
	if(logToConsole == TRUE && consoleActivated == FALSE){
		if(AllocConsole() == TRUE){
			SetConsoleTitle(consoleTitle.c_str());
			consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
			consoleActivated = TRUE;
		}else{
			logToConsole = FALSE;
			consoleActivated = FALSE;
		}
	}else if(logToConsole == FALSE && consoleActivated == TRUE){
		FreeConsole();
		consoleActivated = FALSE;
	}
}
void CLogger::Log(string message){
	Log(message, false);
}
void CLogger::Log(string cls, string method, string message){
	Log(cls, method, message, false);
}
void CLogger::Log(string message, bool error){
	messages.push_back(message);
	if(logToFile == false) return;
	ofstream file("log.txt", ios::app);
	if(file.is_open()){
		file << message << std::endl;
		file.close();
	}
	if(consoleActivated){
		if(error) SetConsoleTextAttribute(consoleOut, L_FATAL);
		else SetConsoleTextAttribute(consoleOut, L_INFO);
		message += "\n\r";
		WriteConsole(consoleOut, message.data(), (DWORD)message.length(), &byteSaved, 0);
	}	
}

void CLogger::Log(string cls, string method, string message, bool error){
	ostringstream os;
	if(error){
		os << "<< ERROR >> ";
	}
	os << cls << ": (" << method << ") " << message;
	string msg = os.str();
		
	messages.push_back(msg);
	if(logToFile == false) return;
	ofstream file("log.txt", ios::app);
	if(file.is_open()){
		file << msg << std::endl;
		file.close();
	}
	if(consoleActivated){
		if(error) SetConsoleTextAttribute(consoleOut, L_FATAL);
		else SetConsoleTextAttribute(consoleOut, L_INFO);
		msg += "\n\r";
		WriteConsole(consoleOut, msg.data(), (DWORD)msg.length(), &byteSaved, 0);
	}	
}