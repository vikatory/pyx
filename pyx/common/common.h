#pragma once
#include <string>

std::string operator * (const std::string &str, int times);

#define RETURN_IF(condition) if(condition) return;

