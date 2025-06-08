#include "Enemy.hpp"


/**
 *  Private Functions
 */


/**
 * @brief Initializes all Variables of the Enemy.
 */
void Enemy::initVariables() {
    this->spriteSize = 30.f;
}


/**
 * @brief Initializes the Sprite by loading the texture first.
 */
void Enemy::initSprite() {
    this->sprite = std::make_unique<sf::Sprite>(this->texture);
    this->sprite->scale({1.875f, 1.875f});
}


/**
 * @brief Loads the font of the enemy. Returns error message if it can not find the directory.
 */
void Enemy::loadTexture() {
    if(!texture.loadFromFile(this->dataDir + "/textures/spiderEnemy_sprite.png")) {
        std::cout << "TEXTURE LOADING ERROR::ENEMY::textures/spiderEnemy_sprite.png" << '\n';
    }
}


/**
 *  Public Functions
 */


/**
 * @brief Default Contructor for accessing the size in Spawner.cpp.
 */
Enemy::Enemy() {
    this->initVariables();
}


/**
 * @brief Constructor of Enemy.
 */
Enemy::Enemy(std::string dataDir, const float& x, const float& y, const int& spawnPosition, const float& movementSpeed) {
    this->dataDir = dataDir;
    this->spawnPosition = spawnPosition;
    this->movementSpeed = movementSpeed;

    this->loadTexture();

    this->initVariables();
    this->initSprite();
    
    this->sprite->setPosition({x,y});
}


/**
 * @brief Returns the bounds of the Enemy as a sf::FloatRect.
 */
const sf::FloatRect Enemy::getBounds() const {
    return this->sprite->getGlobalBounds();
}


/**
 * @brief Returns the size of the enemy.
 */
const float Enemy::getSize() const {
    return this->spriteSize;
}


/**
 * @brief Returns the spawn position on the playfield.
 */
const int Enemy::getSpawnPoint() const{
    return this->spawnPosition;
}


/**
 * @brief Set the position of the enemy at (x, y).
 */
void Enemy::setPosition(const float& x, const float& y) {
    this->sprite->setPosition({x,y});
}


/**
 * @brief Sets the speed of the enemy
 */
void Enemy::setSpeed(const float& x) {
    this->movementSpeed = x;
}


/**
 * @brief Method to reposition/"move" the enemy on the screen.
 */
void Enemy::move(const float& x, const float& y) {
    this->sprite->move({this->movementSpeed * x, this->movementSpeed * y});
}


/**
 *  @brief Draws the Enemy.
 */
void Enemy::render(sf::RenderTarget& target) {
    target.draw(*this->sprite);
}
