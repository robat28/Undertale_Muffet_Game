#include "Enemy.hpp"


/**
 *  Private Functions
 */


/**
 *  @brief Initializes all Variables of the Enemy
 */
void Enemy::initVariables() {

}

/**
 *  @brief Initializes the Sprite by loading the texture first.
 */
void Enemy::initSprite() {
    this->loadEnemyTexture();
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.8f, 1.8f);
}

/**
 *  @brief Loads the Texture from the file and handles it if it can't.
 */
void Enemy::loadEnemyTexture() {
    if(!texture.loadFromFile("../../GitHub/Undertale_Muffet_Game/textures/spiderEnemy_sprite.png")) {
        std::cout << "TEXTURE LOADING ERROR::ENEMY::textures/spiderEnemy_sprite.png" << '\n';
    }
}


/**
 *  Public Functions
 */


/**
 *  @brief Construct a new Enemy object.
 */
Enemy::Enemy(float x, float y, const int spawnPosition) {
    this->initSprite();
    this->initVariables();
    this->sprite.setPosition(x,y);
    this->spawnPosition = spawnPosition;
}

/**
 *  @brief Destroy the Enemy object.
 */
Enemy::~Enemy() {
    std::cout << "DELETED ENEMY";
}

/**
 * @brief 
 * 
 * @return const sf::FloatRect 
 */
const sf::FloatRect Enemy::getBounds() const {
    return this->sprite.getGlobalBounds();
}


/**
 * @brief Set the position of the enemy at x / y.
 * @param x const float 
 * @param y const float
 */
void Enemy::setPosition(const float x, const float y) {
    this->sprite.setPosition(x,y);
}

/**
 * @brief 
 * 
 */
void Enemy::update() {

}

/**
 *  @brief Draws the Enemy.
 *  @param target The window
 */
void Enemy::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}