#pragma once
#include "AnimationWindow.h"
#include "objects.h"
#include <vector>

class SpaceInvadersGame : public TDT4102::AnimationWindow {
    static constexpr int startX = 500;
    static constexpr int startY = 100;
    static constexpr int blockWidth = 50;
    static constexpr int numRows = 10;
    Player player;
    std::vector<Shots> shots;

    

public:
    SpaceInvadersGame();
    void drawBackground();
    void run();
    void drawPlayer();
    void movePlayer();
    void playerShot();
    void drawShot();
    void moveShot();

};