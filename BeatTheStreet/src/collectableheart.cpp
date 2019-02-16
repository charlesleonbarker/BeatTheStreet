/* Charles Barker
P15181036
March 2017 */

//Input and Output Library.
#include <iostream>

//SFML Library for graphics.
#include <SFML/Graphics.hpp>

//Class header file.
#include "collectableheart.h"

//libraries used in the randomization of the x-position.
#include <cstdlib> 
#include <ctime> 

//Constructor
collectableLives::collectableLives()
{
	//Load the texture of the life from file
	if (!tHeartTexture.loadFromFile(".\\Assets\\graphics\\heart.png")) EXIT_FAILURE;

	//Set the texture of the sprite
	sCollectableLife.setTexture(tHeartTexture);

	//Set origin of sprite
	sCollectableLife.setOrigin(25.0f, 50.0f);

	//Initiate Clock for Anamation.
	sf::Clock cAnamationClock;

	//set first frame
	iFrameNumber = 0;
}

//Void function for drawing the life to the render window.
void collectableLives::drawLifes(sf::RenderWindow & window)
{
	//Fade-in time is taken from the clock, which is reset whenever a new life is shown.
	int iFadeInTime = cLifeFadeInClock.getElapsedTime().asMilliseconds();

	//the sprite will fade in lineally over the first 1000 milliseconds.
	if (iFadeInTime < 1000) setTransparancy(iFadeInTime / 10);

	//If the time is over 1000 ms, the heart will be fully bright.
	else setTransparancy(100);

	//The sprite is drawn.
	window.draw(sCollectableLife);
}

//void function that is called when a new collectible life is needed on screen. The players y-position is used a a parameter so that the life can be put as far away as possible.
void collectableLives::newheart(float frogy)
{
	//Restart the fade in clock so that when the life is drawn it fades in.
	cLifeFadeInClock.restart();

	//Depending on where the frog is, the life is drawn in different places.
	if (frogy == 805 || frogy == 505) v2fLifePosition.y = 55;
	if (frogy == 355 || frogy == 55) v2fLifePosition.y = 805;

	//The x-position is set using the setx function, this randomizes the position.
	v2fLifePosition.x = setx();
	
	//Position is set for when it is drawn.
	sCollectableLife.setPosition(v2fLifePosition);
}

//void function that is called when a life is collected, it moves the heart off the screen to a position where it cannot be reached.
void collectableLives::removeLife()
{
	sCollectableLife.setPosition(-100,-100);
}

//Boolean function that returns true when the correctable life intersects with the FloatRect that is a parameter.
bool collectableLives::lifeContact(sf::FloatRect frPlayerBounds)
{
	if (sCollectableLife.getGlobalBounds().intersects(frPlayerBounds))
	{
		return true;
	}
	else return false;
}

//float function that return a random x position for the collectible life to be positioned at.
float collectableLives::setx()
{
	//Random number generated between 1-16 and placed in itempIntiger
	srand(time(NULL));
	int iTempIntiger = rand() % 16 + 1;

	//Depending on the random number generated return 
		 if (iTempIntiger == 1 ) return 25;
	else if (iTempIntiger == 2 ) return 75;
	else if (iTempIntiger == 3 ) return 125;
	else if (iTempIntiger == 4 ) return 175;
	else if (iTempIntiger == 5 ) return 225;
	else if (iTempIntiger == 6 ) return 275;
	else if (iTempIntiger == 7 ) return 325;
	else if (iTempIntiger == 8 ) return 375;
	else if (iTempIntiger == 9 ) return 425;
	else if (iTempIntiger == 10) return 475;
	else if (iTempIntiger == 11) return 525;
	else if (iTempIntiger == 12) return 575;
	else if (iTempIntiger == 13) return 625;
	else if (iTempIntiger == 14) return 675;
	else if (iTempIntiger == 15) return 725;
	else if (iTempIntiger == 16) return 775;
	else return 245; //default 
}

//Void function used to set the transparency, the percentage opaque is passed into the function as a parameter.
void collectableLives::setTransparancy(float iPercent)
{
	//In the rgba scale alpha controls translucency and is measured between 0-255. The percentage parameter is times by 2.55 to give a true value
	int iAlphaAmmount = (2.55 * iPercent);

	//Set the color for the player, with all values to max , except for the alpha
	sf::Color cLifeColor(255, 255, 255, iAlphaAmmount);

	//The players color is set
	sCollectableLife.setColor(cLifeColor);
}

//Function that returns a float of the sprites y-position
float collectableLives::spriteYPosition()
{
	return sCollectableLife.getPosition().y;
}

void collectableLives::anamate()
{
	sf::Time tAnamationTime = cAnamationClock.getElapsedTime();

	if (tAnamationTime.asMilliseconds() > 100) 
	{
		iFrameNumber++;
		if (iFrameNumber == 5) iFrameNumber = 0;
		cAnamationClock.restart();
	}

	if (iFrameNumber == 0)			sCollectableLife.setTextureRect(sf::IntRect(0  , 0, 50, 75));
	else if (iFrameNumber == 1)     sCollectableLife.setTextureRect(sf::IntRect(50 , 0, 50, 75));
	else if (iFrameNumber == 2)     sCollectableLife.setTextureRect(sf::IntRect(100, 0, 50, 75));
	else if (iFrameNumber == 3)     sCollectableLife.setTextureRect(sf::IntRect(150, 0, 50, 75));
	else if  (iFrameNumber == 4)    sCollectableLife.setTextureRect(sf::IntRect(200, 0, 50, 75));

}
