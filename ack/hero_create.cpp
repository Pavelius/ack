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
static skill_s fighter_skills[] = {
	Acrobatics, Alertness, Berserkergang,
	BlindFighting, CombatReflexes, CombatTrickery, Command, DungeonBashing, Endurance,
	FightingStyleDualWeapon, FightingStyleMissile, FightingStylePole, FightingStyleSigle, FightingStyleTwoHanded, FightingStyleWeaponAndShield,
	Gambling, Intimidation, Leadership, MilitaryStrategy, PreciseShooting,
	Riding, Running, Engineering, Skirmishing, Survival, Swashbuckling, WeaponFinesse,
	WeaponFocusAxes, WeaponFocusBows, WeaponFocusSwords
};
static skill_s mage_skills[] = {
	Alchemy, BattleMagic, BeastFriendship, BlackLoreOfZahar, CollegiateWizardry,
	Diplomacy, Elementalism, Engineering, Familiar, Healing,
	IllusionResistance, History, Loremastery, Engineering, Mapping, MysticAura,
	Naturalism, QuietMagic, Prestidigitation, SensingPower, Transmogrification
};
static skill_s theif_skills[] = {
	Acrobatics, Alertness,
	BlindFighting, Bribery, CatBurglary, CombatReflexes, CombatTrickery,
	Contortionism, Diplomacy,
	FightingStyleDualWeapon, FightingStyleMissile, FightingStylePole, FightingStyleSigle, FightingStyleTwoHanded, FightingStyleWeaponAndShield,
	Gambling, Intimidation, LipReading, Lockpicking, Mapping, PreciseShooting,
	Riding, Running, Seafaring, Skirmishing, Skulking, Sniping, Swashbuckling,
	TrapFinding, WeaponFinesse,
	WeaponFocusSwords
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

void hero::chooseskills(bool interactive, const char* skill_name, skill_s* source, unsigned maximum, int count)
{
	while(count > 0)
	{
		for(unsigned i = 0; i < maximum; i++)
		{
			auto rang = get(source[i]);
			if(rang >= 3)
				continue;
			if(rang)
				logs::add(source[i], "%1 x%2i", getstr(source[i]), rang + 1);
			else
				logs::add(source[i], getstr(source[i]));
		}
		auto result = (skill_s)logs::input(interactive, true, "Выбирайте [%1 навык] (осталось %2i)", skill_name, count);
		add(result, 1);
		count--;
	}
}

static void choose_class_general(hero* player, bool interactive, int count)
{
	player->chooseskills(interactive, "общий", general_skills, sizeof(general_skills) / sizeof(general_skills[0]), count);
}

static void choose_class_profiency(hero* player, bool interactive, int count)
{
	unsigned maximum = 0;
	skill_s* source = 0;
	switch(player->type)
	{
	case Cleric:
		source = cleric_skills;
		maximum = sizeof(cleric_skills) / sizeof(cleric_skills[0]);
		break;
	case Fighter:
		source = fighter_skills;
		maximum = sizeof(fighter_skills) / sizeof(fighter_skills[0]);
		break;
	case Mage:
		source = mage_skills;
		maximum = sizeof(mage_skills) / sizeof(mage_skills[0]);
		break;
	case Theif:
		source = theif_skills;
		maximum = sizeof(theif_skills) / sizeof(theif_skills[0]);
		break;
	default:
		return;
	}
	player->chooseskills(interactive, "классовый", source, maximum, count);
}

void hero::levelup(bool interactive)
{
	level++;
	mhp += xrand(1, game::getdice(type));
	if(level == 1)
	{
		hp = getmaxhp();
		choose_class_general(this, interactive, 1 + imax(0, getbonus(Intellegence)));
		choose_class_profiency(this, interactive, 1);
	}
	else
	{
		switch(level)
		{
		case 5:
		case 9:
		case 13:
			choose_class_general(this, interactive, 1);
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