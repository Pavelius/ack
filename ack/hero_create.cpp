#include "main.h"

adat<hero, 260>		heroes;

static skill_s general_skills[] = {
	Alchemy, AnimalHusbandry, AnimalTraining, Bargaining, Caving,
	CollegiateWizardry, Diplomacy, Disguise, Endurance,
	Engineering, Gambling, Healing, Intimidation,
	Leadership, LipReading,
	Mapping, MilitaryStrategy, Mimicry, Naturalism, Navigation,
	Riding, Seafaring, Seduction, Signaling, Survival, Theology, Tracking, Trapping
};
static skill_s cleric_skills[] = {
	Apostasy, BattleMagic, BeastFriendship, CombatTrickery,
	Command, Contemplation, Diplomacy, DivineBlessing, DivineHealth,
	FightingStylePole, FightingStyleWeaponAndShield, Healing, History, LayingOnHands,
	Leadership, Loremastery, Engineering, MartialTraining, Prestidigitation,
	Prophecy, QuietMagic, RighteousTurning, SensingEvil, SensingPower,
	Theology
};

static void print_ability(unsigned char* ability)
{
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
	{
		if(i != Strenght)
			logs::add(", ");
		logs::add("%1 %2i", getstr(i), ability[i]);
	}
}

void hero::chooseability()
{
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		ability[i] = (rand() % 6) + (rand() % 6) + (rand() % 6) + 3;
}

static bool match_minimal(unsigned char* ability, unsigned char* minimal)
{
	for(auto i = 0; i < 6; i++)
	{
		if(ability[i] < minimal[i])
			return false;
	}
	return true;
}

void hero::chooseclass(bool interactive)
{
	logs::add("Ваши способности: ");
	print_ability(ability);
	logs::add(".");
	for(auto i = FirstClass; i <= LastClass; i = (class_s)(i + 1))
	{
		if(!match_minimal(ability, game::getminimal(i)))
			continue;
		logs::add(i, getstr(i));
	}
	logs::sort();
	type = (class_s)logs::input(interactive, false, "Выбрайте [класс]:");
}

void hero::choosegender(bool interactive)
{
	logs::add(Male, "Мужчина");
	logs::add(Female, "Женщина");
	logs::sort();
	gender = (gender_s)logs::input(interactive, false, "Выбрайте [пол]:");
}

void hero::chooseskills(bool interactive, skill_s* source, unsigned maximum, int count)
{
	while(count > 0)
	{
		for(unsigned i = 0; i < maximum; i++)
		{
			auto rang = get(source[i]);
			if(rang >= 3)
				continue;
			if(rang)
				logs::add(source[i], "%1x%2i", getstr(source[i]), rang + 1);
			else
				logs::add(source[i], getstr(source[i]));
		}
		auto result = (skill_s)logs::input(interactive, true, "Выбирайте [навык] (осталось %1i)", count);
		add(result, 1);
	}
}

static void choose_class_profiency(hero* player, bool interactive, int count)
{
	unsigned maximum = 0;
	skill_s source = 0;
	switch(player->type)
	{
	case Cleric:
		source = cleric_skills;
		maximum = sizeof(cleric_skills) / sizeof(cleric_skills[0]);
		break;
	default:
		return;
	}
	player->chooseskills(interactive, source, maximum, count);
}

void hero::levelup(bool interactive)
{
	level++;
	mhp += xrand(1, game::getdice(type));
	if(level == 1)
	{
		hp = getmaxhp();
		auto general_ability_count = 1 + imax(0, getbonus(Intellegence));
		chooseskills(interactive, general_skills, sizeof(general_skills) / sizeof(general_skills[0]), general_ability_count);
		choose_class_profiency(this, interactive, 1);
	}
	else
	{
		switch(level)
		{
		case 5:
		case 9:
		case 13:
			chooseskills(interactive, general_skills, sizeof(general_skills) / sizeof(general_skills[0]), 1);
			break;
		}
		if((level%getprogress()) == 0)
			choose_class_profiency(this, interactive, 1);
	}
}

hero* hero::create(bool interactive)
{
	auto p = heroes.add();
	if(!p)
		return 0;
	p->clear();
	p->chooseability();
	p->choosegender(interactive);
	p->chooseclass(interactive);
	p->levelup(interactive);
	return p;
}