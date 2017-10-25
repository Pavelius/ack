#include "main.h"

struct ability_i
{
	const char*		name[2];
} ability_data[] = {
	{{"Strenght", "Сила"}},
	{{"Dexterity", "Ловкость"}},
	{{"Constitution", "Телосложение"}},
	{{"Intellegence", "Интеллект"}},
	{{"Wisdow", "Мудрость"}},
	{{"Charisma", "Харизма"}},
};
assert_enum(ability, Charisma);
getstr_enum(ability);