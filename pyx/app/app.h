#pragma once

#include <string>

class CApp
{
public:
	CApp();
	~CApp();
	void run();
	void exit();

private:
	void loop();
	std::string input();
	void processCmd(std::string cmd);

private:
	bool isExit = false;
};

