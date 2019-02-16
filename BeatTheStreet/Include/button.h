#pragma once
/* Charles Barker
P15181036
March 2017 */

//SFML Library for graphics.
#include <SFML/Graphics.hpp>


class button
{
public:

	//Default constructor
	button();

	//constructor
	button(std::string imgdir, sf::Vector2f size, sf::Vector2f posision);

	//void function used to draw the button sprite
	void drawbutton(sf::RenderWindow & window);

	//Boolean function that returns true when the mouse is released over th button
	bool isclicked(sf::Event &event);

	//void function that changes the texture of the button when the mouse button is depressed this gives the impression that the button is being pushed in.
	void changetexture(sf::String imgdir);

private:

	//private textures and sprites that are used in multiple functions within the class
	sf::Texture tButtonTexture;
	sf::Sprite	 sButtonSprite;
	
	//Darker and normal colors are used to darken the sprite when the button is depressed 


};

