#include "main.h"

logs::state::state() : information(logs::information)
{
}

logs::state::~state()
{
	logs::information = information;
}

char* toupper(char* result, const char* format)
{
	zcpy(result, format);
	szupper(result, 1);
	return result;
}