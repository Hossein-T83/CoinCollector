#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//creating class to manage all texts
class TextManager
{
public:
	//constructor
	TextManager();
	//method to move text to center
	void setCenter();
	//funtions for making basic change to text
	void setScale(float x, float y);
	void setPosition(int x , int y);
	void setString(String string);
	//method for returning text
	Text getText();


private:
	//font and text private variables
	Font font;
	Text text;
};
