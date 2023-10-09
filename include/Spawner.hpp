#pragma once

#include "Enemy.hpp"
#include "Playfield.hpp"
#include "vector"
#include <ctime>

class Spawner {

    private:

        // Private Variables
        int randomPosition;
        float spawnPosX;
        float spawnPosY;

        // Private Functions
        void initVariables();
        

    public:

        // Constructor
        Spawner();

        // Destructor
        ~Spawner();

        // Enemies
        std::vector<Enemy*> enemies;
        Enemy* enemy;

        // Public Functions
        void spawnEnemiesRandom(sf::RenderTarget* window, Playfield* playfield, std::string& dataDir);

};