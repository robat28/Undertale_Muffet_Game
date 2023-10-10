#include "Game.hpp"

/**
 *  Private Functions
 */


/**
 *  @brief Initializes all Variables of the Game class with a default value.
 */
void Game::initVariables() {
    srand(time(NULL));
    this->playfieldCenterX = 0.f;
    this->playfieldCenterY = 0.f;
    this->playfieldPosX = 0.f;
    this->playfieldPosY = 0.f;
    this->spritePosX = 0.f;
    this->spritePosY = 0.f;
    this->playerStartPosX = 0.f;
    this->playerStartPosY = 0.f;
    this->buttonCooldownMax = 5.5f;
    this->buttonCooldown = this->buttonCooldownMax;
    this->spawnTimerMax = 15.f;
    this->spawnTimer = 0.f;
    this->iFramesMax = 60.f;
    this->iFrames = iFramesMax;
    this->enemyDamage = 4.f;
    this->impactFrames = 0.f;

}

/**
 *  @brief Initializes and sets all Properties of the window.
 *  @remark FramerateLimit is at 60 Frames, so the game appears same on most devices.
 */
void Game::initWindow() {
    this->vMode.width = 1000;
    this->vMode.height = 750;
    this->window = new sf::RenderWindow(this->vMode, "Undertale Muffet Minigame", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
} 

/**
 *  @brief Calculate the right Position for the Playfield and also sets the postion of the Playfield and the Position of
 *  the three layers of levels.
 *  @remark Dividend of playfieldCenterY is a wild guess but it looks good.
 *  @remark You have to subtract 5 pixel, because of the Border size. 
 */
void Game::initPlayfield() {
    this->playfieldCenterX = this->window->getSize().x / 2.f;
    this->playfieldCenterY = this->window->getSize().y / 1.4f;

    this->playfieldPosX = playfieldCenterX - (this->playfield->getWidth() / 2.f - 5.f);
    this->playfieldPosY = playfieldCenterY - (this->playfield->getHeight() / 2.f - 5.f);

    this->playfield->setPosition(playfieldPosX, playfieldPosY);
    this->playfield->setLevelPositions(this->playfield->getBounds().left, playfieldCenterY);
}

/**
 *  @brief Sets the position of the Muffet animation right above the palyfield.
 *  @remark Dividend of setSpritePosition().y is a wild guess but it looks good.
 */
void Game::initAnimation() {
    this->spritePosX = this->window->getSize().x / 2.f - this->gui->getSpriteWidth() / 2;
    this->spritePosY = this->window->getSize().y / 1.75f - this->gui->getSpriteHeight();
    this->gui->setSpritePosition(this->spritePosX, this->spritePosY);
}

/**
 *  @brief Sets the spawn position of the player in the middle of the Playfield on the second level.
 */
void Game::initPlayer() {
    this->playerStartPosX = this->window->getSize().x / 2.f - this->player->getWidth() / 2.f;
    this->playerStartPosY = this->playfield->getBounds().top + this->playfield->getHeight() / 2 - this->player->getHeight() / 2.f;
    this->player->setPosition(this->playerStartPosX, this->playerStartPosY);
}


/**
 *  Public Functions
 */


/**
 *  @brief Construct a new Game object that initializes all objects needed to build the game.
 *  @remark The Order of the init functions is important, else you can get segmentation fault.
 */
Game::Game(std::string dataDir) {
    this->dataDir = dataDir;
    this->playfield = new Playfield();
    this->gui = new GUI(this->dataDir);
    this->player = new Player(this->dataDir);
    this->spawner = new Spawner();
    
    this->initWindow();
    this->initVariables();
    this->initPlayfield();
    this->initPlayer();
    this->initAnimation();
}

/**
 *  @brief Destroy the Game:: Game object
 */
Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->playfield;
    delete this->gui;
}

/**
 *  @brief Replaces the isOpen() method.
 *  @return true: While the window is not Closed.
 */
const bool Game::running() const {
    return this->window->isOpen();
}

/**
 *  @brief If buttonCooldown >= buttonCooldownMax, it sets buttonCooldown back to 0.f and returns true. 
 *  @return true: If cooldown is up and the button is ready to press. 
 */
const bool Game::canPressButton() {
    if(this->buttonCooldown >=  this->buttonCooldownMax) {
        this->buttonCooldown = 0.f;
        return true;
    }
    return false;
}

/**
 *  @brief Handles some main actions like closing window, etc.
 */
