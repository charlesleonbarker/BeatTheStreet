#pragma once
/* Charles Barker
P15181036
March 2017 */

//SFML Library for graphics.
#include <SFML/Graphics.hpp>


class Presents
{
public:

	//Constructor
	Presents();

	//Void function for drawing the Present to the render window.
	void drawPresent(sf::RenderWindow &window);

	//Void function that is called whenever a present is collected, it moves the sprite into a new positions.
	void movePresent();

	//Boolean function that returns true when the sprite is intersecting with the floatRect parameter.
	bool presentContact(sf::FloatRect frogglobalbounds);

	//Function that returns a float of the sprites y-position
	float YPosition();

	//float function that return a random x position for the collectible life to be positioned at.
	float setx();

	//Boolean function that returns if the player is moving up or down the map
	bool playerMovingDown();

	//void function used to change texture for anamation
	void anamate();

private:

	//Void function used to set the transparency, the percentage opaque is passed into the function as a parameter.
	void settransparancy(int percent);
	
	//Variables used in class
	sf::Sprite sCoinSprite;
	sf::Texture tCoinTexture;
	sf::Vector2f coinpos;
	sf::Clock cPresentFadeInClock;
	sf::Clock cAnamationClock2;

	//Int variable for anamation frames
	int iFrameNumber;

	//boolean variable used in the class do determine which way the player is moving
	bool bPlayerMovingDown;
	

};
