#ifndef _SPAWNER_
#define _SPAWNER_

#include "Enemy.hpp"
#include "Playfield.hpp"


class Spawner {
    private:

        // Enemies
        std::vector<Enemy*> enemies;
        Enemy* enemy;

        // Private Variables
        int randomPosition;
        float spawnPosX;
        float spawnPosY;

        // Private Functions
        void initVariables();

    public:

        // Constructor
        Spawner();

        // Getter 
        float getEnemySize();
        std::vector<Enemy*>& getEnemyVector();

        // Public Functions
        void deleteEnemies();
        void render(sf::RenderTarget& target);

        // Spawner Functions
        void spawnEnemiesRandom(sf::RenderTarget* window, Playfield* playfield, std::string& dataDir);
};

#endif