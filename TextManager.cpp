#include "TextManager.h"
//defining constructor
TextManager::TextManager()
{
	//setting font and colors that all texts have in common
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	text.setFont(font);
	text.setFillColor(Color::Black);
}
//makin text centered
void TextManager::setCenter()
{
	//gettinig window's size
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	//setting the position to center based on screen's resolution and changing the origin of text
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(resolution.x / 2, resolution.y / 2);
}
//defining methods to change text
void TextManager::setScale(float x, float y)
{
	text.setScale(x, y);
}

void TextManager::setPosition(int x, int y)
{
	text.setPosition(x, y);
}

void TextManager::setString(String string)
{
	text.setString(string);
}
//text return
Text TextManager::getText()
{
	return text;
}