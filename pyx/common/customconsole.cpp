#include"customconsole.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;


#if PE_PLATFORM == PLATFORM_WIN32
#include <windows.h>

typedef pair<string, bool> sipair;

bool operator<(const sipair & a, const sipair & b)
{
	return (a.first < b.first) || (a.first == b.first && a.second < b.second);
}

static map<sipair, int> g_ConsoleColors = map<sipair, int> {
	{make_pair("red",       false), FOREGROUND_RED},
	{make_pair("red_h",     false), FOREGROUND_RED | FOREGROUND_INTENSITY},
	{make_pair("green",     false), FOREGROUND_GREEN},
	{make_pair("green_h",   false), FOREGROUND_GREEN | FOREGROUND_INTENSITY},
	{make_pair("blue",      false), FOREGROUND_BLUE},
	{make_pair("blue_h",    false), FOREGROUND_BLUE | FOREGROUND_INTENSITY},
	{make_pair("yellow",    false), FOREGROUND_RED | FOREGROUND_GREEN},
	{make_pair("yellow_h",  false), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY},
	{make_pair("cyan",      false), FOREGROUND_GREEN | FOREGROUND_BLUE},
	{make_pair("cyan_h",    false), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY},
	{make_pair("magenta",   false), FOREGROUND_BLUE | FOREGROUND_RED},
	{make_pair("magenta_h", false), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY},
	{make_pair("white",     false), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE},
	{make_pair("white_h",   false), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY},
	{make_pair("red",       true),  BACKGROUND_RED},
	{make_pair("red_h",     true),  BACKGROUND_RED | BACKGROUND_INTENSITY},
	{make_pair("green",     true),  BACKGROUND_GREEN},
	{make_pair("green_h",   true),  BACKGROUND_GREEN | BACKGROUND_INTENSITY},
	{make_pair("blue",      true),  BACKGROUND_BLUE},
	{make_pair("blue_h",    true),  BACKGROUND_BLUE | BACKGROUND_INTENSITY},
	{make_pair("yellow",    true),  BACKGROUND_RED | BACKGROUND_GREEN},
	{make_pair("yellow_h",  true),  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY},
	{make_pair("cyan",      true),  BACKGROUND_GREEN | BACKGROUND_BLUE},
	{make_pair("cyan_h",    true),  BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY},
	{make_pair("magenta",   true),  BACKGROUND_BLUE | BACKGROUND_RED},
	{make_pair("magenta_h", true),  BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY},
	{make_pair("white",     true),  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE},
	{make_pair("white_h",   true),  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY},
};

WORD GetForeColor(const char* sTextColor)
{
	if (sTextColor == "")
		return g_ConsoleColors[make_pair("white", false)];
	return g_ConsoleColors[make_pair(string(sTextColor), false)];
}

WORD GetBackColor(const char* sBackColor)
{
	return g_ConsoleColors[make_pair(sBackColor, true)];
}

template<typename AnyType>
void _wprintc(AnyType text, const char *textColor, const char *backColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle == 0)
		return;
	WORD fore = GetForeColor(textColor);
	//WORD back = GetBackColor(backColor);

	//CONSOLE_SCREEN_BUFFER_INFO console_info;
	//GetConsoleScreenBufferInfo(handle, &console_info);
	//SetConsoleTextAttribute(handle, fore | back | 128);
	SetConsoleTextAttribute(handle, fore);
	std::cout << text;
	fore = GetForeColor("white_h");
	SetConsoleTextAttribute(handle, fore);
	//CloseHandle(handle);
}
#endif


void printc(const char *sMsg, const char *sTextColor, const char *sBackColor)
{
#if PE_PLATFORM == PLATFORM_WIN32
	_wprintc(sMsg, sTextColor, sBackColor);
#else
	cout << sMsg;
#endif
}



