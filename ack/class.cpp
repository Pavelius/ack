#include "main.h"

static struct class_i
{
	const char*			name[2];
	ability_s			prime;
	unsigned char		minimal[Charisma + 1];
	int					dice;
} class_data[] = {
	{{"Cleric", "Священник"}, Wisdow, {0, 0, 0, 0, 9, 0}, 6},
	{{"Fighter", "Воин"}, Strenght, {9, 0, 0, 0, 0, 0}, 8},
	{{"Mage", "Маг"}, Intellegence, {0, 0, 0, 9, 0, 0}, 4},
	{{"Theif", "Вор"}, Dexterity, {0, 9, 0, 0, 0, 0}, 4},
};
assert_enum(class, LastClass);
getstr_enum(class);

ability_s game::getprime(class_s id)
{
	return class_data[id].prime;
}

unsigned char* game::getminimal(class_s id)
{
	return class_data[id].minimal;
}

int game::getdice(class_s id)
{
	return class_data[id].dice;
}