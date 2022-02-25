#include<iostream>
#include <cmath>
#include "SFML/Graphics.hpp"
using namespace std;

enum DIRECTIONS { LEFT, RIGHT, UP, DOWN };

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(1920, 800), "breakout"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("./Sprites/brick.png");
    sf::Sprite wall;
    wall.setTexture(brick);

    int map[10][24] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,
        1,0,1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,
        1,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,
        1,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,1,1,
        1,1,0,1,0,1,0,0,0,1,0,1,0,0,1,0,1,0,1,1,1,0,1,1,
        1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,
        1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,
        1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };

    //player setup
    int xpos = 85;
    int ypos = 85;
    int vx = 0;
    int vy = 0;
    int radius = 35;
    sf::CircleShape player(radius);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };

    bool collide = false;

    //coin
    int coinRad = 5;
    sf::CircleShape coin(coinRad);
    coin.setFillColor(sf::Color(250, 250, 0));

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed) {
                screen.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

        }//end event loop---------------------------------------------------------------

        //update player
        if (keys[LEFT] == true)
        {
            vx = -5;
            vy = 0;
        }
        else if (keys[RIGHT] == true)
        {
            vx = 5;
            vy = 0;
        }
        else if (keys[UP] == true)
        {
            vy = -5;
            vx = 0;
        }
        else if (keys[DOWN] == true)
        {
            vy = 5;
            vx = 0;
        }
        else
        {
            
        }   
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

        if (vx > 0 && map[(ypos + 5) / 80][(xpos + (radius * 2) + 5) / 80] == 1 || map[(ypos + (radius * 2) - 5) / 80][(xpos + (radius * 2) - 5) / 80] == 1)
        {
            vx = 0;
        }
        if (vx > 0 && map[(ypos - 5) / 80][(xpos - (radius / 2) - 10) / 80] == 1 || map[(ypos - 5) / 80][(xpos - (radius / 2) + 10) / 80] == 1)
        {
            vx = 0;
        }
        if (vy > 0 && map[(ypos + (radius * 2) + 5) / 80][(xpos + 5) / 80] == 1 || map[(ypos + (radius * 2) - 5) / 80][(xpos + (radius * 2) - 5) / 80] == 1)
        {
            vy = 0;
        }
        if (vy < 0 && map[(ypos + (-radius / 2) + 10) / 80][(xpos) / 80] == 1)
        {
            vy = 0;
        }

        if (map[(ypos + 5) / 80][(xpos + 5) / 80] == 0)
        {
            map[(ypos + 5) / 80][(xpos + 5) / 80] = -1;
        }

        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear
        for (int rows = 0; rows < 10; rows++) {
            for (int cols = 0; cols < 24; cols++) {
                if (map[rows][cols] == 0)
                {
                    coin.setPosition(((cols * 80) + 40), ((rows * 80) + 40));
                    
                    screen.draw(coin);
                }
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 80, rows * 80);
                    screen.draw(wall);
                }
            }
        }
        screen.draw(player);
        screen.display(); //flips memory drawings onto screen

        if (collide == true)
        {
            return NULL;
        }

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
}
