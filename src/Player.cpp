#include "Player.hpp"

/**
 *  Private Functions
 */


/**
 *  @brief Initializes all variables of the player.
 */
void Player::initPlayer() {
    this->setColor(255,255,255,250);
    this->movementSpeed = 4.f;
    this->hpMax = 4.f;
    this->hp = this->hpMax;
    this->currentLevel = MIDDLE;
}

/**
 *  @brief Loads the Texture from the file and handles it if it can't.
 */
void Player::initTexture() {
    if(!this->texture.loadFromFile(this->dataDir + "/textures/player_sprite.png", false)) {
        std::cout << "TEXTURE LOADING ERROR::PLAYER::textures/player_sprite.png" << '\n';
    }

    if(!this->defeatTexture.loadFromFile(this->dataDir + "/textures/defeated_player_sprite.png", false)) {
        std::cout << "TEXTURE LOADING ERROR::PLAYER::defeated_player_sprite.png" << '\n';
    }
}

/**
 *  @brief Sets the texture to the sprite and scales it to the right size.
 */ 
void Player::initSprite() {
    this->sprite = std::make_unique<sf::Sprite>(this->texture);
    this->sprite->scale({1.5f,1.5f});
    this->defeatSprite = std::make_unique<sf::Sprite>(this->defeatTexture);
    this->defeatSprite->scale({1.4f,1.4f});
}


/**
 *  Public Functions
 */


/**
 *  @brief Construct a new Player object.
 */
Player::Player(std::string dataDir) {
    this->dataDir = dataDir;

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
    return this->sprite->getGlobalBounds();
}

/**
 *  @brief Getter for the Height of the player.
 *  @return const float 
 */
const float Player::getHeight() const {
    return this->getBounds().size.y;
}

/**
 *  @brief Getter for the Width of the player.
 *  @return const float 
 */
const float Player::getWidth() const {
    return this->getBounds().size.x;
}

/**
 *  @brief Getter for the Level of the player. 
 *  @return LEVEL 
 */
const LEVEL Player::getCurrentLevel() {
    return this->currentLevel;
 }

/**
 *  @brief Getter for the Health Points of the player. 
 *  @return const float 
 */
 const float Player::getHp() {
    return this->hp;
 }

 /**
 *  @brief Getter for the maximum Health Points of the player. 
 *  @return const float 
 */
 const float Player::getHpMax() {
    return this->hpMax;
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
void Player::setPosition(const float& x, const float& y) {
    this->sprite->setPosition({x,y});
}

/**
 * @brief 
 * 
 * @param r 
 * @param g 
 * @param b 
 * @param transp 
 */
void Player::setColor(const float r, const float g, const float b, const float transp) {
    this->sprite->setColor(sf::Color(r, g, b, transp));
}

void Player::setTexture() {
    this->sprite->setTexture(this->texture);
}

void Player::setDefeatTexture() {
    this->defeatSprite->setPosition(this->sprite->getPosition());
    this->sprite = std::move(this->defeatSprite);
}

void Player::setHP(const int &health) {
    this->hp = health;
}

void Player::takeDamage(const float& damage) {
    if(this->hp > 0) 
        this->hp -= damage;
}

/**
 *  @brief The move function to the left and right of the player. 
 *  @remark Uses sf::move to set the new position which works like an animtion of movement.
 *  @param x const float
 *  @param y const float
 */
void Player::move(const float& x, const float& y) {
    this->sprite->move({this->movementSpeed * x, this->movementSpeed * y});
}

void Player::resetPlayerVariables() {
    this->initPlayer();
    this->setTexture();
}

/**
 *  @brief Draws the player on the window.
 *  @param target The window
 */
void Player::render(sf::RenderTarget& target) {
    target.draw(*this->sprite);
}

