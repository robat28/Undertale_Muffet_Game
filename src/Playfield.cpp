#include "Playfield.hpp"

void Playfield::initVariables() {

}

Playfield::Playfield() {
   
    this->playfield.setSize(sf::Vector2f(300,150));

    this->playfield.setFillColor(sf::Color(0,55,0));
    this->playfield.setOutlineThickness(5);
    this->playfield.setOutlineColor(sf::Color(255,255,255));
}

Playfield::~Playfield() {

}

const sf::FloatRect Playfield::getBounds() const {
    return this->playfield.getGlobalBounds();
}

void Playfield::setPosition(const float x, const float y) {
    this->playfield.setPosition(x,y);
}


void Playfield::render(sf::RenderTarget* target) {
    target->draw(this->playfield);
}



