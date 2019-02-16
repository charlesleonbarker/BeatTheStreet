/* Charles Barker
P15181036
March 2017 */

//Input and Output Library.
#include <iostream>

//SFML Library for graphics and audio.
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


//Class header file.
#include "player.h"

//Constructor for initializing the object.
Player::Player()
{

	//Size of sprite used when setting scale
	sf::Vector2f size(50.f, 75.f);											
	
	//Load textures from file.
	if (!pTextureRight.loadFromFile(".\\Assets\\graphics\\frogright.png")) EXIT_FAILURE;
	if (!pTextureLeft.loadFromFile(".\\Assets\\graphics\\frogleft.png")) EXIT_FAILURE;
	if (!pTextureBack.loadFromFile(".\\Assets\\graphics\\frogback.png")) EXIT_FAILURE;
	if (!pTextureFront.loadFromFile(".\\Assets\\graphics\\frogfront.png")) EXIT_FAILURE;

	//Set the texture of the sprite so that the character is initially facing away.
	sPlayer.setTexture(pTextureBack);

	//Set origin and position
	sPlayer.setOrigin(25, 50);
	sPlayer.setPosition(400, 805);

	//Player starts with 3 lives
	iPlayerLives = 3;

	//Load files into sound buffers
	if (!sbSplashBuffer.loadFromFile(".\\Assets\\audio\\splash.ogg"))EXIT_FAILURE;
	if (!sbCollideBuffer.loadFromFile(".\\Assets\\audio\\playerhit.ogg"))EXIT_FAILURE;

	//Set sounds to sound buffers
	sSplashSound.setBuffer(sbSplashBuffer);
	sCollideSound.setBuffer(sbCollideBuffer);
}

//Void function  that draws the sprite to the window, the render window is passed through by reference.
void Player::drawPlayer(sf::RenderWindow &window)
{
	int itimetofadeininms = playerfadeinclock.getElapsedTime().asMilliseconds();
	if (itimetofadeininms < 1000) settransparancy(itimetofadeininms / 10);
	else settransparancy(100);
	window.draw(sPlayer);
}

//Void function used to move the sprites position, direction is passed in as a parameter.
void Player::movePlayer(char direction)
{
	//Initialize variables
	float fDistanceToLeft, fDistanceToRight;

	//fDistanceToLeft and fDistanceToRight are the distances between the sprite and the x axis window bounds. They are used to make sure the player doesn't move off the screen.
	fDistanceToLeft =   -25 + sPlayer.getPosition().x;
	fDistanceToRight =  775 - sPlayer.getPosition().x;
	
	//Initialize boolean variables.
	//Boolean variables are used to indicate if there is at least 50px to the side of the sprite to move into.
	bool validMoveUp, validMoveDown, validMoveLeft, validMoveRight;

	//If there is space for the player to move into the bool is set to true.
	if (sPlayer.getPosition().x < 75) validMoveLeft = false;
	else validMoveLeft = true;
	if (sPlayer.getPosition().x > 725) validMoveRight = false;
	else validMoveRight = true;
	if (sPlayer.getPosition().y < 105) validMoveUp = false;
	else validMoveUp = true;
	if (sPlayer.getPosition().y > 755) validMoveDown = false;
	else validMoveDown = true;


	if (playerfadeinclock.getElapsedTime().asSeconds() > 1)//Only allows player movement once the sprite has finished fading in.
	{
		//Depending on the direction passed in, and if there is a valid move, the player is moved and the texture is changed
		if (direction == 'u' && validMoveUp == true)
		{
			sPlayer.setTexture(pTextureBack);
			sPlayer.move(0, -50);
		}
		else if (direction == 'd' && validMoveDown == true)
		{
			sPlayer.setTexture(pTextureFront);
			sPlayer.move(0, 50);
		}
		else if (direction == 'l' && validMoveLeft == true)
		{
			sPlayer.setTexture(pTextureLeft);
			sPlayer.move(-50, 0);
		}
		else if (direction == 'r' && validMoveRight == true)
		{
			sPlayer.setTexture(pTextureRight);
			sPlayer.move(50, 0);
		}

		//If there isn't a valid move (so less than 50px), the player gets moved into the available space, using the distance to left variables
		else if (direction == 'l' && validMoveLeft == false)
		{
			sPlayer.setTexture(pTextureLeft);
			sPlayer.move(-fDistanceToLeft, 0);
		}
		else if (direction == 'r' && validMoveRight == false)
		{
			sPlayer.setTexture(pTextureRight);
			sPlayer.move(fDistanceToRight, 0);
		}
	}
}

