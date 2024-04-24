#include "animationSpaceInvaders.h"
#include "Color.h"

SpaceInvadersGame::SpaceInvadersGame() : TDT4102::AnimationWindow{startX,startY,blockWidth*numRows,blockWidth*numRows},
    player{blockWidth*numRows/2, blockWidth*numRows - blockWidth}
    {}


void SpaceInvadersGame::drawBackground(){
    draw_rectangle({0,0},blockWidth*numRows,blockWidth*numRows,TDT4102::Color::black);
}

void SpaceInvadersGame::run(){
    unsigned int framesSinceLastMove = 0;
    unsigned int framesPerMove = 100;
    while(!should_close()) {
        drawBackground(); 
        framesSinceLastMove++;
        if(framesSinceLastMove >= framesPerMove) {
                framesSinceLastMove = 0;
            }
        playerShot();
        moveShot();
        movePlayer();
        drawPlayer();
        drawShot();
        next_frame();
    }
}


void SpaceInvadersGame::drawPlayer(){
    draw_rectangle({player.getPosition()},blockWidth,blockWidth/2,TDT4102::Color::lime);
}

void SpaceInvadersGame::movePlayer(){
    bool aKeyIsPressed = is_key_down(KeyboardKey::A);
    bool dKeyIsPressed = is_key_down(KeyboardKey::D);

    if(aKeyIsPressed && player.getPosition().x > 0) {
        player.moveLeft();
    }

    if(dKeyIsPressed && player.getPosition().x + blockWidth <= blockWidth*numRows) {
        player.moveRight();
    }

}

void SpaceInvadersGame::playerShot(){
    bool spaceKeyIsPressed = is_key_down(KeyboardKey::SPACE);

    if(spaceKeyIsPressed) {
        Shots shot{player.getPosition().x + blockWidth/2, player.getPosition().y};
        shots.push_back(shot);
    }
}

void SpaceInvadersGame::drawShot(){
    for (int i = 0; i < shots.size() ; i++){
        draw_rectangle({shots.at(i).getPosition()},blockWidth/5,shots.at(i).getLen(),TDT4102::Color::lime);
    }
}

void SpaceInvadersGame::moveShot(){
    for (int i = 0; i < shots.size() ; i++){
        shots.at(i).moveUp();
    }
}