#include "GUI.hpp"


/**
 *  Private Functions
 */


/**
 * @brief Initializes all variables of GUI.
 */
void GUI::initVariables() {
    this->currentFrame = 0.f;
    this->frameDuration = sf::seconds(0.03f);
    this->numFrames = this->sprite->getTexture().getSize().x / this->frameLength;
}


/**
 * @brief Initializes the variables of the sprite.
 * @remark The frames of the sprite sheet has to be set horizontaly.
 * @remark The single frame should be a square, e.g. 200px x 200px for one frame.
 */
void GUI::initSprite() {
    this->sprite = std::make_unique<sf::Sprite>(this->spritesheetTexture);
    this->frameLength = this->sprite->getTexture().getSize().y;
    this->frameRect = sf::IntRect({0,0},{this->frameLength, this->frameLength});

    // Clip to the very first frame
    this->sprite->setTextureRect(this->frameRect);
    this->sprite->scale({3.f, 3.f});
}


/**
 * @brief Initializes the variables of the sounds, like the hitsound.
 */
void GUI::initSounds() {
    this->hitSound = std::make_unique<sf::Sound>(this->hitBuffer);
    this->hitSound->setVolume(15.f);

    this->defeatSound = std::make_unique<sf::Sound>(this->defeatBuffer);
    this->defeatSound->setVolume(15.f);

    this->gameOverTheme = std::make_unique<sf::Sound>(this->gameOverBuffer);
    this->gameOverTheme->setVolume(15.f);
}


/**
 * @brief Initializes the variables of the numerical health view.
 */
void GUI::initHealthText() {
    this->healthText = std::make_unique<sf::Text>(this->font);
    this->healthText->scale({0.7f, 0.7f});
    this->healthText->setString("");
    this->setHpString(20);
}


/**
 * @brief Initializes the variables of the graphical health view.
 */ 
void GUI::initHealthBar() {
    this->healthBarRemaining.setSize(sf::Vector2f(35.f, 30.f));
    this->healthBarLost.setSize(sf::Vector2f(35.f, 30.f));

    this->healthBarRemaining.setFillColor(sf::Color(255, 255, 0));
    this->healthBarLost.setFillColor(sf::Color(255, 0, 0));
}    


/**
 * @brief Initializes the variables of the fixed player name.
 */
void GUI::initPlayerName() {
    this->playerName = std::make_unique<sf::Text>(this->font);
    this->playerName->scale({0.7f, 0.7f});
    this->playerName->setString("FRISK    LV1");
}


/**
 * @brief Initializes the variables for the timer.
 */
void GUI::initTimer() {
    this->time = std::make_unique<sf::Text>(this->font);
    this->time->setFillColor(sf::Color::White);
    this->time->scale({0.7f, 0.7f});

    this->time->setString("00:00:00");
    auto bounds = this->time->getLocalBounds();
    this->time->setOrigin({bounds.position.x + bounds.size.x / 2.f,bounds.position.y  + bounds.size.y/2.f});
}


/**
 * @brief Loads the Texture from the file and handles it if it can't. 
 */
void GUI::loadSpriteSheetTexture() {
    if (!this->spritesheetTexture.loadFromFile(this->dataDir + "textures/muffet_spriteSheet.png")) {
        std::cout << "TEXTURE LOADING ERROR::GUI::muffet_spriteSheet.png" << '\n';
    }
}


/**
 * @brief Loads the Sounds for hit, defeat and game over from the files and handles it if it can't. 
 */
void GUI::loadSounds() {
    if(!this->hitBuffer.loadFromFile(this->dataDir + "sounds/damaged.wav")) {
        std::cout << "SOUND LOADING ERROR::GUI::damaged.wav" << '\n';
    }
    if(!this->defeatBuffer.loadFromFile(this->dataDir + "sounds/death_sound.wav")) {
        std::cout << "SOUND LOADING ERROR::GUI::death_sound.wav" << '\n';
    }
     if(!this->gameOverBuffer.loadFromFile(this->dataDir + "sounds/game_over_theme.wav")) {
        std::cout << "SOUND LOADING ERROR::GUI::game_over_theme.wav" << '\n';
    }
}


/**
 * @brief Loads the music from the file and handles it if it can't. 
 */
void GUI::loadMusic() {
    if(!this->ingameOST.openFromFile(this->dataDir + "sounds/spider_dance_ost.wav")) {
        std::cout << "MUSIC LOADING ERROR::GUI::spider_dance_ost.wav" << '\n';
    }
    this->ingameOST.setLooping(true);
    this->ingameOST.setVolume(15.f);
}


/**
 * @brief Loads the font from the file and handles it if it can't.
 */
void GUI::loadFont() {
    if(!this->font.openFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
        std::cout << "FONT LOADING ERROR::GUI::fonts/ingame-hud-font.ttf" << '\n';
    }
}


/**
 *  Public Functions
 */


/**
 *  @brief Constructor of GUI.
 */
GUI::GUI(std::string dataDir, sf::RenderWindow* window) {
    this->dataDir = dataDir;
    this->window = window;

    // Loading
    this->loadSpriteSheetTexture();
    this->loadFont();
    this->loadSounds();
    this->loadMusic();

    // Init
    this->initSprite();
    this->initVariables();
    this->initHealthBar();
    this->initHealthText();
    this->initPlayerName();
    this->initSounds();
    this->initTimer();
}


