#pragma once

#include "Spawner.hpp"
#include "Playfield.hpp"

#include <math.h>
#include <optional>
#include <variant>

class Game {    
    private:

        std::string dataDir;

        // Window and Displays
        sf::RenderWindow* window;
        bool running;

        // Render objects
        GUI* gui;
        Playfield* playfield;
        Player* player;

        // Update Time 
        sf::Clock clock;
        sf::Time deltaTime;

        // Enemy Spawner
        Spawner* spawner;
        float enemyDamage;

        // Playfield Variables
        float playfieldCenterX;
        float playfieldCenterY;
        float playfieldPosX;
        float playfieldPosY;

        // Button Variables
        float buttonCooldown;
        float buttonCooldownMax;

        // Animation
        float spritePosX;
        float spritePosY;

        // 
        float spawnTimer;
        float spawnTimerMax;

        int iFrames;
        int iFramesMax;

        float impactFrames;

        float playerStartPosX;
        float playerStartPosY;

        // Game Over Variables
        int gameOverTimer;
        int defeatSpriteCounter;

        bool gameOver;
        bool switchToDFScreen;

        // Private Functions
        void initVariables();
        void initWindow();
        void initPlayfield();
        void initGUI();
        void initPlayer();


    public:

        virtual int Run();

        // Constructor
        Game(std::string dataDir, sf::RenderWindow *window);

        // Destructor
        ~Game();

        // Public Functions
        const bool canPressButton();
        const bool getSwitchToDFScreen();
        bool borderReachedOdd(Enemy& enemy) const;
        bool borderReachedEven(Enemy& enemy) const;
        void moveEnemy();
        void shakeScreen();
        void resetScreen();

        void gameOverScreen();
        void killScreen();
        void restartGame();


        // Update Functions
        void update();
        void updateInput();
        void updateCollisonPlayfield();
        void updateCollisionEnemy();
        void updateButtonCooldown();
        void updateDeltaTime();
        void upadteEnemies();

        void render();


};
