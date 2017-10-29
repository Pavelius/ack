#include "main.h"

struct names
{
	race_s		race;
	gender_s	gender;
	const char*	name[2];
};
static names objects[] = {
	{Human, Male, {"Hawke","�����"}},
	{Human, Male, {"Rudiger","�������"}},
	{Human, Male, {"Gregor","������"}},
	{Human, Female, {"Brianne","�����"}},
	{Human, Male, {"Walton","�������"}},
	{Human, Male, {"Castor","������"}},
	{Human, Female, {"Shanna","�����"}},
	{Human, Male, {"Ajax","�����"}},
	{Human, Female, {"Hob","���"}},
	{Halfling, Female, {"Finnegan","�������"}},
	{Halfling, Female, {"Olive","������"}},
	{Halfling, Male, {"Randolph","��������"}},
	{Halfling, Female, {"Bartleby","�������"}},
	{Halfling, Male, {"Aubrey","������"}},
	{Halfling, Male, {"Baldwin","�������"}},
	{Halfling, Female, {"Becca","�����"}},
	{Elf, Female, {"Elohiir","�������"}},
	{Elf, Female, {"Sharaseth","�������"}},
	{Elf, Male, {"Hasrith","������"}},
	{Elf, Male, {"Shevara","�������"}},
	{Elf, Male, {"Cadeus","������"}},
	{Elf, Male, {"Eldar","������"}},
	{Elf, Female, {"Kithracet","��������"}},
	{Elf, Female, {"Thelian","��������"}},
	{Dwarf, Male, {"Ozruk","�����"}},
	{Dwarf, Male, {"Surtur","������"}},
	{Dwarf, Female, {"Brunhilda","���������"}},
	{Dwarf, Female, {"Annika","������"}},
	{Dwarf, Male, {"Janos","������"}},
	{Dwarf, Female, {"Greta","������"}},
	{Dwarf, Male, {"Dim","���"}},
	{Dwarf, Male, {"Rundrig","�������"}},
	{Dwarf, Male, {"Jar","����"}},
	{Dwarf, Male, {"Xotoq","������"}},
	//
	{Dwarf, Female, {"Durga", "�����"}},
	{Dwarf, Male, {"Aelfar", "������"}},
	{Dwarf, Female, {"Gerda", "�����"}},
	{Dwarf, Male, {"Rurgosh", "������"}},
	{Dwarf, Male, {"Bjorn", "�����"}},
	{Dwarf, Male, {"Drummond", "�������"}},
	{Dwarf, Female, {"Helga", "������"}},
	{Dwarf, Female, {"Siggrun", "������"}},
	{Dwarf, Female, {"Freya", "����"}},
	{Human, Male, {"Wesley", "������"}},
	{Human, Male, {"Brinton", "�������"}},
	{Human, Male, {"Jon", "���"}},
	{Human, Female, {"Sara", "����"}},
	{Human, Male, {"Hawthorn", "�������"}},
	{Human, Female, {"Elise", "����"}},
	{Human, Male, {"Clarke", "�����"}},
	{Human, Male, {"Lenore", "�����"}},
	{Human, Male, {"Piotr", "����"}},
	{Human, Male, {"Dahlia", "������"}},
	{Human, Female, {"Carmine", "������"}},
};

static int selectnames(unsigned char* elements, race_s* race, gender_s gender)
{
	auto p = elements;
	for(int i = 0; i < sizeof(objects) / sizeof(objects[0]); i++)
	{
		if(objects[i].gender != gender)
			continue;
		if(race && objects[i].race != *race)
			continue;
		*p++ = i;
	}
	return p - elements;
}

unsigned char game::getrandomname(race_s race, gender_s gender)
{
	unsigned char elements[sizeof(objects) / sizeof(objects[0])];
	int count = selectnames(elements, &race, gender);
	if(!count)
		count = selectnames(elements, 0, gender);
	if(!count)
		return 0;
	return elements[rand() % count];
}

const char* game::getname(unsigned char index)
{
	return objects[index].name[1];
}