/**
 * @brief Getter for the width of the animation sprite.
 */
const float GUI::getSpriteWidth() const {
    return this->sprite->getGlobalBounds().size.x;
}


/**
 * @brief Getter for the height of the animation sprite.
 */
const float GUI::getSpriteHeight() const {
    return this->sprite->getGlobalBounds().size.y;
}


/**
 * @brief Getter for the x size of the player name.
 */
const float GUI::getPlayerNameSizeX() const {
    return this->playerName->getGlobalBounds().size.x;
}


/**
 * @brief Getter for the y size of the player name.
 */
const float GUI::getPlayerNameSizeY() const {
    return this->playerName->getGlobalBounds().size.y;
}


/**
 * @brief Getter for the width of the timer string.
 */
const float GUI::getTimerSizeX() const {
    return this->time->getGlobalBounds().size.x;
}


/**
 * @brief Getter for the height of the timer string.
 */
const float GUI::getTimerSizeY() const {
    return this->time->getGlobalBounds().size.y;
}


/**
 * @brief Getter for the string of the sf::Text timer.
 */
const std::string GUI::getFinalTimer() const {
    return this->time.get()->getString();
}


/**
 * @brief Sets the position of the sprite centered above the playfield. 
 */  
void GUI::setSpritePosition(const float& x, const float& y) {
    this->sprite->setPosition({x, y});
}        


/**
 * @brief Sets the position of the HP bar below the playfield. 
 */  
void GUI::setHPBarPosition(const float& x, const float& y) {
    this->healthBarRemaining.setPosition({x, y});
    this->healthBarLost.setPosition({x, y});
    this->healthText->setPosition({x + 60.f, y + 5.f});
}


/**
 * @brief Sets the position of the player name next to the HP bar.
 */
void GUI::setPlayerNamePosition(const float& x, const float& y) {
    this->playerName->setPosition({x, y});
}


/**
 * @brief Sets the position of the visual timer below the HP Bar.
 */
void GUI::setTimerPosition(const float& x, const float& y) {
    this->time->setPosition({x, y});
}


/**
 * @brief Sets the new current frame from the sprite sheet as texture.
 */
void GUI::setFrameRect(const int& currentFrame) {
    this->frameRect.position.x = currentFrame * this->frameLength;
    this->sprite->setTextureRect(this->frameRect);
}    


/**
 * @brief Sets the new numerical HP.
 */
void GUI::setHpString(const int& currentHp) {
    if(currentHp >= 10) {
        this->healthText->setString(std::to_string(currentHp) + " / 20");
    } else {
        this->healthText->setString("0" + std::to_string(currentHp) + " / 20");
    }
}


/**
 * @brief Sets the size of the remaining HP bar.
 */ 
void GUI::setSizeHPRemaining(sf::Vector2f size) {
    this->healthBarRemaining.setSize(size);
}    


/**
 * @brief Starts playing the ingame OST while playing the game.
 */
void GUI::playMusic() {
    this->ingameOST.play();
}


/**
 * @brief Stops the ingame OST playing. 
 */
void GUI::stopMusic() {
    this->ingameOST.stop();
}


/**
 * @brief Starts playing the game over sound after losing the game.
 */
void GUI::playGameOverSound() {
    this->gameOverTheme->play();
}


/**
 * @brief Stops the game over sound.
 */
void GUI::stopGameOverSound() {
    this->gameOverTheme->stop();
}

/**
 * @brief Plays the hit sound after player got hit.
 */       
void GUI::playHitSound() {
    this->hitSound->play();
}                            


/**
 * @brief Plays the defeat sound after player got hit.
 */
void GUI::playDefeatSound() {
    this->defeatSound->play();
}


/**
 * @brief Updates the timer shown on the screen. Needs to be converted from sf::Time to float to string.
 */
void GUI::updateVisualTimer(sf::Clock& clock) {
    int totalMs = clock.getElapsedTime().asMilliseconds();

    int minutes = totalMs / 60000;
    int seconds = (totalMs / 1000) % 60;
    int centiseconds = (totalMs / 10) % 100;

    // Build "MM:SS:CC" with leading zeros
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ':'
        << std::setw(2) << std::setfill('0') << seconds << ':'
        << std::setw(2) << std::setfill('0') << centiseconds;

    this->time->setString(oss.str());
}


/**
 * @brief Updates the current frame of the sprite sheet.
 */
void GUI::updateSprite(sf::Time& deltaTime) {
    this->totalTime += deltaTime;

    if(this->totalTime >= this->frameDuration) {
        this->totalTime -= this->frameDuration;
        this->currentFrame = (this->currentFrame + 1) % this->numFrames;
        this->setFrameRect(this->currentFrame);
    }
}


/**
 *  @brief Draws the current Frame of the Animation.
 */
void GUI::render() {
    this->window->draw(*this->sprite);
    this->window->draw(this->healthBarLost);
    this->window->draw(this->healthBarRemaining);
    this->window->draw(*this->healthText);
    this->window->draw(*this->playerName);
    this->window->draw(*this->time);
}

