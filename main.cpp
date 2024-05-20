#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "Generators.h"
using namespace sf;

//function for checking if anyone has won or not
bool winCheck(Player player1,Player player2) {
    //returning value of this line that declares the winning situation based on players' point and hp
    return !((player1.getHp() != 0 && player2.getHp() != 0) && (player1.getScore() != 200 && player2.getScore() != 200));
}

int main()
{
    //creating game window based on resolution of screen and capping fps
    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window;
    window.create(VideoMode(resolution.x, resolution.y),
        "Coin Collector",
        Style::Fullscreen);
    window.setFramerateLimit(60);

    //a boolian for detecting start of the game
    bool gameStart = false;
    //boolian for detecting end of game
    bool gameRestart = false;

    //creating background sprite and scaling it to window resolution
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("graphics/background.png");
    Sprite bckground;
    bckground.setTexture(backgroundTexture);
    bckground.setScale(
        resolution.x / bckground.getLocalBounds().width,
        resolution.y / bckground.getLocalBounds().height);


    //creating an event for smooth key detection
    Event event;


    //creating player sprite from player class
    Player player1("graphics/thomas.png", 0, resolution.y/2 + 50, 5,false);
    //creating detection zone to detect collisions
    FloatRect detectionZonePlayer1 = player1.getPos();
    //samething again for player2
    Player player2("graphics/bob.png", resolution.x-player1.getPos().width, resolution.y / 2 +50, 5, true);
    FloatRect detectionZonePlayer2 = player2.getPos();


    //creating an object from generator class to help with creating sprites
    Generators generator(resolution);
    //generating dots
    generator.dotGenerator();
    //generating cherries
    generator.cherryGenerator();

    //point value of dots sprite to adress recieved from class
    Sprite* dot = generator.getDot();
    bool* dotCheck = generator.getDotBool();

    //point value of cherries sprite to adress recieved from class
    Sprite* cherry = generator.getCherry();
    bool* cherryCheck = generator.getCherryBool();
    

    //creating the text for showing health from text manager class
    TextManager healthCounter;
    healthCounter.setScale(0.8,0.8);
    healthCounter.setString(std::to_string(player1.getHp()) + "/" + "100");
    //creating the text for showing score from text manager class
    TextManager pointCounter;
    pointCounter.setString(std::to_string(int(player1.getScore()))+"/"+"200");
    pointCounter.setPosition(0, 70);

    //doing the same thing for second player
    TextManager healthCounter2;
    healthCounter2.setPosition(resolution.x - 100, 0);
    healthCounter2.setScale(0.8, 0.8);
    healthCounter2.setString(std::to_string(player2.getHp()) + "/" + "100");
    TextManager pointCounter2;
    pointCounter2.setPosition(resolution.x - 200, 70);
    pointCounter2.setString(std::to_string(int(player2.getScore())) + "/" + "200");

    //creating text for start menue
    TextManager startMenu;
    startMenu.setString("Press Enter to start game");
    startMenu.setScale(5, 5);
    startMenu.setCenter();

    //creating text for end menue
    TextManager endMenu;
    endMenu.setString("Press Enter to play again or press Esc to exit");
    endMenu.setScale(3, 3);
    endMenu.setCenter();
    endMenu.setPosition(endMenu.getText().getPosition().x, endMenu.getText().getPosition().y + 200);

    //creating an object from class of sound manager to manage sounds
    soundManager sounds;
    //a boolian to make the winning sound only play once
    bool playWinSound = true;


    //setting diffrent starting position for each enemy based on screen's resolution
    int xEnemy[3];
    xEnemy[0] = resolution.x - 120;
    xEnemy[1] = resolution.x /3  - 120;
    xEnemy[2] = (resolution.x * 2) / 3 - 120;
    int yEnemy[3];
    yEnemy[0] = 0;
    yEnemy[1] = resolution.y/3;
    yEnemy[2] = (resolution.y/3)*2;
    //generating enemies
    generator.enemyGenerator(xEnemy, yEnemy);
    //point value of enemies sprite to adress recieved from class
    Sprite* enemy = generator.getEnemy();

    //creating game's ending text (both win and lose) from text manager class
    TextManager gameOver;
    gameOver.setScale(5, 5);
    gameOver.setString("Player 1 won!");
    //setting the position to center based on screen's resolution and changing the origin of text
    gameOver.setCenter();


    //main loop of the game
    while (window.isOpen())

    {   
        //clearing the mai window and making it ready by drawing background first
        window.clear();
        window.draw(bckground);
        if (gameStart) {
            //quit the game with esc key anytime
            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
            //check for win before starting detection
            if (!winCheck(player1, player2)) {
                while (window.pollEvent(event))
                {
                    //closing game with closing event
                    if (event.type == Event::Closed)
                        window.close();
                }
                //key detection for movement of player
                if (Keyboard::isKeyPressed(Keyboard::D))player1.right();
                if (Keyboard::isKeyPressed(Keyboard::A))player1.left();
                if (Keyboard::isKeyPressed(Keyboard::S))player1.down();
                if (Keyboard::isKeyPressed(Keyboard::W))player1.up();
                if (Keyboard::isKeyPressed(Keyboard::Right)) player2.right();
                if (Keyboard::isKeyPressed(Keyboard::Left)) player2.left();
                if (Keyboard::isKeyPressed(Keyboard::Down)) player2.down();
                if (Keyboard::isKeyPressed(Keyboard::Up)) player2.up();

                //setting new detection zone of player after each time they move
                detectionZonePlayer1 = player1.getPos();
                detectionZonePlayer2 = player2.getPos();
            }

            
            if (!winCheck(player1, player2)) {
                //checking if player has collectefd any of cherries with a for loop
                for (int i = 0; i < 8; i++) {
                    //creating a zone for detecting collisions of cherries
                    FloatRect detectionZoneCherry = cherry[i].getGlobalBounds();
                    if ((detectionZoneCherry.intersects(detectionZonePlayer1) || detectionZoneCherry.intersects(detectionZonePlayer2)) && cherryCheck[i]) {
                        //making cherry disapear
                        cherryCheck[i] = false;
                        sounds.playCherry();
                        //grating player invisibility
                        if (detectionZoneCherry.intersects(detectionZonePlayer1)) {
                            player1.cherryCollision();
                        }
                        else {
                            player2.cherryCollision();
                        }
                    }
                    //if cherry is not collected draw it
                    if (cherryCheck[i]) {
                        window.draw(cherry[i]);
                    }
                }
                //doing the same thing as cherries but this time with coins
                for (int i = 0; i < 40; i++) {
                    //creating a zone for detecting collisions of dots
                    FloatRect detectionZoneDot = dot[i].getGlobalBounds();
                    if ((detectionZoneDot.intersects(detectionZonePlayer1) || detectionZoneDot.intersects(detectionZonePlayer2)) && dotCheck[i]) {
                        dotCheck[i] = false;
                        //playing sound effect and updating player score and score bar
                        sounds.playCollect();
                        if (detectionZoneDot.intersects(detectionZonePlayer1)) {
                            player1.dotCollision();
                            pointCounter.setString(std::to_string(int(player1.getScore())) + "/" + "200");
                        }
                        else {
                            player2.dotCollision();
                            pointCounter2.setString(std::to_string(int(player2.getScore())) + "/" + "200");
                        }
                    }
                    //if coin is not collected draw it
                    if (dotCheck[i]) {
                        window.draw(dot[i]);
                    }
                }
            }

            //checking if the game has ended or not
            if (!winCheck(player1, player2)) {
                //checking collision of player and enemies
                for (int i = 0; i < 3; i++) {
                    //creating a zone for detecting collisions of bees
                    FloatRect detectionZoneEnemy = enemy[i].getGlobalBounds();
                    if (detectionZoneEnemy.intersects(detectionZonePlayer1) || detectionZoneEnemy.intersects(detectionZonePlayer2))
                    {
                        //reducing health and updating the bar if player is not invisible then grant player invisibility and play sound
                        if (detectionZoneEnemy.intersects(detectionZonePlayer1) && !player1.getInvisibility()) {
                            sounds.playHit();
                            player1.enemyCollision();
                            healthCounter.setString(std::to_string(player1.getHp()) + "/" + "100");
                        }
                        if (detectionZoneEnemy.intersects(detectionZonePlayer2) && !player2.getInvisibility()) {
                            sounds.playHit();
                            player2.enemyCollision();
                            healthCounter2.setString(std::to_string(player2.getHp()) + "/" + "100");
                        }
                    }
                    //making player visible after 3 seconds
                    player1.updateInvisibility();
                    player2.updateInvisibility();
                    //reseting enemy position after reaching end of the screen
                    if (xEnemy[i] + enemy[i].getLocalBounds().width - 20 < 0)
                    {
                        xEnemy[i] = resolution.x - enemy[i].getLocalBounds().width;
                        //enemy comes back to screen from random locations
                        yEnemy[i] = 50 + (std::rand() % (int(resolution.y) - 50 - 50 + 1));
                        enemy[i].setPosition(xEnemy[i], yEnemy[i]);
                        detectionZoneEnemy = enemy[i].getGlobalBounds();
                    }
                    else {
                        //move enemy if not out of screen
                        xEnemy[i] -= 20;
                        enemy[i].setPosition(xEnemy[i], yEnemy[i]);
                        detectionZoneEnemy = enemy[i].getGlobalBounds();
                    }
                }
            }
        }
      
        //drawing everything that is left
        window.draw(player1.getSprite());
        window.draw(player2.getSprite());
        window.draw(enemy[0]);
        window.draw(enemy[1]);
        window.draw(enemy[2]);
        window.draw(player1.getHealthBar());
        window.draw(player1.getHealth());
        window.draw(player1.getScoreBar());
        window.draw(player1.getPoint());
        window.draw(player2.getHealthBar());
        window.draw(player2.getHealth());
        window.draw(player2.getScoreBar());
        window.draw(player2.getPoint());
        window.draw(healthCounter.getText());
        window.draw(pointCounter.getText());
        window.draw(healthCounter2.getText());
        window.draw(pointCounter2.getText());
        if (!gameStart) {
            //draw starting menue only when game hasnt started yet
            window.draw(startMenu.getText());
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                gameStart = true;
            }
        }
        if (gameRestart) {
            //drawing the end menue when game has ended
            window.draw(endMenu.getText());
            //key detection for 2 choices that player has
            if (Keyboard::isKeyPressed(Keyboard::Escape))window.close();
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                gameRestart = false;
                //resetting stats of players
                player1.reset();
                player2.reset();
                //generating new dots and cherries
                generator.dotGenerator();
                generator.cherryGenerator();
                Sprite* dot = generator.getDot();
                bool* dotCheck = generator.getDotBool();
                Sprite* cherry = generator.getCherry();
                bool* cherryCheck = generator.getCherryBool();
                //resetting health and point bars
                healthCounter.setString(std::to_string(player1.getHp()) + "/" + "100");
                healthCounter2.setString(std::to_string(player2.getHp()) + "/" + "100");
                pointCounter2.setString(std::to_string(int(player1.getScore())) + "/" + "200");
   
            }
        }
        //checking for end of game and setting the text baed on result
        if (player1.getHp() == 0 || player2.getScore() == 200) {
            gameRestart = true;
            //make sure to hear win sound once
            if (playWinSound) {
                sounds.playWin();
                playWinSound = false;
            }
            //changeing string of text to winning player
            gameOver.setString("Player 2 won!");
            window.draw(gameOver.getText());
        }
        if (player1.getScore() == 200 || player2.getHp() == 0) {
            gameRestart = true;
            if (playWinSound) {
                sounds.playWin();
                playWinSound = false;
            }
            gameOver.setString("Player 1 won!");
            window.draw(gameOver.getText());
        }
        //display everything that is drawed
        window.display();
    }

    return 0;
}