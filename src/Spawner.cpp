#include "Spawner.hpp"


/**
 *  Private Functions
 */


 /**
  * @brief Initializes all variables of spawner.
  */
void Spawner::initVariables() {
    this->eventTimerMax = 19;
    this->eventTimer = 0;
    this->spawnPosX = 0.f;
    this->spawnPosY = 0.f;
    this->randomEvent = SINGLE;
}


/**
 * @brief Initializes and stores the spawn points of enemies in two vectors.
 */
void Spawner::initSpawnPositions() {
    // spawnPositionX[0] is odd/left spawns, etc.
    this->spawnPointsX.push_back((this->playfield->getBounds().position.x) - (this->playfield->getBounds().size.x / 4) - this->enemy->getSize());
    this->spawnPointsX.push_back((this->playfield->getBounds().position.x) + (this->playfield->getBounds().size.x) + (this->playfield->getBounds().size.x / 4));

    // spawnPositionY[0] is first level, etc.
    this->spawnPointsY.push_back((this->window->getSize().y / 1.4f) - (this->playfield->getBounds().size.y / 4) - (this->enemy->getSize() / 2));
    this->spawnPointsY.push_back((this->window->getSize().y / 1.4f) - this->enemy->getSize() / 2);
    this->spawnPointsY.push_back((this->window->getSize().y / 1.4f) + (this->playfield->getBounds().size.y / 4) - (this->enemy->getSize() / 2));
}


/**
 *  Public Functions
 */


/**
 * @brief Constructor of Spawner.
 */
Spawner::Spawner(std::string& dataDir, sf::RenderTarget* window, Playfield* playfield) {
    this->dataDir = dataDir;
    this->window = window;
    this->playfield = playfield;
    this->enemy = new Enemy();
    
    this->initVariables();
    this->initSpawnPositions();
}


/**
 * @brief Getter for the size of the enemy.
 */
float Spawner::getEnemySize() {
    return this->enemy->getSize();
}


/**
 * @brief Getter for the vector containing all enemies currently in the game.
 */
std::vector<Enemy*>& Spawner::getEnemyVector() {
    return this->enemies;
}


/**
 * @brief Method to delete and clear all enemies. E.g after losing the game.
 */
void Spawner::deleteEnemies() {
    for(Enemy* enemy : this->enemies) {delete enemy;}
    this->enemies.clear();
}


/**
 * @brief Draws all the enemies.
 */
void Spawner::render() {
    for(auto enemy : this->enemies) {
        enemy->render(*this->window);
    }
}


/**
 * @brief Spawner method called by Game.cpp. Generall call to spawn an enemy.
 */
void Spawner::spawn() {
    if(this->eventTimer >= this->eventTimerMax) {
        this->eventTimer = 0;
        this->randomEvent = rand() % size;
    }
    this->spawnEnemies(randomEvent);
    this->eventTimer += 1;
}


/**
 * @brief Mehod to spawn enemies based on the random event chosen in Spawner::spawn.
 */
void Spawner::spawnEnemies(int& event) {
    switch (event) {
    case SINGLE:
        this->spawnSingleEnemy();
        break;
    case PAIR:
        this->spawnEnemyPair();
        break;
    default:
        break;
    }
}


/**
 * @brief Spawns single enemy on one of the 6 spawn points.
 */
void Spawner::spawnSingleEnemy() {
    int randomPosition = rand() % 6 + 1;
    if((randomPosition % 2) == 1) {
        // Left spawn
        this->spawnPosX = this->spawnPointsX[0];
        this->spawnPosY = this->spawnPointsY[(randomPosition-1) / 2];
    } else {
        // Right spawn 
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[(randomPosition/2) - 1];
    }

    Enemy* newEnemy = new Enemy(this->spawnPosX, this->spawnPosY, randomPosition, this->dataDir);
    this->enemies.push_back(newEnemy);
}


/**
 * @brief Spawns two enemies next to each other.
 */
void Spawner::spawnEnemyPair() {
    int randomPosition = rand() % 4 + 1;
    for(int i = 0; i < 2; i++) {
        if((randomPosition % 2) == 1) {
            // Left spawn
            this->spawnPosX = this->spawnPointsX[0];
            this->spawnPosY = this->spawnPointsY[(randomPosition-1) / 2 + i];
        } else {
            // Right spawn 
            this->spawnPosX = this->spawnPointsX[1];
            this->spawnPosY = this->spawnPointsY[(randomPosition/2) - 1 + i];
        }

        Enemy* newEnemy = new Enemy(this->spawnPosX, this->spawnPosY, randomPosition, this->dataDir);
        this->enemies.push_back(newEnemy);
    }
}




