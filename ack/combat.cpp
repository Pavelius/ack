#include "main.h"

const unsigned combatant_max = 32;

enum combat_side_s {
	PartySide, EnemySide,
};
enum combat_state_s {
	ReadyToFight, FlatFooted,
};
enum combat_action_s {
	ActionMeleeAttack, ActionRangeAttack,
};

static struct combatant
{
	creature*		object;
	char			initiative;
	combat_side_s	side;
	combat_state_s	state;

	operator bool() const { return object != 0; }
	
	bool isactive() const
	{
		return object->isactive();
	}

	bool isplayer() const
	{
		return object->isplayer();
	}

	bool isflatfooted() const
	{
		return state == FlatFooted;
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

} combatants[combatant_max + 8];;

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
			logs::add(ActionMeleeAttack, "Броситься на врага, используя [%1]", di.weapon->getname());
		else
			logs::add(ActionMeleeAttack, "Броситься на врага давя его голыми руками");
	}
	auto id = logs::input(interactive, false, "Что будет делать [%1]?", player->getname());
	logs::add("\n");
	switch(id)
	{
	case ActionMeleeAttack:
		player->attack(enemy->object, true);
		break;
	case ActionRangeAttack:
		player->attack(enemy->object, true, 0, enemy->isflatfooted(), RangedWeapon);
		break;
	}
}

static combatant* getenemy(combatant* parcipants, int side)
{
}

static bool combat_round(combatant* parcipants)
{
	for(auto p = parcipants; *p; p++)
	{
		if(!p->isactive())
			continue;
		// Получим список врагов
		combatant* enemies[combatant_max]; enemies[0] = 0;
		for(auto pe = parcipants; *pe; pe++)
		{
			if(!pe->isactive() || p->side==pe->side)
				continue;
			zcat(enemies, pe);
		}
		if(!enemies[0])
			return false;
		// Выполним действие по конкретному врагу
		make_actions(p, enemies[0], p->isplayer());
	}
	return true;
}

bool game::isgameover()
{
	for(auto p : players)
	{
		if(!p || !p->isactive())
			continue;
		return false;
	}
	logs::add("Все игроки мертвы. Игра окончена.");
	return true;
}

void game::encounter(monster_s type)
{
	creature enemies[combatant_max];
	memset(enemies, 0, sizeof(enemies));
	memset(combatants, 0, sizeof(combatants));
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
	while(true)
	{
		if(!combat_round(combatants))
			break;
		logs::next();
	}
	if(!isgameover())
		logs::add("Все враги мертвы.");
	logs::next();
}