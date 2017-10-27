#include "main.h"

static struct item_i
{
	struct combatinfo
	{
		dice			one_hand;
		dice			two_hands;
		int				ac;
	};
	const char*			name[3];
	int					cost;
	combatinfo			combat;
} item_data[] = {
	{{"", ""}},
	//
	{{"Club", "Дубина"}, 1 * GP, {{1, 4}}},
	{{"Flail", "Цеп"}, 5 * GP, {{1, 6}, {1, 8}}},
	{{"Hammer", "Молот"}, 5 * GP, {{1, 6}, {1, 8}}},
	{{"Mace", "Булава"}, 5 * GP, {{1, 6}, {1, 8}}},
	{{"Spear", "Копье"}, 3 * GP, {{1, 6}, {1, 8}}},
	{{"Javelin", "Дротик"}, 1 * GP, {{1, 6}}},
	{{"Staff", "Посох"}, 1 * GP, {{0}, {1, 6}}},
	{{"Axe", "Топор"}, 7 * GP, {{1, 6}, {1, 8}}},
	{{"Halberd", "Алебарда"}, 10 * GP, {{0}, {1, 10}}},
	{{"Dagger", "Кинжал"}, 3 * GP, {{1, 4}}},
	{{"Greatsword", "Двуручный меч"}, 15 * GP, {{0}, {1, 10}}},
	{{"Longsword", "Меч"}, 10 * GP, {{1, 6}, {1, 8}}},
	{{"Shortsword", "Короткий меч"}, 7 * GP, {{1, 6}}},
	{{"Crossbow", "Арбалет"}, 30 * GP, {{1, 6}}},
	{{"Longbow", "Лук"}, 7 * GP, {{1, 6}}},
	{{"Shortbow", "Короткий лук"}, 3 * GP, {{1, 6}}},
	{{"Dart", "Дротик"}, 2 * GP, {{1, 4}}},
	{{"Sling", "Пращя"}, 2 * GP, {{1, 4}}},
	//
	{{"Stone", "Камень"}, 0},
	{{"Arrow", "Стрела"}, 5 * CP},
	{{"Bolt", "Болт"}, 1 * SP},
	// Items (armor)
	{{"Hide armor", "Меховая броня"}, 10 * GP, {{},{}, 1}},
	{{"Leather armor", "Кожанная броня"}, 20 * GP, {{}, {}, 2}},
	{{"Ring mail", "Кольчужная рубашка"}, 30 * GP, {{}, {}, 3}},
	{{"Scale mail", "Чешуйчатый доспех"}, 30 * GP, {{}, {}, 3}},
	{{"Chain mail", "Кольчуга"}, 40 * GP, {{}, {}, 4}},
	{{"Banded mail", "Кольцевой доспех"}, 50 * GP, {{}, {}, 5}},
	{{"Plate mail", "Латы"}, 60 * GP, {{}, {}, 6}},
	//
	{{"Shield", "Щит"}, 10 * GP, {{}, {}, 1}},
	{{"Helmet", "Шлем"}},
	{{"Bracers", "Наручи"}},
	// Items (other)
	{{"Ration", "Паек"}},
	{{"Apple", "Яблоко"}},
	//
	{{"Silver coins", "Серебрянная монета"}},
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

const char* item::getname() const
{
	return item_data[type].name[1];
}

bool item::islight() const
{
	return type == Dagger;
}

bool item::istwohanded() const
{
	return item_data[type].combat.one_hand.c == 0;
}