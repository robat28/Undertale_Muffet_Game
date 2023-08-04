#include "Player.hpp"

/*
    private Functions
*/

/*  
    @return void
*/  
void Player::initVariables() {
    this->movementSpeed = 8.f;
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

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target) {

    // Left
    if(this->shape.getGlobalBounds().left <= 0.f) {
        this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
    }
    // Right    
    if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x) {
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }
    // Top
    if(this->shape.getGlobalBounds().top <= 0.f) {
        this->shape.setPosition(this->shape.getGlobalBounds().left ,0.f);  
    }
    // Bottom  
    if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y) {
        this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
    }
}

void Player::update(const sf::RenderTarget* target) {

     // Keybord Input
    this->updateInput();

    // Window bounds collision
    this->updateWindowBoundsCollision(target);

}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->shape);
}

