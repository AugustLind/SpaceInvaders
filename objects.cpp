#include "objects.h"

TDT4102::Point Player::getPosition(){
    return {posX,posY};
}

int Player::getLives(){
    return lives;
}

void Player::moveLeft(){
    posX -= 5;
}

void Player::moveRight(){
    posX += 5;
}

void Shots::moveUp(){
    posY -= 5;
}

void Shots::moveDown(){
    posY += 5;
}

TDT4102::Point Shots::getPosition(){
    return {posX,posY};
}

int Shots::getLen(){
    return lenShot;
}