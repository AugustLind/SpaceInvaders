#pragma once
#include "AnimationWindow.h"
#include "objects.h"
#include <vector>
#include "widgets/TextInput.h"

class SpaceInvadersGame : public TDT4102::AnimationWindow {
    static constexpr int startX = 500;
    static constexpr int startY = 100;
    static constexpr int blockWidth = 50;
    static constexpr int numRows = 10;
    Player player;
    std::vector<Shots> shots;
    std::vector<std::vector<Enemies>> enemies;
    std::vector<Shots> shotsEnemies;
    int rowsEnemies = 0;
    int totalRows = 5;
    int enemieSize = 30;
    int score = 0;
    TDT4102::TextInput scoreTxt;
    std::string livesStr = "Liv: " + std::to_string(player.getLives());
    TDT4102::TextInput livesTxt;
    

    

public:
    SpaceInvadersGame();
    void drawBackground();
    void run();
    void drawPlayer();
    void movePlayer();
    void playerShot();
    void drawShot();
    void moveShot();
    void createEnemies();
    void drawEnemies();
    void moveEnemies();
    void checkEnemiesHit();
    void enemiesShot();
    void drawShotEnemies();
    void moveShotEnemies();
    void checkPlayerHit();
};