#include "Playfield.hpp"


/**
 *  Private Functions
 */


/**
 * @brief Initializes the playfield.
 */
void Playfield::initPlayfield() {
    this->playfield.setSize(sf::Vector2f(325, 180));
    this->playfield.setFillColor(sf::Color(0, 0, 0, 255));
    this->playfield.setOutlineThickness(5);
    this->playfield.setOutlineColor(sf::Color(255, 255, 255, 255));
}


/**
 *  @brief Adds three same 'Levels' to the Container and sets their color.
 *  @remark Sub 25.f to make the level not as long as the playfield width for visual purpose.
 *  @remark One pixel height to create a Rectangle as a Line.
 */
void Playfield::initLevels() {
    this->levels.push_back(sf::RectangleShape(sf::Vector2f(this->playfield.getSize().x - 25.f, 1.f)));
    this->levels.push_back(sf::RectangleShape(sf::Vector2f(this->playfield.getSize().x - 25.f, 1.f)));
    this->levels.push_back(sf::RectangleShape(sf::Vector2f(this->playfield.getSize().x - 25.f, 1.f)));

    this->levels[0].setFillColor(sf::Color(100,100,100));
    this->levels[1].setFillColor(sf::Color(100,100,100));
    this->levels[2].setFillColor(sf::Color(100,100,100));
}


/**
 *  Public Functions
 */


/**
 * @brief Construct a new Playfield object.
 */
Playfield::Playfield() {
    this->initPlayfield();
    this->initLevels();
}


/**
 * @brief Getter for the Height of the Playfield.
 */
const float Playfield::getHeight() const {
    return this->getBounds().size.y;
}


/**
 * @brief Getter for the Width of the Playfield.
 */
const float Playfield::getWidth() const {
    return this->getBounds().size.x;
}


/**
 * @brief Getter for the bounds of the Playfield.
 */
const sf::FloatRect Playfield::getBounds() const {
    return this->playfield.getGlobalBounds();
}


/**
 * @brief Getter for the border thickness.
 */
const float Playfield::getBorderThickness() const {
    return this->playfield.getOutlineThickness();
}


/**
 * @brief Sets new position of the Playfied.
 */
void Playfield::setPosition(const float& x, const float& y) {
    this->playfield.setPosition({x,y});
}


/**
 * @brief Sets the position of the three levels based on the middle one.
 * @remark Used to initialize and for the shaking animation.
 */
void Playfield::setLevelPositions(const float& x, const float& y) {
    this->levels[0].setPosition({x + 15.f, y - this->playfield.getGlobalBounds().size.y / 4});
    this->levels[1].setPosition({x + 15.f, y});
    this->levels[2].setPosition({x + 15.f, y + (this->playfield.getGlobalBounds().size.y / 4)});
}


/**
 * @brief Draws the playfield Rectangle and the three levels.
 */
void Playfield::render(sf::RenderTarget& target) {
    target.draw(this->playfield);

    target.draw(this->levels[0]);
    target.draw(this->levels[1]);
    target.draw(this->levels[2]);
}


