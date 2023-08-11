#include "GUI.hpp"

void GUI::initVariables() {
    this->numFrames = 121;
    this->frameWidth = 15972.f / numFrames;
    this->frameHeight = 132.f;
    this->frameDuration = sf::seconds(0.03f);
    this->frameRect = sf::IntRect(0,0,frameWidth, frameHeight);
    this->currentFrame = 0;
    std::cout << frameWidth  << '\n';
    std::cout << frameHeight << '\n';
}

void GUI::initSprite() {
    this->loadSpriteSheetTexture();
    this->sprite.setTexture(spritesheetTexture);
    this->sprite.scale(2.5f, 2.5f);
}

void GUI::loadSpriteSheetTexture() {
    if (!this->spritesheetTexture.loadFromFile("/Users/roberttarabrin/Documents/GitHub/Undertale_Muffet_Game/textures/muffet_spriteSheet.png")) {
        std::cout << "TEXTURE LOADING ERROR :: ANIMATION: muffet_spriteSheet.png";
    }
}

GUI::GUI() {
    this->initVariables();
    this->initSprite();
}

GUI::~GUI() {
    
}

void GUI::setFrameRect(const int currentFrame) {
    int frameWidth = frameRect.width;
    int frameHeight = frameRect.height;

    frameRect.left = currentFrame * frameWidth;
    sprite.setTextureRect(frameRect);
}

void GUI::setSpritePosition(const float x, const float y) {
    this->sprite.setPosition(x - ((this->sprite.getGlobalBounds().width / 2) / numFrames), y - this->sprite.getGlobalBounds().height);
    std::cout << this->sprite.getGlobalBounds().width / 2  << '\n';
}

void GUI::update(sf::Time deltaTime) {
    totalTime += deltaTime;

    if (totalTime >= frameDuration) {
        totalTime -= frameDuration;
        currentFrame = (currentFrame + 1) % numFrames;
        setFrameRect(currentFrame);
    }
}

void GUI::render(sf::RenderTarget* target) {
    target->draw(sprite);
}