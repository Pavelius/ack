#include "main.h"

adat<creature, 260>		heroes;
creature*				players[7];

static char ability_bonus[] = {-4,
-4, -4, -3, -2, -2, -1, -1, -1, 0,
0, 0, 0, 1, 1, 1, 2, 2, 3};

void creature::clear()
{
	memset(this, 0, sizeof(*this));
}

const char* creature::getname() const
{
	return name;
}

int	creature::getbonus(ability_s id) const
{
	return maptbl(ability_bonus, (int)ability[id]);
}

int creature::gethp() const
{
	return hp;
}

int creature::getmaxhp() const
{
	auto result = mhp + getbonus(Constitution);
	if(result < level)
		result = level;
	return result;
}

int	creature::getarmor(bool flatfooted) const
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

int creature::getinitiative() const
{
	auto result = getbonus(Dexterity);
	return result;
}

int creature::getdifficult(skill_s value) const
{
	auto rang = get(value);
	if(!rang)
		return 30;
	return 21 - get(value) * 4;
}

int creature::roll(skill_s value) const
{
	return 0;
}

void creature::damage(int value, bool interactive)
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

bool creature::attack(creature* enemy, bool interactive, int bonus, bool flat_footed, wear_s weapon)
{
	damageinfo di;
	if(!getattack(di, weapon))
		return false;
	di.difficult += enemy->getarmor(flat_footed);
	di.difficult -= bonus;
	if(flat_footed)
		di.difficult += 4;
	auto result = d20();
	if(result < di.difficult)
	{
		if(interactive)
			logs::add("%1 промазал%2.", getname(), getA());
		return true;
	}
	if(interactive)
		logs::add("%1 попал%2.", getname(), getA());
	auto damage = di.damage.roll();
	if(damage < 0)
		damage = 1;
	enemy->damage(damage, interactive);
	return true;
}

bool creature::getattack(damageinfo& result, wear_s slot) const
{
	memset(&result, 0, sizeof(result));
	result.difficult = game::getattack(type)[imin((unsigned char)14, level)];
	result.damage = dice::create(1, 2);
	if(wear[slot])
	{
		bool two_handed = false;
		if(slot == MeleeWeapon && !wear[SecondanaryWeapon])
			two_handed = true;
		result.weapon = (item*)(wear + slot);
		result.damage = result.weapon->getdamage(two_handed);
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

bool creature::isplayer() const
{
	return zchr(players, (creature*)this) != 0;
}

bool creature::islevelup() const
{
	auto max_level = game::getmaximumlevel(type);
	if(level >= max_level)
		return false;
	auto next_experience = game::getexperience(type)[level + 1];
	return experince >= next_experience;
}

void creature::create(bool interactive, bool add_party)
{
	clear();
	this->race = game::getrace(type);
	chooseability();
	choosegender(interactive);
	chooseclass(interactive);
	chooseequipment(interactive);
	while(islevelup())
		levelup(interactive);
	if(add_party)
	{
		name = game::getname(game::getrandomname(race, gender));
		zcat(players, this);
	}
}