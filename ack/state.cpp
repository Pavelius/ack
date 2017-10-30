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
		zcat(result, "[-�����]");
	else
		zcat(result, logc.player->getname());
}

static void print_player_a(char* result)
{
	static const char* strings[] = {0, "�"};
	gender_sensitive(result, logc.player, strings);
}

static void print_player_as(char* result)
{
	static const char* strings[] = {"��", "���"};
	gender_sensitive(result, logc.player, strings);
}

static void print_opponent(char* result)
{
	if(!logc.opponent)
		zcat(result, "[-��������]");
	else
		zcat(result, logc.opponent->getname());
}

static void print_opponent_a(char* result)
{
	static const char* strings[] = {0, "�"};
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
	{"�", print_opponent_a},
	{"�", print_player_a},
	{"���", print_player_as},
	{"�����", print_player},
	{"��������", print_opponent},
};
static stringcreator::plugin plugin(elements, sizeof(elements));