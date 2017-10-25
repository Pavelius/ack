#include "main.h"

static char ability_bonus[] = {-4,
-4, -4, -3, -2, -2, -1, -1, -1, 0,
0, 0, 0, 1, 1, 1, 2, 2, 3};

void hero::clear()
{
	memset(this, 0, sizeof(*this));
}

const char* hero::getname() const
{
	return "";
}

int	hero::getbonus(ability_s id) const
{
	return maptbl(ability_bonus, (int)ability[id]);
}

int hero::getmaxhp() const
{
	return imin((int)level, mhp + getbonus(Constitution));
}