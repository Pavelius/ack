#include "main.h"

logs::state::state() : information(logs::information)
{
}

logs::state::~state()
{
	logs::information = information;
}