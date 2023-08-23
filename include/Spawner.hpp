#pragma once

#include "Enemy.hpp"
#include "vector"
#include <ctime>s

class Spawner {

    private:

        // Private Variables

        // Private Functions
        void initVariables();
        

    public:

        // Constructor
        Spawner();

        // Destructor
        ~Spawner();

        // Public Variables
        std::vector<Enemy*> enemies;

        // Getter

        // Setter

        // Public Functions
        void spawnEnemy();
        void upadteEnemies();
        void render(sf::RenderTarget& target);

};