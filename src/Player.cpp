#include "Player.hpp"

/*
    private Functions
*/

/*  
    @return void
*/  
void Player::initVariables() {
    this->movementSpeed = 7.f;
}

/*  Initializes the window.
    @return void
*/
void Player::initPlayer() {
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(30.f,30.f));
}

/*  Constructor

*/
Player::Player(float x, float y) {
    this->shape.setPosition(x,y);

    this->initVariables();
    this->initPlayer();

}

/*  Destructor
    Destroys the Object after usage. 
*/
Player::~Player() {
}

void Player::updateInput() {

    // Keybord Input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->shape.move(-this->movementSpeed, 0.f);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->shape.move(this->movementSpeed, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->shape.move(0.f, -this->movementSpeed);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->shape.move(0.f, this->movementSpeed);
    }

}

void Player::update(sf::RenderTarget* target) {

    // Window bounds collision
    // TODO

    // Keybord Input
    this->updateInput();

}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->shape);
}

