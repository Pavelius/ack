#include "main.h"

static monster_i monster_data[] = {
	{{"orc","орк", "орков"}, Beastman, Male, Fighter, Chaotic, 1, 10, 3, {10, 10, 10, 10, 10, 10}, {{2, 4}}},
	{{"zombie", "зомби", "зомби"}, Undead, Male, Fighter, Chaotic, 2, 10, 1, {10, 10, 10, 10, 10, 10}, {{2, 4}}},
};
assert_enum(monster, Zombie);
getstr_enum(monster);

void creature::create(monster_s monster_type)
{
	monster = monster_data + monster_type;
	race = monster->race;
	gender = monster->gender;
	type = monster->type;
	alignment = monster->alignment;
	level = monster->level;
	memcpy(ability, monster->ability, sizeof(ability));
	hp = dice::roll(level, 8);
}

dice game::getmonstercount(monster_s id, encounter_type_s type)
{
	return monster_data[id].encounters[type];
}