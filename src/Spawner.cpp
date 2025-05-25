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
 * @brief Constructor of Spawner.
 */
Spawner::Spawner() {
    this->initVariables();
    this->enemy = new Enemy();
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
void Spawner::render(sf::RenderTarget& target) {
    for(auto enemy : this->enemies) {
        enemy->render(target);
    }
}


/**
 * @brief Spawns enemies randomly on the 6 spawn positions.
 */
void Spawner::spawnEnemiesRandom(sf::RenderTarget* window, Playfield* playfield, std::string& dataDir) {
    this->randomPosition = rand() % 6 + 1;
    this->spawnPosY = window->getSize().y / 1.4f;
        if((this->randomPosition % 2) == 1) {
            this->spawnPosX = (playfield->getBounds().position.x) - (playfield->getBounds().size.x / 4) - this->enemy->getSize();
            switch(this->randomPosition) {
                case 1:
                    this->spawnPosY = this->spawnPosY - (playfield->getBounds().size.y / 4) - (this->enemy->getSize() / 2);
                    break;
                case 3:
                    this->spawnPosY = this->spawnPosY - this->enemy->getSize() / 2;
                    break;
                case 5:
                    this->spawnPosY = this->spawnPosY + (playfield->getBounds().size.y / 4) - (this->enemy->getSize() / 2);
                    break;
            }
        }
        else {
            this->spawnPosX = (playfield->getBounds().position.x) + (playfield->getBounds().size.x) + (playfield->getBounds().size.x / 4);
            switch(this->randomPosition) {
                case 2:
                    this->spawnPosY = this->spawnPosY - (playfield->getBounds().size.y / 4) - (this->enemy->getSize() / 2);
                    break;
                case 4:
                    this->spawnPosY = this->spawnPosY - this->enemy->getSize() / 2;
                    break;
                case 6:
                    this->spawnPosY = this->spawnPosY + (playfield->getBounds().size.y / 4) - (this->enemy->getSize() / 2);
                    break;
            }
        }
    Enemy* newEnemy = new Enemy(this->spawnPosX, this->spawnPosY, randomPosition, dataDir);
    this->enemies.push_back(newEnemy);
}
