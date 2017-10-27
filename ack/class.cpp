#include "main.h"

static int cleric_experience[15] = {0,
0, 1500, 3000, 6000, 12000, 24000, 50000, 100000, 200000,
300000, 400000, 500000, 600000, 700000};
static int fighter_experience[15] = {0,
0, 2000, 4000, 8000, 16000, 32000, 65000, 130000, 250000,
370000, 490000, 610000, 730000, 850000};
static int mage_experience[15] = {0,
0, 2500, 5000, 10000, 20000, 40000, 80000, 160000, 310000,
460000, 610000, 760000, 910000, 1060000};
static int theif_experience[15] = {0,
0, 1250, 2500, 5000, 10000, 20000, 40000, 80000, 180000,
280000, 380000, 480000, 580000, 680000};
static unsigned char fighter_attack[15] = {11,
10, 9, 9, 8, 7, 7, 6, 5, 5,
4, 3, 3, 2, 1};
static unsigned char cleric_attack[15] = {11,
10, 10, 9, 9, 8, 8, 7, 7, 6,
6, 5, 5, 4, 4};
static unsigned char mage_attack[15] = {11,
10, 10, 10, 9, 9, 9, 8, 8, 8,
7, 7, 7, 6, 6};

static struct class_i
{
	const char*			name[2];
	race_s				race;
	ability_s			prime;
	unsigned char		minimal[Charisma + 1];
	int*				experience;
	unsigned char		maximum_level;
	unsigned char*		attack;
	int					dice;
} class_data[] = {
	{{"Cleric", "Священник"}, Human, Wisdow, {0, 0, 0, 0, 9, 0}, cleric_experience, 14, cleric_attack, 6},
	{{"Fighter", "Воин"}, Human, Strenght, {9, 0, 0, 0, 0, 0}, fighter_experience, 14, fighter_attack, 8},
	{{"Mage", "Маг"}, Human, Intellegence, {0, 0, 0, 9, 0, 0}, mage_experience, 14, mage_attack, 4},
	{{"Theif", "Вор"}, Human, Dexterity, {0, 9, 0, 0, 0, 0}, theif_experience, 14, cleric_attack, 4},
};
assert_enum(class, LastClass);
getstr_enum(class);

race_s game::getrace(class_s id)
{
	return class_data[id].race;
}

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

unsigned char* game::getattack(class_s id)
{
	return class_data[id].attack;
}

int* game::getexperience(class_s id)
{
	return class_data[id].experience;
}

unsigned char game::getmaximumlevel(class_s id)
{
	return class_data[id].maximum_level;
}