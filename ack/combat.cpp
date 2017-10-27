#include "main.h"

enum combat_side_s {
	PartySide, EnemySide,
};

enum combat_action_s {
	ActionMeleeAttack, ActionRangeAttack,
};

struct combatant
{
	creature*		object;
	char			initiative;
	combat_side_s	side;

	operator bool() const { return object != 0; }
	
	bool isactive() const
	{
		return object->isactive();
	}

	bool isplayer() const
	{
		return object->isplayer();
	}

	const char* getname() const
	{
		return object->getname();
	}

	static int compare(const void* p1, const void* p2)
	{
		auto e1 = ((combatant*)p1);
		auto e2 = ((combatant*)p2);
		return e2->initiative - e1->initiative;
	}

};

static void roll_initiative(combatant* parcipants)
{
	for(auto p = parcipants; *p; p++)
		p->initiative = xrand(1, 6) + p->object->getinitiative();
	auto count = zlen(parcipants);
	qsort(parcipants, count, sizeof(parcipants[0]), combatant::compare);
}

static void make_actions(combatant* parcipant, combatant* enemy, bool interactive)
{
	damageinfo di;
	auto player = parcipant->object;
	if(player->getattack(di, MeleeWeapon))
	{
		if(di.weapon)
			logs::add(ActionMeleeAttack, "Броситься на врага давя его голыми руками");
		else
			logs::add(ActionMeleeAttack, "Броситься на врага, используя [%1]", di.weapon->getname());
	}
	auto id = logs::input(interactive, false, "Что будет делать [%1]?", player->getname());
	switch(id)
	{
	case ActionMeleeAttack:
		break;
	case ActionRangeAttack:
		break;
	}
}

static combatant* getenemy(combatant* parcipants, int side)
{
}

static void combat_round(combatant* parcipants)
{
	for(auto p = parcipants; *p; p++)
	{
		if(!p->isactive())
			continue;
		make_actions(p, 0, p->isplayer());
	}
}

void game::encounter(monster_s type)
{
	creature enemies[32]; memset(enemies, 0, sizeof(enemies));
	combatant combatants[40]; memset(combatants, 0, sizeof(combatants));
	auto dice = game::getmonstercount(type, Dungeon);
	auto count = dice.roll();
	for(int i = 0; i < count; i++)
	{
		enemies[i].create(type);
		combatants[i].object = enemies + i;
		combatants[i].side = EnemySide;
	}
	for(auto p : players)
	{
		if(!p)
			continue;
		auto& e = combatants[zlen(combatants)];
		e.object = p;
		e.side = PartySide;
	}
	roll_initiative(combatants);
	logs::add("Внезапно показались %1i %2.", count, getstr(type));
	combat_round(combatants);
}