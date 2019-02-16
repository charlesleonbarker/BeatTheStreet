#pragma once
/* Charles Barker
P15181036
March 2017 */

//SFML Library for graphics.
#include <SFML/Graphics.hpp>

class collectableLives{
public:

	//Constructor
	collectableLives();

	//Void function for drawing the heart to the render window.
	void drawLifes(sf::RenderWindow &window);

	//void function that i called when a new collectible life is needed on screen. The players y-position is used a a parameter so that the life can be put as far away as possible.
	void newheart(float frogy);

	//void function that is called when a life is collected, it moves the heart off the screen to a positioned where it cannot be reached.
	void removeLife();

	//Boolean function that returns true when the collectible life intersects with the FloatRect that is a parameter.
	bool lifeContact(sf::FloatRect frogglobalbounds);

	//float function that return a random x position for the collectible life to be positioned at.
	float setx();

	//Function that returns a float of the sprites y-position.
	float spriteYPosition();

	//void function used to change texture for anamation.
	void anamate();

private:

	//Void function used to set the transparency, the percentage opaque is passed into the function as a parameter.
	void setTransparancy(float iPercent);
	
	//Public variables used in multiple functions within the class
	sf::Sprite sCollectableLife;
	sf::Texture tHeartTexture;
	sf::Vector2f v2fLifePosition;
	sf::Clock cLifeFadeInClock;
	sf::Clock cAnamationClock;
	

	//Int variable for anamation frames
	int iFrameNumber;

};

