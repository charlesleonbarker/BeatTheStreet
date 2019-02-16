#pragma once
/* Charles Barker
P15181036
March 2017 */

//Input and Output Library.
#include <iostream>

//SFML Library for graphics.
#include <SFML/Graphics.hpp>



class obsticle {
public:
	//Default constructor
	obsticle();

	//Constructor
	obsticle(int vehicletype, float lane, bool direction, float hStart);

	//Void function that draws the sprite to the screen.
	void drawObsticle(sf::RenderWindow &window);

	//Void function that moves the sprite along the lane
	void moveObsticle(float extraspeed);

	//Boolean function that returns true if the sprite contacts the floatrect parameter.
	bool playerContact(sf::FloatRect frogglobalbounds , bool log);

private:

	//Private textures and sprites tat are used in multiple functions within the class
	sf::Texture oTexture;
	sf::Sprite oSprite;
	std::string objectTextureDirectory;

	//Initalise variables for use in multiple functions within the class
	bool bObsticalDirection;
	float fSpeedOfStrip;
	float fLane;
	float vStart;

	//Bool true if the vehicle is a train
	bool bIsTrain;
};