void Game::pollEvents() {
    while(this->window->pollEvent(this->evnt)) {
        switch(this->evnt.type) {
            case sf::Event::Closed: 
                this->window->close();
                break; 
            case sf::Event::KeyPressed:
                if(evnt.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;    
            default:
                break;
        }
        /*
        if(this->player->getHp() <= 0.f) {
            this->window->close();
        }
        */
        
    }
}

/**
 *  @brief The update function of the main method. Executes all update function of the game to update every frame.
 */
void Game::update() {
    this->pollEvents();
    this->updateDeltaTime();
    this->updateInput();
    this->updateButtonCooldown();
    this->upadteEnemies();
}

/**
 *  @brief Handles the movement of the player in every Direction.
 *  @remark The first Value of move is a multiplier of the movementspeed, so you can go left and right.
 *  @remark Can only press UP and DOWN if canPressButton is true (cooldown is up). 
 */
void Game::updateInput() {
    //Moving LEFT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->player->move(-1.f, 0.f);
    } 
    // Moving RIGHT
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->player->move(1.f, 0.f);
    }
    // Moving UP
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->canPressButton()) {
        switch(this->player->getCurrentLevel()) {
            case TOP: 
                break;
            case MIDDLE: 
                this->player->setNewLevel(TOP);
                this->player->setPosition(this->player->getBounds().left, playfieldCenterY - (this->playfield->getBounds().height / 4) - 
                                         (this->player->getHeight() / 2));
                break;
            case BOTTOM:
                this->player->setNewLevel(MIDDLE);
                this->player->setPosition(this->player->getBounds().left, playfieldCenterY - (this->player->getHeight() / 2));
                break;
            default:
                break;
        }
    }
    // Moving DOWN
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->canPressButton())  {
        switch(this->player->getCurrentLevel()) {
            case TOP: 
                this->player->setNewLevel(MIDDLE);
                this->player->setPosition(this->player->getBounds().left, playfieldCenterY - (this->player->getHeight() / 2));
                break;
            case MIDDLE: 
                this->player->setNewLevel(BOTTOM);
                this->player->setPosition(this->player->getBounds().left, (playfieldCenterY + this->playfield->getBounds().height / 4) - 
                                         (this->player->getHeight() / 2));
                break;
            case BOTTOM:
                break;
            default:
                break;
        }
    }
    // Collision check
    this->updateCollisonPlayfield();
    this->updateCollisionEnemy();
}

/**
 *  @brief If the Player touches the Border on the left or right of the Playfield, the Players position gets set to his previous one, 
 *  so he can't move any further.
 *  @remark You have to subtract add or sub 5 pixel, because of the Border. 
 */
void Game::updateCollisonPlayfield() {
    //Left
    if(this->player->getBounds().left < this->playfield->getBounds().left + 5) {
        this->player->setPosition(this->playfield->getBounds().left + 5, this->player->getBounds().top);
    }
    //Right
    else if(this->player->getBounds().left + this->player->getBounds().width > this->playfield->getBounds().left + this->playfield->getBounds().width - 5) {
        this->player->setPosition((this->playfield->getBounds().left) + (this->playfield->getBounds().width) - (this->player->getBounds().width) - 5, 
        this->player->getBounds().top);
    }
}

/**
 * 
 *  iFrames in int for modulo
 * 
 */
void Game::updateCollisionEnemy() {
    // Visual Iframes
    if(this->iFramesMax > this->iFrames)
        this->iFrames += 1;
        if(this->iFrames % 10 == 0) {
            this->player->setColor(255, 255, 255 ,255);
        } 
        else if(this->iFrames % 5 == 0) {
            this->player->setColor(255, 255, 255 ,150);
        }
        // Shaking Screen
        if(this->iFrames < 20) {
            if(this->iFrames % 8 == 0) {
                this->resetScreen();
            } 
            else if(this->iFrames % 4 == 0) {
                this->shakeScreen();
            }
        }

    if(this->iFrames >= this->iFramesMax) {
        for(Enemy* enemy : this->spawner->enemies) {
            if(this->player->getBounds().intersects(enemy->getBounds())) {
                this->iFrames = 0.f;
                this->player->takeDamage(this->enemyDamage);
                std::cout << this->player->getHp() << "HP left" << "\n";
                this->gui->playHitSound();

            }
        }
    }

    
}

