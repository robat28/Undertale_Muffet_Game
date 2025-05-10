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
    this->frameLength = this->sprite->getTexture().getSize().y;
    this->numFrames = this->sprite->getTexture().getSize().x / frameLength;
    this->frameDuration = sf::seconds(0.03f);
    this->frameRect = sf::IntRect({0,0},{frameLength, frameLength});
    this->currentFrame = 0.f;
}

/**
 *  @brief Initializes the Sprite by loading the texture first.
 */
void GUI::initSprite() {
    this->loadSpriteSheetTexture();
    sprite = std::make_unique<sf::Sprite>(this->spritesheetTexture);
    this->sprite->scale({3.f, 3.f});
}

void GUI::initSounds() {
    this->loadSounds();
    this->hitSound = std::make_unique<sf::Sound>(this->hitBuffer);
    this->hitSound->setVolume(15.f);

    defeatSound = std::make_unique<sf::Sound>(this->defeatBuffer);
    this->defeatSound->setVolume(15.f);

    this->gameOverTheme = std::make_unique<sf::Sound>(this->gameOverBuffer);
    this->gameOverTheme->setVolume(15.f);
}

void GUI::initHealthBar() {
    this->healthBarRemaining.setSize(sf::Vector2f(35.f, 30.f));
    this->healthBarLost.setSize(sf::Vector2f(35.f, 30.f));

    this->healthBarRemaining.setFillColor(sf::Color(255, 255, 0));
    this->healthBarLost.setFillColor(sf::Color(255, 0, 0));
}

void GUI::initHealthText() {
    this->loadFont();
    healthText = std::make_unique<sf::Text>(this->font);
    this->healthText->scale({0.7f, 0.7f});
    this->healthText->setString("");
    this->setHpString(20);
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
    if(!this->defeatBuffer.loadFromFile(this->dataDir + "sounds/Undertale Death Sound Effect.wav")) {
        std::cout << "SOUND LOADING ERROR::GUI::damaged.wav" << '\n';
    }
     if(!this->gameOverBuffer.loadFromFile(this->dataDir + "sounds/game_over_theme.wav")) {
        std::cout << "SOUND LOADING ERROR::GUI::game_over_theme.wav" << '\n';
    }
}


void GUI::loadMusic() {
    if(!this->ingameOST.openFromFile(this->dataDir + "sounds/spider_dance_ost.wav")) {
        std::cout << "MUSIC LOADING ERROR::GUI::spider_dance_ost.wav" << '\n';
    }
    this->ingameOST.setLooping(true);
    this->ingameOST.setVolume(15.f);
}


void GUI::loadFont() {
    if(!this->font.openFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
        std::cout << "FONT LOADING ERROR::GUI::fonts/ingame-hud-font.ttf" << '\n';
    }
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
    this->initHealthBar();
    this->initHealthText();
    this->loadMusic();
}

/**
 *  @brief Destroy the GUI object.
 */
GUI::~GUI() {
}


void GUI::playHitSound() {
    this->hitSound->play();
}

/**
 * @brief Sets the position of the sprite centered above the playfield. 
 * @param x const float
 * @param y const float
 */
void GUI::setSpritePosition(const float& x, const float& y) {
    this->sprite->setPosition({x, y});
}

void GUI::setHPBarPosition(const float& x, const float& y) {
    this->healthBarRemaining.setPosition({x, y});
    this->healthBarLost.setPosition({x, y});
    this->healthText->setPosition({x + 60.f, y + 5.f});
}

const float GUI::getSpriteWidth() const {
    return this->sprite->getGlobalBounds().size.x / numFrames;
}

const float GUI::getSpriteHeight() const {
    return this->sprite->getGlobalBounds().size.y;
}

/**
 * @brief Sets the new current frame as texture.
 * @param currentFrame 
 */
void GUI::setFrameRect(const int& currentFrame) {
    this->frameRect.position.x = currentFrame * this->frameLength;
    this->sprite->setTextureRect(this->frameRect);
}

void GUI::setSize(sf::Vector2f size) {
    this->healthBarRemaining.setSize(size);
}

void GUI::setHpString(const int& currentHp) {
    if(currentHp >= 10) {
        this->healthText->setString(std::to_string(currentHp) + " / 20");
    } else {
        this->healthText->setString("0" + std::to_string(currentHp) + " / 20");
    }
}

void GUI::playMusic() {
    this->ingameOST.play();
}

void GUI::stopMusic() {
    this->ingameOST.stop();
}

void GUI::playDefeatSound() {
    this->defeatSound->play();
}

void GUI::playGameOverSound() {
    this->gameOverTheme->play();
}

void GUI::stopGameOverSound() {
    this->gameOverTheme->stop();
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
    target.draw(*this->sprite);
    target.draw(this->healthBarLost);
    target.draw(this->healthBarRemaining);
    target.draw(*this->healthText);
}

