#include "main.h"

static struct item_i
{
	struct combatinfo
	{
		dice			one_hand;
		dice			two_hands;
		int				ac;
	};
	const char*			name[2];
	int					cost;
	combatinfo			combat;
} item_data[] = {
	{{"", ""}},
	//
	{{"Club", ""}, 1 * GP, {{1, 4}}},
	{{"Flail", ""}, 5 * GP, {{1, 6}, {1, 8}}},
	{{"Hammer", ""}, 5 * GP, {{1, 6}, {1, 8}}},
	{{"Mace", ""}, 5 * GP, {{1, 6}, {1, 8}}},
	{{"Spear", ""}, 3 * GP, {{1, 6}, {1, 8}}},
	{{"Javelin", ""}, 1 * GP, {{1, 6}}},
	{{"Staff", ""}, 1 * GP, {{0}, {1, 6}}},
	{{"Axe", ""}, 7 * GP, {{1, 6}, {1, 8}}},
	{{"Halberd", ""}, 10 * GP, {{0}, {1, 10}}},
	{{"Dagger", ""}, 3 * GP, {{1, 4}}},
	{{"Greatsword", ""}, 15 * GP, {{0}, {1, 10}}},
	{{"Longsword", ""}, 10 * GP, {{1, 6}, {1, 8}}},
	{{"Shortsword", ""}, 7 * GP, {{1, 6}}},
	{{"Crossbow", ""}, 30 * GP, {{1, 6}}},
	{{"Longbow", ""}, 7 * GP, {{1, 6}}},
	{{"Shortbow", ""}, 3 * GP, {{1, 6}}},
	{{"Dart", ""}, 2 * GP, {{1, 4}}},
	{{"Sling", ""}, 2 * GP, {{1, 4}}},
	//
	{{"Stone", ""}, 0},
	{{"Arrow", ""}, 5 * CP},
	{{"Bolt", ""}, 1 * SP},
	// Items (armor)
	{{"Hide armor", ""}, 10 * GP, {{},{}, 1}},
	{{"Leather armor", ""}, 20 * GP, {{}, {}, 2}},
	{{"Ring mail", ""}, 30 * GP, {{}, {}, 3}},
	{{"Scale mail", ""}, 30 * GP, {{}, {}, 3}},
	{{"Chain mail", ""}, 40 * GP, {{}, {}, 4}},
	{{"Banded mail", ""}, 50 * GP, {{}, {}, 5}},
	{{"Plate mail", ""}, 60 * GP, {{}, {}, 6}},
	//
	{{"Shield", ""}, 10 * GP, {{}, {}, 1}},
	{{"Helmet", ""}},
	{{"Bracers", ""}},
	// Items (other)
	{{"Ration", ""}},
	{{"Apple", ""}},
	//
	{{"Silver coins", ""}},
};
assert_enum(item, LastItem);
getstr_enum(item);

int item::getarmor() const
{
	return item_data[type].combat.ac;
}

const dice& item::getdamage(bool two_handed) const
{
	if(two_handed)
		return item_data[type].combat.two_hands;
	else
		return item_data[type].combat.one_hand;
}

bool item::islight() const
{
	return type == Dagger;
}

bool item::istwohanded() const
{
	return item_data[type].combat.one_hand.c == 0;
}