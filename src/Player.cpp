#include "Player.hpp"

/**
 *  Private Functions
 */


/**
 *  @brief Initializes all variables for the player.
 */
void Player::initPlayer() {
    this->movementSpeed = 4.f;
    this->currentLevel = MIDDLE;
}

/**
 *  @brief Loads the Texture from the file and handles it if it can't.
 */
void Player::initTexture() {
    if(!this->texture.loadFromFile("/Users/roberttarabrin/Documents/GitHub/Undertale_Muffet_Game/textures/player_icon.png")) {
        std::cout << "TEXTURE LOADING ERROR::PLAYER::textures/heart_icon.png";
    }
}

/**
 *  @brief Sets the texture to the sprite and scales it to the right size.
 */ 
void Player::initSprite() {
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.022f,0.022f);
}


/**
 *  Public Functions
 */


/**
 *  @brief Construct a new Player object.
 */
Player::Player() {
    this->initPlayer();
    this->initTexture();
    this->initSprite();
}

/**
 *  @brief Destroy the Player object.
 */
Player::~Player() {
}

/**
 *  @brief Getter for the Bounds of the player.
 *  @return const sf::FloatRect
 */
const sf::FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();
}

/**
 *  @brief Getter for the Height of the player.
 *  @return const float 
 */
const float Player::getHeight() const {
    return this->getBounds().height;
}

/**
 *  @brief Getter for the Width of the player.
 *  @return const float 
 */
const float Player::getWidth() const {
    return this->getBounds().width;
}

/**
 *  @brief Getter for the Level of the player. 
 *  @return LEVEL 
 */
 LEVEL Player::getCurrentLevel() {
    return this->currentLevel;
 }

/**
 *  @brief Sets new Level of the player.
 *  @param newLevel 
 */
void Player::setNewLevel(LEVEL newLevel) {
    this->currentLevel = newLevel;
}

/**
 *  @brief Sets new position of the player.
 *  @param x const float
 *  @param y const float
 */
void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x,y);
}

/**
 *  @brief The move function to the left and right of the player. 
 *  @remark Uses sf::move to set the new position which works like an animtion of movement.
 *  @param x const float
 *  @param y const float
 */
void Player::move(const float x, const float y) {
    this->sprite.move(this->movementSpeed * x, this->movementSpeed * y);
}

/**
 *  @brief Draws the player on the window.
 *  @param target The window
 */
void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}

