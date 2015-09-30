#include "app.h"
#include "common.h"
#include "pyengine.h"
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
using namespace std;


CApp::CApp()
{
}

CApp::~CApp()
{
}

void CApp::run()
{
	loop();
}

void CApp::loop()
{
	while (!isExit)
	{
		string cmd = input();
		processCmd(cmd);
	}
}

string CApp::input()
{
	cout << string("=") * 80 << endl;
	cout << "输入指令:";
	char cmd[256];
	cin.getline(cmd, 256);
	return cmd;
}

//   指令名    指令名          指令        参数                       
//  +---------+---------------+-----------+---------------------------------------------+
//  添加物品   addItem         ai          序号 物品名
//  +---------+---------------+-----------+---------------------------------------------+
//  保存文件   save            save         
//  +---------+---------------+-----------+---------------------------------------------+


void CApp::processCmd(string cmd)
{
	vector<string> tokens;
	boost::split(tokens, cmd, boost::is_any_of(" "));
	for_each(tokens.begin(), tokens.end(), [](string &s) {boost::trim(s); });
	tokens.erase(remove_if(tokens.begin(), tokens.end(), [](string s) {return s == ""; }), tokens.end());
	if (tokens.size() < 1) return;
	string sCmdName = tokens[0];

	try
	{
		tokens.erase(tokens.begin());

		if (sCmdName == "cr")
		{
		}
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
		cout << "指令解析错误" << endl;
	}
}


void CApp::exit()
{
	isExit = true;
}

