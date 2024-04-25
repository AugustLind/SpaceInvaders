#include "animationSpaceInvaders.h"
#include "Color.h"
#include <iostream>

SpaceInvadersGame::SpaceInvadersGame() : TDT4102::AnimationWindow{startX,startY,blockWidth*numRows,blockWidth*numRows},
    player{blockWidth*numRows/2, blockWidth*numRows - blockWidth}
{
    enemies.reserve(totalRows);
    for (int i = 0; i < totalRows; i++){
        std::vector<Enemies> column;
        column.reserve(numRows-1);
        for (int j = 0; j < numRows-1; j++){
            Enemies enemie{0,0};
            column.push_back(enemie);

        }
        enemies.push_back(column);
    }
}



void SpaceInvadersGame::drawBackground(){
    draw_rectangle({0,0},blockWidth*numRows,blockWidth*numRows,TDT4102::Color::black);
}

void SpaceInvadersGame::run(){
    unsigned int framesSinceLastMove = 0;
    unsigned int framesPerMove = 100;
    unsigned int framesSinceLastShot = 0;
    unsigned int framesPerShot = 20;
    while(!should_close()) {
        drawBackground(); 
        framesSinceLastMove++;
        framesSinceLastShot++;
        if(framesSinceLastMove >= framesPerMove) {
                moveEnemies();
                createEnemies();
                framesSinceLastMove = 0;
            }
        if(framesSinceLastShot >= framesPerShot) {
                playerShot();
                framesSinceLastShot = 0;
            }
        moveShot();
        drawEnemies();
        movePlayer();
        checkEnemiesHit();
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

void SpaceInvadersGame::createEnemies(){
    if (rowsEnemies < totalRows){
        for (int i = 0; i < enemies.at(rowsEnemies).size(); i++){
            Enemies enemie{blockWidth*i + enemieSize, enemieSize};
            enemies.at(rowsEnemies).at(i) = enemie;
        }
        rowsEnemies += 1;
    }
}

void SpaceInvadersGame::drawEnemies(){
    for (int i = 0; i < enemies.size(); i++){
        for (int j = 0; j < enemies.at(i).size(); j++){
            if (enemies.at(i).at(j).getPosition().y != 0){
                draw_rectangle({enemies.at(i).at(j).getPosition()},enemieSize,enemieSize,TDT4102::Color::lime);
            }
        }
    }
}

void SpaceInvadersGame::moveEnemies(){
    for (int i = 0; i < enemies.size(); i++){
        for (int j = 0; j < enemies.at(i).size(); j++){
            if (enemies.at(i).at(j).getPosition().y != 0){
                enemies.at(i).at(j).moveDown();
            }
        }
    }
}

void SpaceInvadersGame::checkEnemiesHit(){
    for (int i = 0; i < shots.size(); i++){
        shots.at(i).getPosition();
        for (int k = 0; k < enemies.size(); k++){
            for (int j = 0; j < enemies.at(k).size(); j++){
                int xPos = enemies.at(k).at(j).getPosition().x;
                int yPos = enemies.at(k).at(j).getPosition().y;
                if (shots.at(i).getPosition().x >= xPos && shots.at(i).getPosition().x <= xPos + enemieSize
                && shots.at(i).getPosition().y >= yPos && shots.at(i).getPosition().y <= yPos + enemieSize){
                    Enemies enemie{0,0};
                    enemies.at(k).at(j) = enemie;
                }
        }
    }
    }
}