#include "Enemy.hpp"


/**
 *  Private Functions
 */


/**
 *  @brief Initializes all Variables of the Enemy
 * 
 */
void Enemy::initVariables() {

}

/**
 *  @brief Initializes the Sprite by loading the texture first.
 */
void Enemy::initSprite() {
    this->loadEnemyTexture();
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.5f, 1.5f);
    this->sprite.setPosition(20, 20);
}

/**
 *  @brief Loads the Texture from the file and handles it if it can't.
 */
void Enemy::loadEnemyTexture() {
    if(!texture.loadFromFile("../../GitHub/Undertale_Muffet_Game/textures/spiderEnemy_sprite.png")) {
        std::cout << "TEXTURE LOADING ERROR::ENEMY::textures/spiderEnemy_sprite.png";
    }
}


/**
 *  Public Functions
 */


/**
 * @brief Construct a new Enemy object.
 */
Enemy::Enemy() {
    this->initSprite();
    this->initVariables();
}

/**
 * @brief Destroy the Enemy object.
 */
Enemy::~Enemy() {
    std::cout << "DELETED ENEMY";
}

/**
 *  @brief Draws the Enemy.
 *  @param target The window
 */
void Enemy::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}