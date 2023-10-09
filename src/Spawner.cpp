#include "Spawner.hpp"



/**
 *  Private Functions
 */


void Spawner::initVariables() {
}


/**
 *  Public Functions
 */


/**
 *  @brief Construct a new Spawner object.
 */
Spawner::Spawner() {
    this->initVariables();
    this->enemy = new Enemy();
}

/**
 *  @brief Destroy the Spawner object.
 */
Spawner::~Spawner() {
}

/**
 *  @brief 
 * 
 */
void Spawner::spawnEnemiesRandom(sf::RenderTarget* window, Playfield* playfield, std::string& dataDir) {
    this->randomPosition = rand() % 6 + 1;
    this->spawnPosY = window->getSize().y / 1.4f;
        if((this->randomPosition % 2) == 1) {
            this->spawnPosX = (playfield->getBounds().left) - (playfield->getBounds().width / 4) - this->enemy->getSize();
            switch(this->randomPosition) {
                case 1:
                    this->spawnPosY = this->spawnPosY - (playfield->getBounds().height / 4) - (this->enemy->getSize() / 2);
                    break;
                case 3:
                    this->spawnPosY = this->spawnPosY - this->enemy->getSize() / 2;
                    break;
                case 5:
                     this->spawnPosY = this->spawnPosY + (playfield->getBounds().height / 4) - (this->enemy->getSize() / 2);
                     break;
            }
        }
        else {
            this->spawnPosX = (playfield->getBounds().left) + (playfield->getBounds().width) + (playfield->getBounds().width / 4);
            switch(this->randomPosition) {
                case 2:
                    this->spawnPosY = this->spawnPosY - (playfield->getBounds().height / 4) - (this->enemy->getSize() / 2);
                    break;
                case 4:
                    this->spawnPosY = this->spawnPosY - this->enemy->getSize() / 2;
                    break;
                case 6:
                     this->spawnPosY = this->spawnPosY + (playfield->getBounds().height / 4) - (this->enemy->getSize() / 2);
                     break;
            }
        }
    Enemy* newEnemy = new Enemy(this->spawnPosX, this->spawnPosY, randomPosition, dataDir);
    this->enemies.push_back(newEnemy);
}
