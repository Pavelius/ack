#include "main.h"
#include "stringcreator.h"

logs::state logc;

logs::state::state() : information(logc.information)
{
}

logs::state::~state()
{
	logc.information = information;
}

static void gender_sensitive(char* result, const creature* player, const char** strings)
{
	if(!player)
		return;
	auto p = strings[player->gender];
	if(p)
		zcat(result, p);
}

static void print_player(char* result)
{
	if(!logc.player)
		zcat(result, "[-игрок]");
	else
		zcat(result, logc.player->getname());
}

static void print_player_a(char* result)
{
	static const char* strings[] = {0, "а"};
	gender_sensitive(result, logc.player, strings);
}

static void print_player_as(char* result)
{
	static const char* strings[] = {"ся", "ась"};
	gender_sensitive(result, logc.player, strings);
}

static void print_opponent(char* result)
{
	if(!logc.opponent)
		zcat(result, "[-оппонент]");
	else
		zcat(result, logc.opponent->getname());
}

static void print_opponent_a(char* result)
{
	static const char* strings[] = {0, "а"};
	gender_sensitive(result, logc.opponent, strings);
}

char* toupper(char* result, const char* format)
{
	zcpy(result, format);
	szupper(result, 1);
	return result;
}

const char* logs::getpanel(int index)
{
	if(index == 0)
		return logc.information;
	return 0;
}

static stringcreator::plugin::element elements[] = {
	{"А", print_opponent_a},
	{"а", print_player_a},
	{"ась", print_player_as},
	{"игрок", print_player},
	{"оппонент", print_opponent},
};
static stringcreator::plugin plugin(elements, sizeof(elements));