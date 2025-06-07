#ifndef _SPAWNER_
#define _SPAWNER_

#include "Enemy.hpp"
#include "Playfield.hpp"

// Random, double, path
enum EVENT {SINGLE, PAIR, size};

class Spawner {
    private:

        std::string dataDir;

        // Window
        sf::RenderTarget* window;
        
        // Playfield
        Playfield* playfield;

        // Enemies
        std::vector<Enemy*> enemies;
        Enemy* enemy;
        int randomPosition;
        std::vector<float> spawnPointsX;
        std::vector<float> spawnPointsY;
        float spawnPosX;
        float spawnPosY;

        // Timer
        int eventTimer;
        int eventTimerMax;
        int randomEvent;

        // Private Functions
        void initVariables();
        void initSpawnPositions();

    public:

        // Constructor
        Spawner(std::string& dataDir, sf::RenderTarget* window, Playfield* playfield);

        // Getter 
        float getEnemySize();
        std::vector<Enemy*>& getEnemyVector();
        
        // Public Functions
        void deleteEnemies();
        void render();

        // Spawner Functions
        void spawn();
        void spawnEnemies(int& event);
        void spawnSingleEnemy();
        void spawnEnemyPair();
        
};

#endif