//Void function for player movement in the y-axis when on a boat, extraspeed is passed through for when presents are collected.
void Player::moveOnBoat(float fExtraSpeed)
{
	float fMoveOnLogSpeed;

	//The movement speed is dependent in which water lane the player is in.
	if (sPlayer.getPosition().y >  80 && sPlayer.getPosition().y < 130) { fMoveOnLogSpeed = 5; }
	else if (sPlayer.getPosition().y > 130 && sPlayer.getPosition().y < 180) { fMoveOnLogSpeed = -4; }
	else if (sPlayer.getPosition().y > 180 && sPlayer.getPosition().y < 230) { fMoveOnLogSpeed = 3; }
	else if (sPlayer.getPosition().y > 230 && sPlayer.getPosition().y < 280) { fMoveOnLogSpeed = -2; }
	else if (sPlayer.getPosition().y > 280 && sPlayer.getPosition().y < 330) { fMoveOnLogSpeed = 1; }

	//Extra speed is added which changes as more presents are collected.
	if (fMoveOnLogSpeed < 0)fMoveOnLogSpeed = fMoveOnLogSpeed  - fExtraSpeed;
	else if (fMoveOnLogSpeed > 0) fMoveOnLogSpeed = fMoveOnLogSpeed + fExtraSpeed;

	//Move the player
	sPlayer.move(fMoveOnLogSpeed, 0);
}

//float function that returns the x-position of the sprites origin.
float Player::playerXPosition()
{
	return sPlayer.getPosition().x;
}

//float function that returns the y-position of the sprites origin.
float Player::playerYPosition()
{
	return  sPlayer.getPosition().y;
}

//FloatRect function that returns a set of bounds used in determining if the player has contacted an obstacle.
sf::FloatRect Player::playerIntercectBounds()
{
		//FloatRect that will be returned
		sf::FloatRect frPlayerGlobalBounds;

		//Global bounds from the player sprite are taken and modified for the return FloatRect
		frPlayerGlobalBounds.left = sPlayer.getGlobalBounds().left;
		frPlayerGlobalBounds.top = sPlayer.getGlobalBounds().top + 25;
		frPlayerGlobalBounds.width = sPlayer.getGlobalBounds().width;
		frPlayerGlobalBounds.height = sPlayer.getGlobalBounds().height - 50;
		
		//FloatRect is returned
		return frPlayerGlobalBounds;
}

//Void function used to reset the sprite after it has died.
void Player::resetPlayer(bool bPLayerMovingDown)
{
	//Thh player will respawn at the begining of the area where they died.

	//Initalise variabvle for y respawn location.
	float  iRespawnY;

	//Depending on where the player dies, and which direction they where traveling the player will respawn in a diffrent location.
	if (playerYPosition() == 105 || playerYPosition() == 155 || playerYPosition() == 205 || playerYPosition() == 255 || playerYPosition() == 305)
	{//Drowned
		if (bPLayerMovingDown == true) iRespawnY = 55;
		else iRespawnY = 355;
	}

	else if (playerYPosition() == 405 || playerYPosition() == 455) 
	{//Hit by train
		if (bPLayerMovingDown == true) iRespawnY = 355;
		else iRespawnY = 505;
	}

	else if (playerYPosition() == 555 ||  playerYPosition() == 605 || playerYPosition() == 655 || playerYPosition() == 705 || playerYPosition() == 755)
	{//Hit by Car
		if (bPLayerMovingDown == true) iRespawnY = 505;
		else iRespawnY = 805;
	}

	else iRespawnY = 805; //Deafult

	//Set the position back to the start
	sPlayer.setPosition(375, iRespawnY);

	//Reset the texture dependin on which direction the player will be travelling.
	if (!bPLayerMovingDown)sPlayer.setTexture(pTextureBack);
	else sPlayer.setTexture(pTextureFront);

	//Reset the fade in clock so that the player fades back in.
	playerfadeinclock.restart();

}

//int function that returns the number of lives after taking one away.
int Player::lostLife(bool bMute)
{
	//Only play death sounds if not muted.
	if (!bMute)
	{
		//play splash sound if player looses life in water region
		if (water()) sSplashSound.play();

		//play colisionsound if player is on traintracks or road
		else sCollideSound.play();
	}

	//Remove a life.
	 iPlayerLives -- ;

	 //Return the number of lives the player now has.
	 return iPlayerLives;
}

//int function that returns the number of lives after adding one.
int Player::gainedlife()
{
	iPlayerLives++;
	return iPlayerLives;
}

//int function that returns the current number of lives that the player has.
int Player::getlives()
{
	return iPlayerLives;
}

//boolean function that returns true in the player is within the water segment of the map.
bool Player::water()
{
	if (sPlayer.getPosition().y < 330 && sPlayer.getPosition().y >80 )
	{
		return true;
	}
	else return false;
}

//Void function used to set the transparency, the percentage opaque is passed into the function as a parameter.
void Player::settransparancy(float iPercent)
{
	//In the rgba scale alpha controls translucency and is measured between 0-255. The percentage parameter is times by 2.55 to give a true value
	int iAlphaAmmount = (2.55 * iPercent);

	//Set the color for the player, with all values to max , except for the alpha
	sf::Color cPlayerColor(255,255,255, iAlphaAmmount);

	//The players color is set
	sPlayer.setColor(cPlayerColor);
}