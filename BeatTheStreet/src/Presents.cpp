/* Charles Barker
P15181036
March 2017 */

//Input and Output Library.
#include <iostream>

//SFML Library for graphics.
#include <SFML/Graphics.hpp>

//Class header file.
#include "Presents.h"

//libraries used in the randomization of the x-position.
#include <cstdlib> 
#include <ctime> 

//Constructor
Presents::Presents()
{
	//The player moves up and down the screen collecting presents. If the player is moving down, the boolean variable bPlayerMovingDown is true. this is used to set the position of the next present.
	bPlayerMovingDown = false;

	//load the texture from file.
	if (!tCoinTexture.loadFromFile(".\\Assets\\graphics\\present.png")) EXIT_FAILURE;

	//setting the  origin of the sprite
	sCoinSprite.setOrigin(25.0f, 50.0f);

	//setting the texture of the sprite
	sCoinSprite.setTexture(tCoinTexture);

	sCoinSprite.setTextureRect(sf::IntRect(0, 0, 50, 75));
	//The y position of the sprite is set to where the first collectible present will be.
	coinpos.y = 505;

	//the x position is set randomly using the setx function
	coinpos.x = setx();

	//Initiate Clock for Anamation.
	sf::Clock cAnamationClock;

	//Set posision
	sCoinSprite.setPosition(coinpos);

	//Set first frame of anamation
	iFrameNumber = 0;
}

//Void function for drawing the Present to the render window.
void Presents::drawPresent(sf::RenderWindow & window)
{
	//Fade-in time is taken from the clock, which is reset whenever a new present is shown.
	int iTimeSpentFadingInInMilliseconds = cPresentFadeInClock.getElapsedTime().asMilliseconds();
	
	//the sprite will fade in lineally over the first 1000 milliseconds.
	if (iTimeSpentFadingInInMilliseconds < 1000) settransparancy(iTimeSpentFadingInInMilliseconds / 10);
	
	//If the time is over 1000 ms, the life will be fully bright.
	else settransparancy(100);

	//The sprite is drawn.
	window.draw(sCoinSprite);
}

//Void function that is called whenever a present is collected, it moves the sprite into a new positions.
void Presents::movePresent()
{
	//Depending on where the present was when it was collected, it gets moved into a new position.
	if (coinpos.y == 55) {
		//When the player collects the present from the very top of the screen, the boolean variable is set to true to show that the player is now working down the screen.
		bPlayerMovingDown = true;
		coinpos.y = 355;
	}
	else if (coinpos.y == 355) {
		if (bPlayerMovingDown)//If the player is moving down the screen, the present gets moved to a different position than if it where moving up the screen.
		{
			coinpos.y = 505;
		}
		else coinpos.y = 55;
	}
	else if (coinpos.y == 505) {
		if (bPlayerMovingDown)//If the player is moving down the screen, the present gets moved to a different position than if it where moving up the screen.
		{
			coinpos.y = 805;
		}
		else coinpos.y = 355;
	}
	else if (coinpos.y == 805) {
		coinpos.y = 505;
		//When the player collects the present from the very top of the screen, the boolean variable is set to false to show that the player is now working up the screen.
		bPlayerMovingDown = false;
	}

	//After the coins y position is set, the x position is then randomly set using the setx function;
	coinpos.x = setx();

	//sprite position is then set.
	sCoinSprite.setPosition(coinpos);

	// fade in clock is then reset so that when the sprite is drawn, it knows to set transparency accordingly.
	cPresentFadeInClock.restart();
}

//Boolean function that returns true when the sprite is intersecting with the floatRect parameter.
bool Presents::presentContact(sf::FloatRect frogglobalbounds)
{

	if (sCoinSprite.getGlobalBounds().intersects(frogglobalbounds))
	{
		return true;
	}
	else return false;
}

//float function that return a random x position for the collectible life to be positioned at.
float Presents::setx()
{
	//Random number generated between 1-16 and placed in itempIntiger
	int itempIntiger = rand() % 16 + 1;

		 if (itempIntiger == 1 ) return 25;
	else if (itempIntiger == 2 ) return 75;
	else if (itempIntiger == 3 ) return 125;
	else if (itempIntiger == 4 ) return 175;
	else if (itempIntiger == 5 ) return 225;
	else if (itempIntiger == 6 ) return 275;
	else if (itempIntiger == 7 ) return 325;
	else if (itempIntiger == 8 ) return 375;
	else if (itempIntiger == 9 ) return 425;
	else if (itempIntiger == 10) return 475;
	else if (itempIntiger == 11) return 525;
	else if (itempIntiger == 12) return 575;
	else if (itempIntiger == 13) return 625;
	else if (itempIntiger == 14) return 675;
	else if (itempIntiger == 15) return 725;
	else if (itempIntiger == 16) return 775;

}

//Boolean function that returns if the player is moving up or down the map
bool Presents::playerMovingDown()
{
	return bPlayerMovingDown;
}

//void function used to change texture for anamation
void Presents::anamate()
{
	//Anamation time is set from the anamation clock.
	sf::Time tAnamationTime2 = cAnamationClock2.getElapsedTime();

	if (tAnamationTime2.asMilliseconds() > 100)//every 100ms
	{
		//add one to frame number
		iFrameNumber++;

		//if frame number is four reset it abck to 0, this is because there are only 4 frames.
		if (iFrameNumber == 4) iFrameNumber = 0;

		//Change intrect when frame number changes.
		if (iFrameNumber == 0)			sCoinSprite.setTextureRect(sf::IntRect(0, 0, 50, 75));
		else if (iFrameNumber == 1)     sCoinSprite.setTextureRect(sf::IntRect(50, 0, 50, 75));
		else if (iFrameNumber == 2)     sCoinSprite.setTextureRect(sf::IntRect(100, 0, 50, 75));
		else if (iFrameNumber == 3)     sCoinSprite.setTextureRect(sf::IntRect(150, 0, 50, 75));

		//clock is reset when frame is changed
		cAnamationClock2.restart();
	}
}

//Void function used to set the transparency, the percentage opaque is passed into the function as a parameter.
void Presents::settransparancy(int iPercent)
{
	//In the rgba scale alpha controls translucency and is measured between 0-255. The percentage parameter is times by 2.55 to give a true value
	int iAlphaAmmount = (2.55 * iPercent);

	//Set the color for the player, with all values to max , except for the alpha
	sf::Color cPresentColor(255, 255, 255, iAlphaAmmount);

	//The players color is set
	sCoinSprite.setColor(cPresentColor);

}

//Function that returns a float of the sprites y-position
float Presents::YPosition()
{
	return sCoinSprite.getPosition().y;
}
