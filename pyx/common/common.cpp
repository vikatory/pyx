#include "common.h"
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

std::string operator * (const std::string &str, int times)
{
	string result;
	result.reserve(str.length() * times);  // �����ظ������·���
	for (int i = 0; i < times; i++)
		result.append(str);
	return result;
}



