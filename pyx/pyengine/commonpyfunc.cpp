#include "commonpyfunc.h"
#include"customconsole.h"
#include <boost/locale/conversion.hpp>
#include <boost/locale/encoding.hpp>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


void cwrite(const char *sMsg, const char *sTextColor, const char *sBackColor)  //py²ãutf8, c++²ãgbk
{
	printc(boost::locale::conv::between(sMsg, "gbk", "utf8").c_str(), sTextColor, sBackColor);
}

