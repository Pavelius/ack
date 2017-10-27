#include "main.h"

void game::encounter(monster_s type)
{
	creature enemies[32]; memset(enemies, 0, sizeof(enemies));
	creature* combatants[40]; combatants[0] = 0;
	auto dice = game::getmonstercount(type, Dungeon);
	auto count = dice.roll();
	for(int i = 0; i < count; i++)
	{
		enemies[i].create(type);
		zcat(combatants, enemies + i);
	}
	logs::add("Внезапно показались %1i %2.", count, getstr(type));
	logs::next();
}

