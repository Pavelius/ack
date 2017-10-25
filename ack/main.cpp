#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("ACK");
	auto hero_size = sizeof(hero);
	auto p = hero::create(true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	return main(0, 0);
}