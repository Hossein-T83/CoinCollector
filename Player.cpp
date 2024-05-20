#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

//constructor definition that contains texture adress,positions ,speed and side of player (mirror)
Player::Player(String filename, int positionX, int positionY,int playerSpeed,bool mirror)
{
    //declaring variables
    speed = playerSpeed;
    startX = positionX;
    startY = positionY;
    x = positionX;
    y = positionY;
    invisible = false;
    hp = 100;
    score = 0;

    //making changes to bars
    healthbar.setSize(Vector2f(100, 50));
    health.setSize(Vector2f(100, 50));
    healthbar.setFillColor(Color::White);
    health.setFillColor(Color::Red);
    scorebar.setSize(Vector2f(200, 50));
    point.setSize(Vector2f(score, 50));
    scorebar.setFillColor(Color::White);
    point.setFillColor(Color::Yellow);

    //geting window's resolution
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    //move bars to righ side of screen for player 2
    if (mirror) {
        healthbar.setPosition(resolution.x - healthbar.getLocalBounds().width, 0);
        health.setPosition(resolution.x - health.getLocalBounds().width, 0);
        scorebar.setPosition(resolution.x - scorebar.getLocalBounds().width, 70);
        point.setPosition(resolution.x - scorebar.getLocalBounds().width, 70);
    }
    //setting bar positions
    else {
        healthbar.setPosition(0, 0);
        health.setPosition(0, 0);
        scorebar.setPosition(0, 70);
        point.setPosition(0, 70);
    }
    //creating player's sprite
    Texture playerTexture;
    playerTexture.loadFromFile(filename);
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(x, y);
    playerSprite.setColor(Color::Green);
}

//getSptite method definition
Sprite Player::getSprite() {
    return playerSprite;
}

//getPos method definition
FloatRect Player::getPos() {
    return playerSprite.getGlobalBounds();
}
//updatePosition method definition
void Player::updatePosition() {
    playerSprite.setPosition(x, y);
}
//movement methods definition
void Player::left() {
    //making sure players dont get out of screen then move it based on their speed(same thing with next ones)
    if (getLoc().x >= 10) {
        x -= speed;
        updatePosition();
    }
}

void Player::right() {
    if (resolution.x > getPos().width + getLoc().x + 10) {
        x += speed;
        updatePosition();
    }
}

void Player::up() {
    if (getLoc().y >= 10) {
        y -= speed;
        updatePosition();
    }
}

void Player::down() {
    if (resolution.y > getPos().height + getLoc().y + 10) {
        y += speed;
        updatePosition();
    }
}

//getLoc method definition
Vector2f Player::getLoc() {
    return Vector2f(x, y);
}
//changeColor method definition
void Player::changeColor() {
    //changing color of player based on their current color
    if (playerSprite.getColor() == Color::Green) {
        playerSprite.setColor(Color::Blue);
    }
    else {
        playerSprite.setColor(Color::Green);
    }
}
//cherryCollision method definition
void Player::cherryCollision() {
    speed += 2;
    //restarting clock for invisibility
    clock.restart();
    //granting invisible
    if (!invisible) {
        changeColor();
        invisible = true;
        clock.restart();
    }
}
//enemyCollision method definition
void Player::enemyCollision() {
    //check if player is invisible
    if (!invisible)
    {
        //restarting clock to start invisibility
        clock.restart();
        //change color and reduce hp
        changeColor();
        hp -= 20;
        health.setSize(Vector2f(hp, 50));
        invisible = true;
    }
}
//updateInvisibility method definition
void Player::updateInvisibility() {
    //cehck if player is invisivbile when does it end
    if (invisible) {
        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() > 3) {
            if (speed > 5) speed = 5;
            invisible = false;
            changeColor();
        }

    }
}
//getInvisibility method definition
bool Player::getInvisibility() {
    return invisible;
}
//dotCollision method definition
void Player::dotCollision() {
    //adding to score 
    score += 10;
    point.setSize(Vector2f(score, 50));
}
//getting bars method
int Player::getHp() {
    return hp;
}

float Player::getScore() {
    return score;
}

RectangleShape Player::getHealthBar() {
    return healthbar;
}

RectangleShape Player::getHealth() {
    return health;
}

RectangleShape Player::getScoreBar() {
    return scorebar;
}

RectangleShape Player::getPoint() {
    return point;
}
//method for reseting player stats and position
void Player::reset() {
    hp = 100;
    score = 0;
    point.setSize(Vector2f(score, 50));
    health.setSize(Vector2f(100, 50));
    playerSprite.setColor(Color::Green);
    invisible = false;
    x = startX;
    y = startY;
    playerSprite.setPosition(x,y);
}