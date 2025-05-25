#ifndef _GAME_
#define _GAME_

#include "SFML/Graphics.hpp"
#include "Playfield.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include "Spawner.hpp"


enum DEFEATFLAG {NORMAL, BROKEN, VANISHED};

class Game {    
    private:

        std::string dataDir;

        // Window and Displays
        sf::RenderWindow* window;
        int windowSizeX;
        int windowSizeY;

        // Render objects
        GUI* gui;        

        // Update Time 
        sf::Clock clock;
        sf::Time deltaTime;

        // Spawner Variables
        Spawner* spawner;
        float spawnTimer;
        float spawnTimerMax;

        // Playfield Variables
        Playfield* playfield;
        float playfieldCenterX;
        float playfieldCenterY;
        float playfieldPosX;
        float playfieldPosY;
        float borderThickness;
        float leftPlayfieldBorder;
        float rightPlayfieldBorder;

        // Player Variables
        Player* player;
        float playerStartPosX;
        float playerStartPosY;
        float playerPositionX;
        float playerPositionY;
        float impactFrames;
        int iFrames;
        int iFramesMax;

        // Enemy Variables
        float enemyDamage;
        float oddEnemyBorder;
        float evenEnemyBorder;
        std::vector<Enemy*> enemies;

        // Button Variables
        float buttonCooldown;
        float buttonCooldownMax;

        // Animation Variables
        float spritePosX;
        float spritePosY;

        // Game Over Variables
        bool gameOver;
        int gameOverTimer;
        DEFEATFLAG defeatFlag;

        // Initialization
        void initVariables();
        void initPlayfield();
        void initGUI();
        void initPlayer();
        void initConst();

        // Update and draw Functions
        void updateDeltaTime();
        void updateInput();
        void updateCollisionPlayfield();
        void updateCollisionEnemy();
        void updateButtonCooldown();
        void updateEnemies();
        
        // Helper Methods
        const bool canPressButton();
        void shakeScreen();
        void resetScreen();
        void moveEnemy();
        bool borderReachedOdd(Enemy& enemy) const;
        bool borderReachedEven(Enemy& enemy) const;
        void deathAction();
        void deathAnimation();

    public:

        // Constructor
        Game(std::string dataDir, sf::RenderWindow *window);
        
        // Destructor
        ~Game();

        // Public Variables
        bool switchToDFScreen;

        //Public Functions
        void update();
        void render();
};

#endif