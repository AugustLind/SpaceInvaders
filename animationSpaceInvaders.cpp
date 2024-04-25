#include "animationSpaceInvaders.h"
#include "Color.h"
#include <iostream>
#include <random>

SpaceInvadersGame::SpaceInvadersGame() : TDT4102::AnimationWindow{startX,startY,blockWidth*numRows,blockWidth*numRows},
    player{blockWidth*numRows/2, blockWidth*numRows - blockWidth}, scoreTxt{{10,10},blockWidth*3,blockWidth/2,"Score: 0"}, livesTxt{{200,10},blockWidth*3,blockWidth/2,livesStr}
{
    add(scoreTxt);
    add(livesTxt);
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
    unsigned int framesPerMove = 200;
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
                enemiesShot();
            }
        drawShotEnemies();
        moveShot();
        moveShotEnemies();
        drawEnemies();
        movePlayer();
        checkEnemiesHit();
        checkPlayerHit();
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
    bool spaceKeyIsPressed = is_key_down(KeyboardKey::UP);

    if(spaceKeyIsPressed) {
        Shots shot{player.getPosition().x + blockWidth/2, player.getPosition().y};
        shots.push_back(shot);
    }
}

void SpaceInvadersGame::drawShot(){
    for (int i = 0; i < shots.size() ; i++){
        if (shots.at(i).getVisible()){
            draw_rectangle({shots.at(i).getPosition()},blockWidth/5,shots.at(i).getLen(),TDT4102::Color::lime);
        }
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
            Enemies enemie{blockWidth*i + enemieSize*2, enemieSize};
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
        if (shots.at(i).getVisible()){
            for (int k = 0; k < enemies.size(); k++){
                for (int j = 0; j < enemies.at(k).size(); j++){
                    int xPos = enemies.at(k).at(j).getPosition().x;
                    int yPos = enemies.at(k).at(j).getPosition().y;
                    if (shots.at(i).getPosition().x >= xPos && shots.at(i).getPosition().x <= xPos + enemieSize
                    && shots.at(i).getPosition().y >= yPos && shots.at(i).getPosition().y <= yPos + enemieSize){
                        Enemies enemie{0,0};
                        enemies.at(k).at(j) = enemie;
                        shots.at(i).setHidden();
                        score += 1;
                        std::string txt = "Score: " + std::to_string(score);
                        scoreTxt.setText(txt);
                    }
                }
            }   
        }
    }
}


void  SpaceInvadersGame::enemiesShot(){
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0,rowsEnemies);
    std::uniform_real_distribution<> col(0,numRows-1);
    std::uniform_real_distribution<> sho(0,(numRows-1)*rowsEnemies/6);
    int numberShots = sho(gen);
    for (int i = 0; i < numberShots; i++){
        int row = dis(gen);
        int colm = col(gen);
        if (enemies.at(row).at(colm).getPosition().y != 0){
             Shots shot{enemies.at(row).at(colm).getPosition().x + enemieSize/2, enemies.at(row).at(colm).getPosition().y + enemieSize};
             shotsEnemies.push_back(shot);
        }
    }
}

void SpaceInvadersGame::drawShotEnemies(){
    for (int i = 0; i < shotsEnemies.size() ; i++){
        if (shotsEnemies.at(i).getVisible()){
            draw_rectangle({shotsEnemies.at(i).getPosition()},blockWidth/5,shotsEnemies.at(i).getLen(),TDT4102::Color::lime);
        }
    }
}

void SpaceInvadersGame::moveShotEnemies(){
    for (int i = 0; i < shotsEnemies.size() ; i++){
        shotsEnemies.at(i).moveDown();
    }
}

void SpaceInvadersGame::checkPlayerHit(){
    for (int i = 0; i < shotsEnemies.size(); i++){
        if (shotsEnemies.at(i).getVisible()){
            int xPos = player.getPosition().x;
            int yPos = player.getPosition().y;
            if (shotsEnemies.at(i).getPosition().x >= xPos && shotsEnemies.at(i).getPosition().x <= xPos + blockWidth
            && shotsEnemies.at(i).getPosition().y >= yPos){
                player.loseLife(); 
                shotsEnemies.at(i).setHidden();  
                livesStr = "Liv: " + std::to_string(player.getLives());
                livesTxt.setText(livesStr);
            }
        }
    }   
}


