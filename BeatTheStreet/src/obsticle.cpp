#pragma once
/* Charles Barker
P15181036
March 2017 */

//SFML Library for graphics.
#include <SFML/Graphics.hpp>

//Class header file
#include "obsticle.h"

//Default constructor
obsticle::obsticle()
{
	//Default
}

//Constructor
obsticle::obsticle(int vehicletype, float strip, bool bDirection, float fHorizontalStartingPosision)
{
	//lane 
	fLane = strip;

	//v2f used to hold the size of the sprite, set depending on vehicle type
	sf::Vector2f oSize;


	//Set bool initially to false
	bIsTrain = false;

	//Depending on the vehicletype and direction, different textures are set, along with different values for the size
	if (vehicletype == 1) {
		if (bDirection)objectTextureDirectory = ".\\Assets\\graphics\\car1right.png";
		else objectTextureDirectory = ".\\Assets\\graphics\\car1left.png";
		oSize.x = 100.f;
		oSize.y = 75.f;
		}	
		else if (vehicletype == 2) { 
		if (bDirection)objectTextureDirectory = ".\\Assets\\graphics\\car2right.png";
		else objectTextureDirectory = ".\\Assets\\graphics\\car2left.png";
		oSize.x = 100.f;
		oSize.y = 75.f;
	}
	else if (vehicletype == 3) {
		if (bDirection)objectTextureDirectory = ".\\Assets\\graphics\\car3right.png";
		else objectTextureDirectory = ".\\Assets\\graphics\\car3left.png";		
		oSize.x = 100.f;
		oSize.y = 75.f;
	}
	else if (vehicletype == 4) {
		if (bDirection)objectTextureDirectory = ".\\Assets\\graphics\\train.png";
		else objectTextureDirectory = ".\\Assets\\graphics\\train2.png";		
		oSize.x = 1700.f;
		oSize.y = 75.f;
		bIsTrain = true;
	}
	else if (vehicletype == 5) {
		if (bDirection)objectTextureDirectory = ".\\Assets\\graphics\\Log1right.png";
		else objectTextureDirectory = ".\\Assets\\graphics\\Log1left.png";		
		oSize.x = 150.f;
		oSize.y = 75.f;
	}
	else if (vehicletype == 6) {
		if (bDirection)objectTextureDirectory = ".\\Assets\\graphics\\Log2right.png";
		else objectTextureDirectory = ".\\Assets\\graphics\\Log2left.png";		
		oSize.x = 150.f;
		oSize.y = 75.f;
	}
	else if (vehicletype == 7) {
		if (bDirection)objectTextureDirectory = ".\\Assets\\graphics\\Log3right.png";
		else objectTextureDirectory = ".\\Assets\\graphics\\Log3left.png";		
		oSize.x = 150.f;
		oSize.y = 75.f;
	}



	//vertical start posision set depending on lane
	float fOffset = 12.5;
	if (fLane == 1) vStart = 55.f - fOffset;
	else if (fLane == 2) vStart = 105.f - fOffset;
	else if (fLane == 3) vStart = 155.f - fOffset;
	else if (fLane == 4) vStart = 205.f - fOffset;
	else if (fLane == 5) vStart = 255.f - fOffset;
	else if (fLane == 6) vStart = 305.f - fOffset;
	else if (fLane == 7) vStart = 355.f - fOffset;
	else if (fLane == 8) vStart = 405.f - fOffset;
	else if (fLane == 9) vStart = 455.f - fOffset;
	else if (fLane == 10) vStart = 505.f - fOffset;
	else if (fLane == 11) vStart = 555.f - fOffset;
	else if (fLane == 12) vStart = 605.f - fOffset;
	else if (fLane == 13) vStart = 655.f - fOffset;
	else if (fLane == 14) vStart = 705.f - fOffset;
	else if (fLane == 15) vStart = 755.f - fOffset;
	else if (fLane == 16) vStart = 805.f - fOffset;
	

	//set position
	oSprite.setPosition(fHorizontalStartingPosision, vStart);

	//parameter direction dictates direction
	if (bDirection == 0) bObsticalDirection = 0;
	if (bDirection == 1) bObsticalDirection = 1;

	//load texture from directory
	if (!oTexture.loadFromFile(objectTextureDirectory)) EXIT_FAILURE;
	//set texture
	oSprite.setTexture(oTexture);

	//set scale using size from vehicletype
	oSprite.setScale(oSize.x / oTexture.getSize().x, oSize.y / oTexture.getSize().y);

	//origin set to middle of sprite
	oSprite.setOrigin(oSize.x / oSprite.getScale().x / 2.0f , oSize.y / oSprite.getScale().y / 2.0f);
}

