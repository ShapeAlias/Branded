#include "system.h"
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	System* system;
	bool result;

	system = new System;
	if (!system)
	{
		return -1;
	}

	result = system->init();
	if (result)
	{
		system->run();
	}

	system->shutDown();
	delete system;
	system = NULL;

	return 0;
}