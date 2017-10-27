#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("ACK");
	auto hero_size = sizeof(creature);
	creature players[4];
	players[0].create(false, true);
	players[1].create(false, true);
	game::encounter(Ork);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	return main(0, 0);
}