#pragma once 
/* Charles Barker
P15181036
March 2017 */

//Input and Output Library.
#include <iostream>

//SFML Library for graphics.
#include <SFML/Graphics.hpp>


class livesRemaining{
public:

	//Constructor
	livesRemaining();

	//Function that draws the graphic for the number of lives remaining.
	void drawlives(sf::RenderWindow &window, int numberoflives);

private:

	//private textures and sprites that are used in multiple functions within the class. 
	sf::Texture tLifeIconTexture;
	sf::Sprite lSprite;
	
};

