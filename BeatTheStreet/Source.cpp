#include "game.h"//Game header file

int main()
{  	
	FreeConsole();//Hide console
	game game;	//Construct Game
	return game.loop();	//Run Loop 
}