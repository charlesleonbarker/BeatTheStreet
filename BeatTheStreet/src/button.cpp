/* Charles Barker
P15181036
March 2017 */

//SFML library for graphic and audio
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Class header file
#include "button.h"

button::button()
{
	//default
}

//constructor
button::button(std::string imgdir, sf::Vector2f size, sf::Vector2f posision)
{
	//load texture using directory in parameters
	if (!tButtonTexture.loadFromFile(imgdir)) EXIT_FAILURE;

	//set texture
	sButtonSprite.setTexture(tButtonTexture);

	//set scale using size from parameters
	sButtonSprite.setScale(size.x / tButtonTexture.getSize().x, size.y / tButtonTexture.getSize().y);

	//set possession based on parameters, origin default to 0,0
	sButtonSprite.setPosition(posision);
	
}

//void function used to draw the button sprite
void button::drawbutton(sf::RenderWindow & window )
{

	window.draw(sButtonSprite);
}

//Boolean function that returns true when the mouse is released over th button
bool button::isclicked(sf::Event &event)
{
	//floatrect of button global bounds initialized, used when determining if it has been clicked.
	sf::FloatRect frButtonBounds = sButtonSprite.getGlobalBounds();

	//vector that holds x and y position of the click location
	sf::Vector2f v2fClickLocation(event.mouseButton.x, event.mouseButton.y);
	
	//Darker and normal colors are used to darken the sprite when the button is depressed.
	sf::Color darker(100, 100, 100, 255);
	sf::Color normal(255, 255, 255, 255);

	if (event.type == sf::Event::MouseButtonPressed)//If a mouse button is pressed
	{
		if (event.mouseButton.button == sf::Mouse::Left)//If the mouse button is left
		{
			if (frButtonBounds.contains(v2fClickLocation))//If the click location is within the bounds of the button
			{
				sButtonSprite.setColor(darker);//set the button color to darker
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)//If the mouse button is released 
	{
		if (event.mouseButton.button == sf::Mouse::Left)//If the mouse button is left
		{
			sButtonSprite.setColor(normal);//Set the color back to normal

			if (frButtonBounds.contains(v2fClickLocation)) //If the click location is within the bounds of the button
			{
				return true;//Return true
			}
			else return false;
		}
		else return false;
	}
	return false;
}

//void function that changes the texture of the button.
void button::changetexture(sf::String imgdir)
{
	//load texture dorm imgdir
	if (!tButtonTexture.loadFromFile(imgdir))EXIT_FAILURE;
	
	//set texture
	sButtonSprite.setTexture(tButtonTexture);
}
