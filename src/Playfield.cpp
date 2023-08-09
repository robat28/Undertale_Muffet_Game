#include "Playfield.hpp"

void Playfield::initVariables() {

}

Playfield::Playfield() {
   
    this->playfield.setSize(sf::Vector2f(250,125));

    this->playfield.setFillColor(sf::Color(0,0,0,255));
    this->playfield.setOutlineThickness(5);
    this->playfield.setOutlineColor(sf::Color(255,255,255,255));
}

Playfield::~Playfield() {
}

const sf::FloatRect Playfield::getBounds() const {
    return this->playfield.getGlobalBounds();
}

const float Playfield::getHeight() const {
    return this->getBounds().height;
}

const float Playfield::getWidth() const {
    return this->getBounds().width;
}

void Playfield::setPosition(const float x, const float y) {
    this->playfield.setPosition(x,y);
}


void Playfield::render(sf::RenderTarget* target) {
    target->draw(this->playfield);
}



