#include "main.h"
#include "stringcreator.h"

hero* text_player;

static void get_hero(char* result)
{
	zcpy(result, text_player->getname());
}

//static void get_A(char* result)
//{
//	zcpy(result, text_player->getA());
//}
//
//static void get_AS(char* result)
//{
//	zcpy(result, text_player->getAS());
//}
//
//static void get_LA(char* result)
//{
//	zcpy(result, text_player->getLA());
//}

static stringcreator::plugin::element elements[] = {
	//{"а", get_A},
	//{"ась", get_AS},
	{"герой", get_hero},
//	{"ла", get_AS},
};
static stringcreator::plugin plugin(elements, sizeof(elements));