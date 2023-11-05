#pragma once

#include "Spawner.hpp"
#include "Playfield.hpp"

class Game {    
    private:
        std::string dataDir;

        // Window and Display
        sf::RenderWindow* window;
        sf::Event evnt;
        sf::VideoMode vMode;

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

        // Private Functions
        void initVariables();
        void initWindow();
        void initPlayfield();
        void initGUI();
        void initPlayer();

    public:

        // Constructor
        Game(std::string dataDir);

        // Destructor
        ~Game();

        // Public Functions
        const bool running() const;
        const bool canPressButton();
        bool borderReachedOdd(Enemy& enemy) const;
        bool borderReachedEven(Enemy& enemy) const;
        void pollEvents();
        void moveEnemy();
        void shakeScreen();
        void resetScreen();

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
