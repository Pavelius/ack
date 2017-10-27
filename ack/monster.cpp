#include "main.h"

static struct monster_i
{
	const char*			name[2];
	race_s				race;
	gender_s			gender;
	class_s				type;
	alignment_s			alignment;
	char				level;
	int					experience;
	unsigned char		ability[6];
} monster_data[] = {
	{{"Orc","Îðê"}, Beastman, Male, Fighter, Chaotic, 1, 10, {10, 10, 10, 10, 10, 10}},
};