#include "GUI.hpp"

/**
 *  Private Functions
 */


/**
 *  @brief Initializes all Variables of the Animation.
 *  @remark The Frames of the sprite sheet has to be set horizontaly.
 *  @remark The single Frame should be a square.
 *  @example 200px x 200px for one frame.
 */
void GUI::initAnimationVariables() {
    this->frameLength = this->sprite.getTexture()->getSize().y;
    this->numFrames = this->sprite.getTexture()->getSize().x / frameLength;
    this->frameDuration = sf::seconds(0.03f);
    this->frameRect = sf::IntRect(0,0,frameLength, frameLength);
    this->currentFrame = 0.f;
}

/**
 *  @brief Initializes the Sprite by loading the texture first.
 */
void GUI::initSprite() {
    this->loadSpriteSheetTexture();
    this->sprite.setTexture(spritesheetTexture);
    this->sprite.scale(3.f, 3.f);
}

void GUI::initSounds() {
    this->loadSounds();
    this->hitSound.setBuffer(hitBuffer);
    this->hitSound.setVolume(15.f);
}

/**
 *  @brief Loads the Texture from the file and handles it if it can't. 
 */
void GUI::loadSpriteSheetTexture() {
    if (!this->spritesheetTexture.loadFromFile(this->dataDir + "textures/muffet_spriteSheet.png")) {
        std::cout << "TEXTURE LOADING ERROR::GUI::muffet_spriteSheet.png" << '\n';
    }
}

/**
 *  @brief 
 */
void GUI::loadSounds() {
    if(!this->hitBuffer.loadFromFile(this->dataDir + "sounds/damaged.wav")) {
        std::cout << "SOUND LOADING ERROR::GUI::damaged.wav" << '\n';
    }
}

void GUI::loadMusic() {
    if(!this->music.openFromFile(this->dataDir + "sounds/spider_dance_ost.wav")) {
        std::cout << "MUSIC LOADING ERROR::GUI::spider_dance_ost.wav" << '\n';
    }
    this->music.setLoop(true);
    this->music.setVolume(15.f);
    this->music.play();
}

/**
 *  Public Functions
 */


/**
 *  @brief Construct a new GUI object.
 */
GUI::GUI(std::string dataDir) {
    this->dataDir = dataDir;
    this->initSprite();
    this->initSounds();
    this->initAnimationVariables();
    this->loadMusic();
}

/**
 *  @brief Destroy the GUI object.
 */
GUI::~GUI() {
}


void GUI::playHitSound() {
    this->hitSound.play();
}

/**
 * @brief Sets the position of the sprite centered above the playfield. 
 * @param x const float
 * @param y const float
 */
void GUI::setSpritePosition(const float& x, const float& y) {
    this->sprite.setPosition(x, y);
}

const float GUI::getSpriteWidth() const {
    return this->sprite.getGlobalBounds().width / numFrames;
}

const float GUI::getSpriteHeight() const {
    return this->sprite.getGlobalBounds().height;
}

/**
 * @brief Sets the new current frame as texture.
 * @param currentFrame 
 */
void GUI::setFrameRect(const int& currentFrame) {
    this->frameRect.left = currentFrame * this->frameLength;
    this->sprite.setTextureRect(this->frameRect);
}

/**
 *  @brief Updates the Animation frame.
 *  @param deltaTime 
 */
void GUI::updateSprite(sf::Time& deltaTime) {
    this->totalTime += deltaTime;

    if(this->totalTime >= this->frameDuration) {
        this->totalTime -= this->frameDuration;
        this->currentFrame = (this->currentFrame + 1) % this->numFrames;
        setFrameRect(this->currentFrame);
    }
}

/**
 *  @brief Draws the current Frame of the Animation.
 *  @param target The window
 */
void GUI::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}
