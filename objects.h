#pragma once
#include "AnimationWindow.h"


class Player {
    int posX;
    int posY;
    int lives = 3;

public: 
    Player(int pos1, int pos2) : posX{pos1}, posY{pos2} {};
    TDT4102::Point getPosition();
    int getLives();
    void moveLeft();
    void moveRight();
    void loseLife();
};

class Shots{
    int lenShot = 30;
    int posX;
    int posY;
    bool visible = true;

public:
    Shots(int pos1, int pos2) : posX{pos1}, posY{pos2 - lenShot} {};
    void moveUp();
    void moveDown();
    TDT4102::Point getPosition();
    int getLen();
    void setHidden();
    bool getVisible();
};


class Enemies{
    int posX;
    int posY;

public:

    Enemies(int pos1, int pos2) : posX{pos1}, posY{pos2} {};
    TDT4102::Point getPosition();
    void moveDown();
};