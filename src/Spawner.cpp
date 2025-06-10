#include "Spawner.hpp"


/**
 *  Private Functions
 */


 /**
  * @brief Initializes all variables of spawner.
  */
void Spawner::initVariables() {
    this->eventTimerMax = 18;
    this->eventTimer = 0;
    this->penTimer = 0;
    this->penTimerMax = 1;
    this->speedTimerMax = 1;
    this->speedTimer = this->speedTimerMax;
    this->spawnPosX = 0.f;
    this->spawnPosY = 0.f;
    this->randomEvent = SINGLE;
    this->latestEvent = SINGLE;
    this->speedIncrease = 0.f;
    this->outsideSpawn = true;
    this->penalty = false;
    this->path = 1;
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
    // Updates the event
    if(this->eventTimer >= this->eventTimerMax) {
        this->eventTimer = 0;
        this->speedIncrease += 0.1f;

        // Checks for repetition. One event should not repeat back to back.
        int r = std::rand() % (size - 1);
        this->randomEvent = (r >= this->latestEvent) ? (r + 1) : r;

        // Handles changes of enemies for each events.
        switch(this->latestEvent) {
            case SINGLE:
                this->penTimerMax = 0;
                break;
            case PAIR:
                this->penTimerMax = 2;
                break;
            case LANE:
                this->outsideSpawn = true;
                this->penTimerMax = 3;
                break;
            case SPEED:
                this->speedTimer = this->speedTimerMax;
                this->penTimerMax = 0;
            case PATH:
                this->path = 1;
                this->directionUp = false;
                this->penTimerMax = 2;
            default:
                break;
        }

        this->latestEvent = this->randomEvent;
        this->penalty = true;
    }

    // Adds a spawn penalty for each event, so it doesnt spawn enemys directly after changing events.
    if(!this->penalty) {
        this->spawnEnemies(this->randomEvent);
    } else {
        if(this->penTimer >= this->penTimerMax) {
            this->penTimer = 0;
            this->penalty = false;
        }
        this->penTimer += 1;
    }

    this->eventTimer += 1;
}


/**
 * @brief Mehod to spawn enemies based on the random event chosen in Spawner::spawn.
 */
void Spawner::spawnEnemies(int& event) {
    switch (event) {
        case SINGLE: this->spawnSingleEnemy(); break;
        case PAIR: this->spawnEnemyPair(); break;
        case LANE: this->spawnEnemiesLane(); break;
        case SPEED: this->spawnSpeedyEnemy(); break;
        case PATH: this->spawnEnemiesPath(); break;
        default: break;
    }
}


/**
 * @brief Spawns single enemy on given conditions.  // change speed
 */
void Spawner::spawnSingleEnemy(int& position, float& speed) {
    this->movementSpeed = speed + this->speedIncrease;

    if((position % 2) == 1) {
        // Left spawn
        this->spawnPosX = this->spawnPointsX[0];
        this->spawnPosY = this->spawnPointsY[(position-1) / 2];
    } else {
        // Right spawn 
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[(position/2) - 1];
    }

    Enemy* newEnemy = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position, this->movementSpeed);
    this->enemies.push_back(newEnemy);
}


/**
 * @brief Spawns single enemy on one of the 6 spawn points. // change speed
 */
void Spawner::spawnSingleEnemy() {
    int randomPosition = rand() % 6 + 1;
    this->movementSpeed = 8.f + this->speedIncrease;

    if((randomPosition % 2) == 1) {
        // Left spawn
        this->spawnPosX = this->spawnPointsX[0];
        this->spawnPosY = this->spawnPointsY[(randomPosition-1) / 2];
    } else {
        // Right spawn 
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[(randomPosition/2) - 1];
    }

    Enemy* newEnemy = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, randomPosition, this->movementSpeed);
    this->enemies.push_back(newEnemy);
}


/**
 * @brief Spawns two enemies next to each other. // change speed
 */
void Spawner::spawnEnemyPair() {
    int randomPosition = rand() % 4 + 1;
    this->movementSpeed = 5.f + this->speedIncrease/2;

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

        Enemy* newEnemy = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, randomPosition, this->movementSpeed);
        this->enemies.push_back(newEnemy);
    }
}


/**
 * @brief Spawns enemies on top and bottom which create gaps and faster enemies in the middle.
 */
void Spawner::spawnEnemiesLane() {
    if(this->outsideSpawn) {
        int position1 = 2;
        int position2 = 6;
        this->movementSpeed = 3.f + this->speedIncrease/2;

        // Top Enemy
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[0];
        Enemy* newEnemy1 = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position1, this->movementSpeed);
        this->enemies.push_back(newEnemy1);

        // Bottom Enemy
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[2];
        Enemy* newEnemy2 = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position2, this->movementSpeed);
        this->enemies.push_back(newEnemy2);

        this->outsideSpawn = false;

    } else {
        int position = 3;
        this->movementSpeed = 8.f + this->speedIncrease;

        this->spawnPosX = this->spawnPointsX[0];
        this->spawnPosY = this->spawnPointsY[1];
        Enemy* newEnemy = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position, this->movementSpeed);
        this->enemies.push_back(newEnemy);

        this->outsideSpawn = true;
    }
}


/**
 * @brief Spawns less but very fast enemies.
 */
void Spawner::spawnSpeedyEnemy() {
    if(this->speedTimer >= this->speedTimerMax) {
        this->speedTimer = 0;
        
        // Spawns the enemy
        int randomPosition = rand() % 6 + 1;
        this->movementSpeed = 11.f + this->speedIncrease/2;

        this->spawnSingleEnemy(randomPosition, this->movementSpeed);
        
    } else {
        this->speedTimer += 1;
    }
}


/**
 * @brief Spawns enemies in such way that it creates a path between them.
 */
void Spawner::spawnEnemiesPath() {
    this->movementSpeed = 6.f + this->speedIncrease/2;
    // Level 1 is free
    if(this->path == 0) {
        int position1 = 4;
        int position2 = 6;

        // Middle Enemy
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[1];
        Enemy* newEnemy1 = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position1, this->movementSpeed);
        this->enemies.push_back(newEnemy1);

        // Bottom Enemy
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[2];
        Enemy* newEnemy2 = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position2, this->movementSpeed);
        this->enemies.push_back(newEnemy2);

        this->path = 1;
        this->directionUp = false;

    // Level 2 is free
    } else if(this->path == 1) {
        int position1 = 2;
        int position2 = 6;

        // Top Enemy
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[0];
        Enemy* newEnemy1 = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position1, this->movementSpeed);
        this->enemies.push_back(newEnemy1);

        // Bottom Enemy
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[2];
        Enemy* newEnemy2 = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position2, this->movementSpeed);
        this->enemies.push_back(newEnemy2);

        this->path = (this->directionUp) ? 0 : 2;

    // Level 3 is free
    } else if(this->path == 2) {
        int position1 = 2;
        int position2 = 4;

        // Top Enemy
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[0];
        Enemy* newEnemy1 = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position1, this->movementSpeed);
        this->enemies.push_back(newEnemy1);

        // Middle Enemy
        this->spawnPosX = this->spawnPointsX[1];
        this->spawnPosY = this->spawnPointsY[1];
        Enemy* newEnemy2 = new Enemy(this->dataDir, this->spawnPosX, this->spawnPosY, position2, this->movementSpeed);
        this->enemies.push_back(newEnemy2);

        this->path = 1;
        this->directionUp = true;
    }
}








