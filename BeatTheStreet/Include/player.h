#pragma once
/* Charles Barker
P15181036
March 2017 */

//Input and Output Library.
#include <iostream>

//SFML Library for graphics.
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Player {

public:

	//Constructor.
	Player();

	//Void function  that draws the sprite to the window, the render window is passed through by reference
	void drawPlayer(sf::RenderWindow &window);

	//Void function used to move the sprites position, direction is passed in as a parameter.
	void movePlayer(char direction);

	//Void function for player movement in the y-axis when on a boat, "extraspeed" is passed through for when presents are collected.
	void moveOnBoat(float fExtraSpeed);

	//float function that returns the x-position of the sprites origin.
	float playerXPosition();

	//float function that returns the y-position of the sprites origin.
	float playerYPosition();

	//FloatRect function that returns a set of bounds used in determining if the player has contacted an obstacle.
	sf::FloatRect playerIntercectBounds();

	//Void function used to reset the sprite after it has died.
	void resetPlayer(bool bPLayerMovingDown);

	//int function that returns the number of lives after taking one away.
	int lostLife(bool bMute);

	//int function that returns the number of lives after adding one.
	int gainedlife();

	//int function that returns the current number of lives that the player has.
	int getlives();

	//boolean function that returns true in the player is within the water segment of the map.
	bool water();

private:

	//Void function used to set the transparency, the percentage opaque is passed into the function as a parameter.
	void settransparancy(float iPercent);

	//Number of lives that the player has.
	int iPlayerLives;

	//Player Sprite
	sf::Sprite sPlayer;

	//Textures for the player in each orientation.
	sf::Texture pTextureBack;
	sf::Texture pTextureFront;
	sf::Texture pTextureLeft;
	sf::Texture pTextureRight;

	//Clock used to fade in the sprite when	the position is reset. Used in multiple functions.
	sf::Clock playerfadeinclock;

	//Initalise sounds and sound buffers used in class
	sf::SoundBuffer sbSplashBuffer, sbCollideBuffer;
	sf::Sound sSplashSound, sCollideSound;
};
