#include "Player.hpp"

/*  Load a texture from file.
    @return void
*/
void Player::initTexture() {
    if(!this->texture.loadFromFile("/Users/roberttarabrin/Documents/GitHub/Undertale_Muffet_Game/textures/player_icon.png")) {
        std::cout << "TEXTURE LOADING ERROR :: PLAYER: textures/heart_icon.png";
    }
}

/*  Set the texture to the sprite.
    @return void
*/
void Player::initSprite() {
    this->sprite.setTexture(this->texture);

    // Resize the sprite
    this->sprite.scale(0.02f,0.02f);
}

/*  Constructor

*/
Player::Player() {

    this->movementSpeed = 4.f;
    this->initTexture();
    this->initSprite();
}

/*  Destructor
    Destroys the Object after usage. 
*/
Player::~Player() {
}


const sf::FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();
}

const float Player::getHeight() const {
    return this->getBounds().height;
}

const float Player::getWidth() const {
    return this->getBounds().width;
}


void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x,y);
}


void Player::move(const float x, const float y) {
    this->sprite.move(this->movementSpeed * x, this->movementSpeed * y);
}

void Player::update(const sf::RenderTarget* target) {

}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}

