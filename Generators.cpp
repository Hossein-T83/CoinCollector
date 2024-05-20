#include "Generators.h"
//definition of constructor
Generators::Generators(Vector2f res) {
    //So we get diffrent random values everytime we run the game
    srand(time(NULL));
    resolution = res;
	dotTexture.loadFromFile("graphics/dot.png");
	cherryTexture.loadFromFile("graphics/cherry.png");
    enemyTexture.loadFromFile("graphics/bee.png");
}

void Generators::dotGenerator() {
    //assigning values for dots and dotcheck with a for loop
    for (int i = 0; i < 40; i++) {
        dot[i].setTexture(dotTexture);
        //generating random numbers for position between 50 pixels and window resolution - 50
        dot[i].setPosition(50 + (std::rand() % (int(resolution.x) - 50 - 50 + 1)), 50 + (std::rand() % (int(resolution.y) - 50 - 50 + 1)));
        dotCheck[i] = true;
    }
}

void Generators::cherryGenerator() {
    //same thing as dots but with cherry
    for (int i = 0; i < 8; i++) {
        cherry[i].setTexture(cherryTexture);
        //generating random numbers for position between 50 pixels and window resolution - 50
        cherry[i].setPosition(50 + (std::rand() % (int(resolution.x) - 50 - 50 + 1)), 50 + (std::rand() % (int(resolution.y) - 50 - 50 + 1)));
        cherryCheck[i] = true;
    }
}

Sprite* Generators::getDot() {
    return dot;
}

Sprite* Generators::getCherry() {
    return cherry;
}

bool* Generators::getDotBool() {
    return dotCheck;
}

bool* Generators::getCherryBool() {
    return cherryCheck;
}

void Generators::enemyGenerator(int xEnemy[3],int yEnemy[3]) {
    //creating and setting position of enemies
    for (int i = 0; i < 3; i++) {
        enemy[i].setTexture(enemyTexture);
        enemy[i].setPosition(xEnemy[i], yEnemy[i]);
        enemy[i].setScale(2, 2);
    }
}

Sprite* Generators::getEnemy() {
    return enemy;
}