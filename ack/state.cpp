#include "main.h"

logs::state logc;

logs::state::state() : information(logc.information)
{
}

logs::state::~state()
{
	logc.information = information;
}

char* toupper(char* result, const char* format)
{
	zcpy(result, format);
	szupper(result, 1);
	return result;
}

const char* logs::getpanel(int index)
{
	if(index == 0)
		return logc.information;
	return 0;
}