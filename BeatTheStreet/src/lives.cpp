#pragma once 
/* Charles Barker
P15181036
March 2017 */

//Input and Output Library.
#include <iostream>

//SFML Library for graphics.
#include <SFML/Graphics.hpp>

//header file for class
#include "lives.h"

//Constructor 
livesRemaining::livesRemaining()
{
	sf::Vector2f lSize(120.f, 30.0f);
	
	//Load sorite sheet
	if (!tLifeIconTexture.loadFromFile(".\\Assets\\graphics\\life.png")) EXIT_FAILURE;

	lSprite.setTexture(tLifeIconTexture);
	lSprite.setTextureRect(sf::IntRect(0, 0, 62, 20));
	lSprite.setScale(lSize.x / tLifeIconTexture.getSize().x, (lSize.y / tLifeIconTexture.getSize().y )* 3);
	lSprite.setOrigin(0 , 0);
	lSprite.setPosition(0, 0);
}

//Function that draws the graphic for the number of lives remaining.
void livesRemaining::drawlives(sf::RenderWindow &window,int numberoflives)
{
	//Depending on the number of lives that the player has, a different graphic is shown to represent this.
	//Number of lives is only ever 3, 2, or 1.
	if (numberoflives == 3)
	{
		//texture is set for corresponding lives.
		lSprite.setTextureRect(sf::IntRect(0, 0, 62, 20));
	}
	else if (numberoflives == 2)
	{
		lSprite.setTextureRect(sf::IntRect(0, 20, 62, 20));
	}
	else  lSprite.setTextureRect(sf::IntRect(0, 40, 62, 20));

	//sprite is drawn
	window.draw(lSprite);
}