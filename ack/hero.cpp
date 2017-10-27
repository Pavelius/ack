#include "main.h"

static char ability_bonus[] = {-4,
-4, -4, -3, -2, -2, -1, -1, -1, 0,
0, 0, 0, 1, 1, 1, 2, 2, 3};

void hero::clear()
{
	memset(this, 0, sizeof(*this));
}

const char* hero::getname() const
{
	return "";
}

int	hero::getbonus(ability_s id) const
{
	return maptbl(ability_bonus, (int)ability[id]);
}

int hero::getmaxhp() const
{
	return imin((int)level, mhp + getbonus(Constitution));
}

int	hero::getarmor(bool flatfooted) const
{
	auto result = wear[Torso].getarmor();
	result += wear[Head].getarmor();
	result += wear[Legs].getarmor();
	if(!flatfooted)
	{
		result += wear[MeleeWeapon].getarmor();
		result += wear[SecondanaryWeapon].getarmor();
		result += getbonus(Dexterity);
	}
	return result;
}

int hero::getinitiative() const
{
	auto result = getbonus(Dexterity);
	return result;
}

static int base_attack(attack_progress_s type, int level)
{
	if(!level)
		return 11;
	switch(type)
	{
	case AsFighter: return 10 - ((level - 1) * 2) / 3;
	case AsCleric: return 10 - (level - 1) / 2;
	default: return 10 - (level - 1) / 3;
	}
	return 10;
}

int hero::getdifficult(skill_s value) const
{
	auto rang = get(value);
	if(!rang)
		return 30;
	return 21 - get(value)*4;
}

int hero::roll(skill_s value) const
{
	return 0;
}

void hero::damage(int value, bool interactive)
{
	if(interactive)
		logs::add("%1 получил%2 %3i повреждений", getname(), getA(), value);
	hp -= value;
	if(hp <= 0)
	{
		if(interactive)
			logs::add("и упал%1", getA());
	}
	logs::add(".");
}

bool hero::attack(hero* enemy, bool interactive, int bonus, bool flat_footed, wear_s weapon)
{
	damageinfo di;
	if(!getattack(di, weapon))
		return false;
	di.difficult += enemy->getarmor(flat_footed);
	di.difficult -= bonus;
	auto result = d20();
	if(result < di.difficult)
	{
		if(interactive)
			logs::add("%1 промазал%2", getname(), getA());
		return true;
	}
	if(interactive)
		logs::add("%1 попал%2", getname(), getA());
	enemy->damage(imin(1, di.damage.roll()), interactive);
	return true;
}

bool hero::getattack(damageinfo& result, wear_s slot) const
{
	result.difficult = base_attack(game::getattack(type), level);
	result.damage = dice::create(1, 2);
	if(wear[slot])
	{
		bool two_handed = false;
		if(slot == MeleeWeapon && !wear[SecondanaryWeapon])
			two_handed = true;
		result.damage = wear[slot].getdamage(two_handed);
	}
	if(slot == MeleeWeapon || slot == SecondanaryWeapon)
	{
		result.difficult -= getbonus(Strenght);
		result.damage.b += getbonus(Strenght);
	}
	else if(slot == RangedWeapon)
		result.difficult -= getbonus(Dexterity);
	return true;
}