#include "Playfield.hpp"

void Playfield::initPlayfield() {
    this->playfield.setSize(sf::Vector2f(325, 180));

    this->playfield.setFillColor(sf::Color(0, 0, 0, 255));
    this->playfield.setOutlineThickness(5);
    this->playfield.setOutlineColor(sf::Color(255, 255, 255, 255));
}

//TODO
void Playfield::initLevels() {
    this->levels.push_back(sf::RectangleShape(sf::Vector2f(this->playfield.getSize().x - 25.f, 1.f)));
    this->levels.push_back(sf::RectangleShape(sf::Vector2f(this->playfield.getSize().x - 25.f, 1.f)));
    this->levels.push_back(sf::RectangleShape(sf::Vector2f(this->playfield.getSize().x - 25.f, 1.f)));

    this->levels[0].setFillColor(sf::Color(100,100,100));
    this->levels[1].setFillColor(sf::Color(100,100,100));
    this->levels[2].setFillColor(sf::Color(100,100,100));
}

Playfield::Playfield() {
    this->initPlayfield();
    this->initLevels();

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

void Playfield::setLevelPositions(const float x, const float y) {

    this->levels[0].setPosition(x + 15.f, y - this->playfield.getGlobalBounds().height / 4);
    this->levels[1].setPosition(x + 15.f, y);
    this->levels[2].setPosition(x + 15.f, y + (this->playfield.getGlobalBounds().height / 4));
}

void Playfield::render(sf::RenderTarget* target) {

    target->draw(this->playfield);
    
    for(sf::RectangleShape level : levels) {
        target->draw(level);
    }
}


