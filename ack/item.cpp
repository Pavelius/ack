#include "main.h"

bool item::islight() const
{
	return type == Dagger;
}

bool item::istwohanded() const
{
	return type == SwordGreat
		|| type == Halberd;
}