#include "Player.hpp"

/*
    private Functions
*/


/*  Load a texture from file.
    @return void
*/
void Player::initTexture() {
    if(!this->texture.loadFromFile("textures/heart_icon.png")) {
        std::cout << "TEXTURE LOADING ERROR :: PLAYER: textures/heart_icon.png";
    }
}

/*  Set the texture to the sprite.
    @return void
*/
void Player::initSprite() {
    this->sprite.setTexture(this->texture);

    // Resize the sprite
    this->sprite.scale(0.04f,0.04f);
}

/*  Constructor

*/
Player::Player() {

    this->movementSpeed = 7.f;
    this->initTexture();
    this->initSprite();
}

/*  Destructor
    Destroys the Object after usage. 
*/
Player::~Player() {
}

void Player::move(const float x, const float y) {
    this->sprite.move(this->movementSpeed * x, this->movementSpeed * y);
}

void Player::update(const sf::RenderTarget* target) {

}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}

