#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
//class for managing players easier
class Player
{
private:
	Sprite playerSprite;
	int startX;
	int startY;
	int x;
	int y;
	int speed;
	bool invisible;
	Clock clock;
	Time elapsed;
	int hp;
	float score;
	RectangleShape healthbar;
	RectangleShape health;
	RectangleShape scorebar;
	RectangleShape point;
	Vector2f resolution;
	//every private variable of player class


public:
	//main constructor
	Player(String filename,int positionX,int PositionY,int playerSpeed,bool mirror);
	//method to create the get sprite value
	Sprite getSprite();
	//method to get globalbounds
	FloatRect getPos();
	//method to update position of sprite
	void updatePosition();
	//methods for movement of sprite
	void left();
	void right();
	void up();
	void down();
	//method to get the position of sprite
	Vector2f getLoc();
	//methods to  change color of sprite
	void changeColor();
	//methods for collision of player
	void cherryCollision();
	void enemyCollision();
	void dotCollision();
	//methods for managing invisibility of player
	void updateInvisibility();
	bool getInvisibility();
	//method for returning hp and score of player
	int getHp();
	float getScore();
	//methods for getting sprite of score and health bars
	RectangleShape getHealthBar();
	RectangleShape getHealth();
	RectangleShape getScoreBar();
	RectangleShape getPoint();
	//method for reseting everything
	void reset();



};