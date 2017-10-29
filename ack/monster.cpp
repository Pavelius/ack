#include "main.h"

static struct monster_i
{
	const char*			name[3];
	race_s				race;
	gender_s			gender;
	class_s				type;
	alignment_s			alignment;
	char				level;
	int					experience;
	unsigned char		ability[6];
	dice				encounters[4];
} monster_data[] = {
	{{"orc","орк", "орков"}, Beastman, Male, Fighter, Chaotic, 1, 10, {10, 10, 10, 10, 10, 10}, {{2, 4}}},
	{{"zombie", "зомби", "зомби"}, Undead, Male, Fighter, Chaotic, 2, 10, {10, 10, 10, 10, 10, 10}, {{2, 4}}},
};
assert_enum(monster, Zombie);
getstr_enum(monster);

void creature::create(monster_s monster_type)
{
	auto& m = monster_data[monster_type];
	race = m.race;
	gender = m.gender;
	type = m.type;
	alignment = m.alignment;
	level = m.level;
	memcpy(ability, m.ability, sizeof(ability));
	hp = dice::roll(level, 8);
	name = m.name[1];
}

dice game::getmonstercount(monster_s id, encounter_type_s type)
{
	return monster_data[id].encounters[type];
}