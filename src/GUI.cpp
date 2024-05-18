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
    this->hitSound.setBuffer(this->hitBuffer);
    this->hitSound.setVolume(15.f);

    this->defeatSound.setBuffer(this->defeatSoundBuffer);
    this->defeatSound.setVolume(15.f);

    this->gameOverTheme.setBuffer(this->gameOverThemeBuffer);
    this->gameOverTheme.setVolume(15.f);
}

void GUI::initHealthBar() {
    this->healthBarRemaining.setSize(sf::Vector2f(35.f, 30.f));
    this->healthBarLost.setSize(sf::Vector2f(35.f, 30.f));

    this->healthBarRemaining.setFillColor(sf::Color(255, 255, 0));
    this->healthBarLost.setFillColor(sf::Color(255, 0, 0));
}

void GUI::initHealthText() {
    this->healthText.setFont(this->font);
    this->healthText.scale(0.7f, 0.7f);
    this->healthText.setString("");
    this->setHpString(20);
}

void GUI::initGameOverText() {
    this->gameOverTextTop.setFont(this->font);
    this->gameOverTextTop.setString("Game");
    this->gameOverTextTop.setCharacterSize(120);
    this->gameOverTextTop.setOrigin(this->gameOverTextTop.getLocalBounds().width / 2, this->gameOverTextTop.getLocalBounds().height / 2);

    this->gameOverTextBottom.setFont(this->font);
    this->gameOverTextBottom.setString("Over");
    this->gameOverTextBottom.setCharacterSize(120);
    this->gameOverTextBottom.setOrigin(this->gameOverTextBottom.getLocalBounds().width / 2, this->gameOverTextBottom.getLocalBounds().height / 2);
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
    if(!this->defeatSoundBuffer.loadFromFile(this->dataDir + "sounds/Undertale Death Sound Effect.wav")) {
        std::cout << "SOUND LOADING ERROR::GUI::damaged.wav" << '\n';
    }
     if(!this->gameOverThemeBuffer.loadFromFile(this->dataDir + "sounds/game_over_theme.wav")) {
        std::cout << "SOUND LOADING ERROR::GUI::game_over_theme.wav" << '\n';
    }
}

void GUI::loadMusic() {
    if(!this->ingameOST.openFromFile(this->dataDir + "sounds/spider_dance_ost.wav")) {
        std::cout << "MUSIC LOADING ERROR::GUI::spider_dance_ost.wav" << '\n';
    }
    this->ingameOST.setLoop(true);
    this->ingameOST.setVolume(15.f);
    this->ingameOST.play();
}

void GUI::loadFont() {
    if(!this->font.loadFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
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
    this->loadFont();
    this->initSprite();
    this->initSounds();
    this->initAnimationVariables();
    this->initHealthBar();
    this->initHealthText();
    this->loadMusic();
    this->initGameOverText();
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

void GUI::setHPBarPosition(const float& x, const float& y) {
    this->healthBarRemaining.setPosition(x, y);
    this->healthBarLost.setPosition(x, y);
    this->healthText.setPosition(x + 60.f, y + 5.f);
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

void GUI::setSize(sf::Vector2f size) {
    this->healthBarRemaining.setSize(size);
}

void GUI::setHpString(const int& currentHp) {
    if(currentHp >= 10) {
        this->healthText.setString(std::to_string(currentHp) + " / 20");
    } else {
        this->healthText.setString("0" + std::to_string(currentHp) + " / 20");
    }
}

void GUI::setGameOverVisibility(const int& visibility) {
    if(visibility*2 < 255) {
        this->gameOverTextTop.setFillColor(sf::Color(255, 255, 255, visibility * 2));
        this->gameOverTextBottom.setFillColor(sf::Color(255, 255, 255, visibility * 2));
    }
}

void GUI::setGameOverTextPosition(const int& x, const int& y) {
    this->gameOverTextTop.setPosition(x, y);
    this->gameOverTextBottom.setPosition(x , y + this->gameOverTextTop.getGlobalBounds().height + 10.f);
}

void GUI::stopMusic() {
    this->ingameOST.stop();
}

void GUI::playDefeatSound() {
    this->defeatSound.play();
}

void GUI::playGameOverSound() {
    this->gameOverTheme.play();
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
    target.draw(this->healthBarLost);
    target.draw(this->healthBarRemaining);
    target.draw(this->healthText);
}

void GUI::renderGameOver(sf::RenderTarget& target) {
    target.draw(this->gameOverTextTop);
    target.draw(this->gameOverTextBottom);
}