//Void function that moves the sprite along the lane
void obsticle::moveObsticle(float extraspeed)
{


	//float variables to hold the speeds of all the lanes.
	float  laneSpeed2, laneSpeed3, laneSpeed4, laneSpeed5, laneSpeed6, laneSpeed8, laneSpeed9, laneSpeed11, laneSpeed12, laneSpeed13, laneSpeed14, laneSpeed15;

	
		/////////////////////
		/////////////////////
		laneSpeed2 = 5.;
		laneSpeed3 = 4;
		laneSpeed4 = 3;
		laneSpeed5 = 2;
		laneSpeed6 = 1;
		/////////////////////
		/////////////////////
		laneSpeed8 = 10;
		laneSpeed9 = 25;
		/////////////////////
		/////////////////////
		laneSpeed11 = 5;
		laneSpeed12 = 6;
		laneSpeed13 = 4;
		laneSpeed14 = 5;
		laneSpeed15 = 3;
		/////////////////////
		/////////////////////

		//set the strip speed depending on lane 
	 if (fLane == 2) { fSpeedOfStrip = laneSpeed2; }
	else if (fLane == 3) { fSpeedOfStrip = laneSpeed3; }
	else if (fLane == 4) { fSpeedOfStrip = laneSpeed4; }
	else if (fLane == 5) { fSpeedOfStrip = laneSpeed5; }
	else if (fLane == 6) { fSpeedOfStrip = laneSpeed6; }
	else if (fLane == 8) { fSpeedOfStrip = laneSpeed8; }
	else if (fLane == 9) { fSpeedOfStrip = laneSpeed9; }
	else if (fLane == 11) { fSpeedOfStrip = laneSpeed11; }
	else if (fLane == 12) { fSpeedOfStrip = laneSpeed12; }
	else if (fLane == 13) { fSpeedOfStrip = laneSpeed13; }
	else if (fLane == 14) { fSpeedOfStrip = laneSpeed14; }
	else if (fLane == 15) { fSpeedOfStrip = laneSpeed15; }

	//add extra speed that is given as a parameter from the main. extra speed is added when presents are collected
	fSpeedOfStrip = fSpeedOfStrip + extraspeed;
		 
	//fHorizontalPosision is set from the sprites origin x position.
	float fHorizontalPossision = oSprite.getPosition().x;

	//Move back distance is the distance off the screen that the sprite is reset to.
	float fMovebackDistance;

	if (bIsTrain) fMovebackDistance = 1500.f; //if the object is a train moveback is set to 1500px due to the long size of the train
	else fMovebackDistance = 150.f; //else set to 150px
	
	//if the sprite goes off the screen the position is reset using the moveback.
	if (!bObsticalDirection && fHorizontalPossision < -fMovebackDistance)
	{
		float sprtieypos = oSprite.getPosition().y;
		oSprite.setPosition(800 + fMovebackDistance, sprtieypos);
	}
	//if the sprite goes off the screen the position is reset using the moveback.

	if (bObsticalDirection && fHorizontalPossision > 800+fMovebackDistance)
	{
		float sprtieypos = oSprite.getPosition().y;
		oSprite.setPosition(-fMovebackDistance, sprtieypos);
	}

	//move the sprite in specific direction
	if (!bObsticalDirection) oSprite.move(-fSpeedOfStrip, 0);
	else if (bObsticalDirection)oSprite.move(fSpeedOfStrip, 0);
}

//Boolean function that returns true if the sprite contacts the floatrect parameter.
bool obsticle::playerContact(sf::FloatRect frogglobalbounds, bool boat)
{

	//Initialize floatrect for intersection and assign modified values from the obstacle sprite.
	sf::FloatRect frContactBox;
	frContactBox.left = oSprite.getGlobalBounds().left;
	frContactBox.top = oSprite.getGlobalBounds().top + 25; //+25 so that only the bottom of the sprite intersects
	frContactBox.height = oSprite.getGlobalBounds().height - 50;//-50 so that only the bottom of the sprite intersects
	frContactBox.width = oSprite.getGlobalBounds().width;

	//if the obstacle is not a boat, return true when collision occurs.
	if (!boat && frContactBox.intersects(frogglobalbounds))
	{
		return true;
	}

	//if it is a boat collision only occurs when the middle of the sprite intersects. This is so 50% of the sprite can hang off the edge of the boat
	else if (boat)
	{
		//floatrect for player center
		sf::FloatRect newfrogcenter = frogglobalbounds;
		newfrogcenter.left = frogglobalbounds.left + 24;
		newfrogcenter.width = 2;
		
		if (frContactBox.intersects(newfrogcenter))//if the new floatrect intersects the boat, the player must be on board.
		{
			return true;
		}
		else return false;
	}
	else return false;
}

//Void function that draws the sprite to the screen.
void obsticle::drawObsticle(sf::RenderWindow &window)
{
	//draw obstacle
	window.draw(oSprite);
}