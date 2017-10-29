#include "main.h"

struct names
{
	race_s		race;
	gender_s	gender;
	const char*	name[2];
};
static names objects[] = {
	{Human, Male, {"Hawke","Хавки"}},
	{Human, Male, {"Rudiger","Рудигер"}},
	{Human, Male, {"Gregor","Грегор"}},
	{Human, Female, {"Brianne","Бриан"}},
	{Human, Male, {"Walton","Вальтон"}},
	{Human, Male, {"Castor","Кастор"}},
	{Human, Female, {"Shanna","Шанна"}},
	{Human, Male, {"Ajax","Айакс"}},
	{Human, Female, {"Hob","Хоб"}},
	{Halfling, Female, {"Finnegan","Финганн"}},
	{Halfling, Female, {"Olive","Оливия"}},
	{Halfling, Male, {"Randolph","Рэндольф"}},
	{Halfling, Female, {"Bartleby","Батлбай"}},
	{Halfling, Male, {"Aubrey","Аурбей"}},
	{Halfling, Male, {"Baldwin","Балдвин"}},
	{Halfling, Female, {"Becca","Бэкки"}},
	{Elf, Female, {"Elohiir","Эйлохир"}},
	{Elf, Female, {"Sharaseth","Харасез"}},
	{Elf, Male, {"Hasrith","Хазрич"}},
	{Elf, Male, {"Shevara","Шеварал"}},
	{Elf, Male, {"Cadeus","Кадиус"}},
	{Elf, Male, {"Eldar","Эльдар"}},
	{Elf, Female, {"Kithracet","Котораса"}},
	{Elf, Female, {"Thelian","Фелианна"}},
	{Dwarf, Male, {"Ozruk","Озрук"}},
	{Dwarf, Male, {"Surtur","Суртур"}},
	{Dwarf, Female, {"Brunhilda","Брундилла"}},
	{Dwarf, Female, {"Annika","Анника"}},
	{Dwarf, Male, {"Janos","Джанос"}},
	{Dwarf, Female, {"Greta","Гретта"}},
	{Dwarf, Male, {"Dim","Дим"}},
	{Dwarf, Male, {"Rundrig","Рундриг"}},
	{Dwarf, Male, {"Jar","Жарл"}},
	{Dwarf, Male, {"Xotoq","Ксоток"}},
	//
	{Dwarf, Female, {"Durga", "Дурга"}},
	{Dwarf, Male, {"Aelfar", "Ольфар"}},
	{Dwarf, Female, {"Gerda", "Герда"}},
	{Dwarf, Male, {"Rurgosh", "Ругрош"}},
	{Dwarf, Male, {"Bjorn", "Бьерн"}},
	{Dwarf, Male, {"Drummond", "Друмонд"}},
	{Dwarf, Female, {"Helga", "Хельга"}},
	{Dwarf, Female, {"Siggrun", "Сигрин"}},
	{Dwarf, Female, {"Freya", "Фрея"}},
	{Human, Male, {"Wesley", "Вислей"}},
	{Human, Male, {"Brinton", "Бринтон"}},
	{Human, Male, {"Jon", "Йон"}},
	{Human, Female, {"Sara", "Сара"}},
	{Human, Male, {"Hawthorn", "Хавторн"}},
	{Human, Female, {"Elise", "Элис"}},
	{Human, Male, {"Clarke", "Кларк"}},
	{Human, Male, {"Lenore", "Линор"}},
	{Human, Male, {"Piotr", "Петр"}},
	{Human, Male, {"Dahlia", "Данила"}},
	{Human, Female, {"Carmine", "Кармин"}},
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