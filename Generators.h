#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Generators
{
public:
	//default constructor
	Generators(Vector2f res);
	//method for creating dots
	void dotGenerator();
	//since you cant return an array a method for returnig pointer of the dot's array
	Sprite* getDot();
	//same things going on here as dots
	void cherryGenerator();
	Sprite* getCherry();
	//methodfor returning check table of dots and cherries
	bool* getDotBool();
	bool* getCherryBool();
	//method for creating enemies and returning their sprite pointer
	void enemyGenerator(int xEnemy[3],int yEnemy[3]);
	Sprite* getEnemy();

private:
	//all the private variables
	Texture dotTexture;
	Texture cherryTexture;
	Texture enemyTexture;
	Sprite dot[40];
	Sprite cherry[40];
	Sprite enemy[3];
	bool dotCheck[40];
	bool cherryCheck[40];
	Vector2f resolution;

};