/** 
 *  @brief Increases the buttonCooldown if the Button got pressed and set to 0.f. Gets called (buttonCooldownMax / buttonCooldown) times till 
 *  buttonCooldown is up.
 */
void Game::updateButtonCooldown() {
    if(this->buttonCooldown < this->buttonCooldownMax) {
        this->buttonCooldown += 0.5f;
    }
}

/**
 *  @brief Updates the frame of the Muffet animation. 
 */
void Game::updateDeltaTime() {
    this->deltaTime = clock.restart();
    this->gui->updateSprite(deltaTime);
}


/**
 *  @brief The render function of the main method. Draws every object every frame after it got updated to simulate movement.
 *  @remark The order of the function is important.
 *          1. window->clear();
 *          2. All render functions
 *          3. window->display(); 
 *          First, you clear the window and draw the same object at differnet places and after you display the window on your screen. 
 */
void Game::render() {
    this->window->clear();

    this->playfield->render(*this->window);
    this->gui->render(*this->window);

    for(auto enemy : this->spawner->enemies) {
        enemy->render(*this->window);
    }

    this->player->render(*this->window);

    this->window->display();
}

/**
 *  @brief 
 * 
 */
void Game::shakeScreen() {
    if(this->impactFrames == 0.f) {
        this->impactFrames = 2.f;
    }
    this->playfield->setPosition(playfieldPosX - this->impactFrames, playfieldPosY - this->impactFrames);
    this->playfield->setLevelPositions(this->playfield->getBounds().left - this->impactFrames, playfieldCenterY - this->impactFrames);
    this->player->setPosition(this->player->getBounds().getPosition().x - this->impactFrames, this->player->getBounds().getPosition().y - this->impactFrames);
    this->gui->setSpritePosition(this->spritePosX - 2.f, this->spritePosY - 2.f);

    for(Enemy* enemy : this->spawner->enemies) {
        enemy->setPosition(enemy->getBounds().getPosition().x - this->impactFrames, enemy->getBounds().getPosition().y - this->impactFrames);
    }
    this->impactFrames -= 1.f;

}

/**
 *  @brief 
 * 
 */
void Game::resetScreen() {
    this->playfield->setPosition(playfieldPosX, playfieldPosY);
    this->playfield->setLevelPositions(this->playfield->getBounds().left, playfieldCenterY);
    this->player->setPosition(this->player->getBounds().getPosition().x + this->impactFrames, this->player->getBounds().getPosition().y + this->impactFrames);
    this->gui->setSpritePosition(this->spritePosX, this->spritePosY);

    for(Enemy* enemy : this->spawner->enemies) {
        enemy->setPosition(enemy->getBounds().getPosition().x + this->impactFrames, enemy->getBounds().getPosition().y + this->impactFrames);
    }
}


// SPAWNER FUNCTOINS 

bool Game::borderReachedOdd(Enemy& movingEnemy) const {
    if(movingEnemy.getBounds().left >= (this->playfield->getBounds().left) + (this->playfield->getBounds().width) + (this->playfield->getBounds().width / 4)) {
            return true;
    } else {
        return false;
    }
}

bool Game::borderReachedEven(Enemy& movingEnemy) const {
     if(movingEnemy.getBounds().left <= (this->playfield->getBounds().left) - (this->playfield->getBounds().width / 4) - this->spawner->enemy->getSize()) {
            return true;
    } else {
        return false;
    }
}   

void Game::moveEnemy() { 
    for(auto* movingEnemy : this->spawner->enemies) {
        // Moving Right
        if((movingEnemy->getSpawnPoint() % 2) == 1) {
            if(this->borderReachedOdd(*movingEnemy)) {
                this->spawner->enemies.erase(this->spawner->enemies.begin());
                delete movingEnemy;
            } else {
                movingEnemy->move(1.f, 0.f);
            }
        } else {
        // Moving Left
            if(this->borderReachedEven(*movingEnemy)) {
                this->spawner->enemies.erase(this->spawner->enemies.begin());
                delete movingEnemy;
            } else {
                movingEnemy->move(-1.f, 0.f);
            }
        }
    }
}

void Game::upadteEnemies() {
    this->spawnTimer += 0.5f;
    if(this->spawnTimer >= this->spawnTimerMax) {
        this->spawnTimer = 0.f;
        this->spawner->spawnEnemiesRandom(this->window, this->playfield, this->dataDir);
    }
    this->moveEnemy();
}

// SPAWNER FUNCTOINS 
