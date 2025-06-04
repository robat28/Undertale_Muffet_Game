#include "Player.hpp"

/**
 *  Private Functions
 */


/**
 *  @brief Initializes all variables of the player.
 */
void Player::initVariables() {
    this->currentLevel = MIDDLE;
    this->movementSpeed = 4.f;
    this->hpMax = 20.f;
    this->hp = this->hpMax;
}


/**
 *  @brief Initializes the variables of the player sprite.
 */ 
void Player::initSprites() {
    this->sprite = std::make_unique<sf::Sprite>(this->texture);
    this->sprite->scale({1.5f,1.5f});

    this->defeatSprite = std::make_unique<sf::Sprite>(this->defeatTexture);
    this->defeatSprite->scale({1.4f,1.4f});
}


/**
 *  @brief Loads the Texture from the file and handles it if it can't.
 */
void Player::loadTexture() {
    if(!this->texture.loadFromFile(this->dataDir + "/textures/player_sprite.png", false)) {
        std::cout << "TEXTURE LOADING ERROR::PLAYER::textures/player_sprite.png" << '\n';
    }

    if(!this->defeatTexture.loadFromFile(this->dataDir + "/textures/defeated_player_sprite.png", false)) {
        std::cout << "TEXTURE LOADING ERROR::PLAYER::defeated_player_sprite.png" << '\n';
    }
}


/**
 *  Public Functions
 */


/**
 *  @brief Construct a new Player object.
 */
Player::Player(std::string dataDir) {
    this->dataDir = dataDir;

    this->loadTexture();

    this->initSprites();
    this->initVariables();
}


/**
 *  @brief Getter for the Height of the player.
 */
const float Player::getHeight() const {
    return this->getBounds().size.y;
}


/**
 *  @brief Getter for the Width of the player.
 */
const float Player::getWidth() const {
    return this->getBounds().size.x;
}


/**
 *  @brief Getter for the Bounds of the player.
 */
const sf::FloatRect Player::getBounds() const {
    return this->sprite->getGlobalBounds();
}


/**
 *  @brief Getter for the Level of the player. 
 */
const LEVEL Player::getCurrentLevel() {
    return this->currentLevel;
}


/**
 *  @brief Getter for the Health Points of the player. 
 */
 const float Player::getHp() {
    return this->hp;
}


 /**
 * @brief Getter for the maximum Health Points of the player.  
 */
 const float Player::getHpMax() {
    return this->hpMax;
}


/**
 *  @brief Sets player on a new Level.
 */
void Player::setNewLevel(LEVEL newLevel) {
    this->currentLevel = newLevel;
}


/**
 *  @brief Sets new position of the player.
 */
void Player::setPosition(const float& x, const float& y) {
    this->sprite->setPosition({x,y});
}


/**
 * @brief Sets a new color / transparency of the player
 */
void Player::setColor(const float r, const float g, const float b, const float transp) {
    this->sprite->setColor(sf::Color(r, g, b, transp));
}


/**
 * @brief Set the sprite of the player as the complette heart.
 */
void Player::setTexture() {
    this->sprite->setTexture(this->texture);
}


/**
 * @brief Set the sprite of the player as the broken heart.
 */
void Player::setDefeatTexture() {
    this->defeatSprite->setPosition(this->sprite->getPosition());
    this->sprite = std::move(this->defeatSprite);
}


/**
 * @brief Reduces the health points if the player takes damage. 
 */
void Player::takeDamage(const float& damage) {
    this->hp -= damage;
}

/**
 *  @brief The move function to the left and right of the player. 
 *  @remark Uses sf::move to set the new position which works like an animtion of movement.
 */
void Player::move(const float& x, const float& y) {
    this->sprite->move({this->movementSpeed * x, this->movementSpeed * y});
}

/**
 *  @brief Draws the player on the window.
 */
void Player::render(sf::RenderTarget& target) {
    target.draw(*this->sprite);
}

