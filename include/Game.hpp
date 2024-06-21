#pragma once

#include "cScreen.hpp"

#include "Spawner.hpp"
#include "Playfield.hpp"

class Game : public cScreen {    
    private:

        std::string dataDir;

        // Window and Displays
        sf::RenderWindow* window;
        sf::Event evnt;
        bool running;

        // Render objects
        GUI* gui;
        Playfield* playfield;

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

        Player* player;

        // Constructor
        Game(std::string dataDir, sf::RenderWindow *window);

        // Destructor
        ~Game();

        // Public Functions
        const bool canPressButton();
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
