#pragma once
/* Charles Barker
P15181036
March 2017 */

//Input and Output Library
#include <iostream>

#include <windows.h>

//SFML Library for graphics and audio.
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp> 

//Include header files for classes.
#include "player.h"
#include "obsticle.h"
#include "lives.h"
#include "button.h"
#include "Presents.h"
#include "collectableheart.h"


class game
{
public:

	//Constructor
	game();

	//Int function for the aplication loop 
	int loop();

	//Bool function that displays the menu and returns true when the user has chosen to start the game.
	bool bGameMenu();

	//Int function for the main game loop
	int iGameLoop();

	//Fail screen function, displays the end menu once the player has lost all lives, it returnes an intiger depending on what the player chooses to do next.
	int iFailScreen();

	//string function that converts the elapsed time to a string, used to display time taken.
	std::string sTimeToString(int iTimetakenInMilliseconds);

private:

	//Render window, used in the game class, named window
	sf::RenderWindow *window;

	//Initiate background music
	sf::Music *mBackgroundMusic;

	//Variables used in multiple functions within the class.
	bool bMute;
	int iTimeTaken;
	int iPresentsCollected;
};

