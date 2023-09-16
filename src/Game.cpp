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
    this->buttonCooldownMax = 5.5f;
    this->buttonCooldown = this->buttonCooldownMax;
    this->spawnTimerMax = 15.f;
    this->spawnTimer = 0.f;
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
    this->gui->setSpritePosition(this->window->getSize().x / 2, this->window->getSize().y / 1.8);
}

/**
 *  @brief Sets the spawn position of the player in the middle of the Playfield on the second level.
 */
void Game::initPlayer() {
    this->player->setPosition(this->window->getSize().x / 2.f - this->player->getWidth() / 2.f, 
                              this->playfield->getBounds().top + this->playfield->getHeight() / 2 - this->player->getHeight() / 2.f);
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
    this->enemy = new Enemy(this->dataDir);
    
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
    delete this->enemy;
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
    }
}

bool Game::borderReachedOdd(Enemy& movingEnemy) const {
    if(movingEnemy.getBounds().left >= (this->playfield->getBounds().left) + (this->playfield->getBounds().width) + (this->playfield->getBounds().width / 4)) {
            return true;
    } else {
        return false;
    }
}

bool Game::borderReachedEven(Enemy& movingEnemy) const {
     if(movingEnemy.getBounds().left <= (this->playfield->getBounds().left) - (this->playfield->getBounds().width / 4) - this->enemy->getSize()) {
            return true;
    } else {
        return false;
    }
}   

/**
 * @brief 
 * 
 */
void Game::spawnEnemies() {
    this->randomPosition = rand() % 6 + 1;
    this->spawnPosY = this->window->getSize().y / 1.4f;
        if((this->randomPosition % 2) == 1) {
            this->spawnPosX = (this->playfield->getBounds().left) - (this->playfield->getBounds().width / 4) - this->enemy->getSize();
            switch(this->randomPosition) {
                case 1:
                    this->spawnPosY = this->spawnPosY - (this->playfield->getBounds().height / 4) - (this->enemy->getSize() / 2);
                    break;
                case 3:
                    this->spawnPosY = this->spawnPosY - this->enemy->getSize() / 2;
                    break;
                case 5:
                     this->spawnPosY = this->spawnPosY + (this->playfield->getBounds().height / 4) - (this->enemy->getSize() / 2);
                     break;
            }
        }
        else {
            this->spawnPosX = (this->playfield->getBounds().left) + (this->playfield->getBounds().width) + (this->playfield->getBounds().width / 4);
            switch(this->randomPosition) {
                case 2:
                    this->spawnPosY = this->spawnPosY - (this->playfield->getBounds().height / 4) - (this->enemy->getSize() / 2);
                    break;
                case 4:
                    this->spawnPosY = this->spawnPosY - this->enemy->getSize() / 2;
                    break;
                case 6:
                     this->spawnPosY = this->spawnPosY + (this->playfield->getBounds().height / 4) - (this->enemy->getSize() / 2);
                     break;
            }
        }
    Enemy* newEnemy = new Enemy(this->spawnPosX, this->spawnPosY, randomPosition, this->dataDir);
    this->enemies.push_back(newEnemy);
}

/**
 *  @brief 
 * 
 */
void Game::moveEnemy() { 
    for(auto* movingEnemy : this->enemies) {
        // Moving Right
        if((movingEnemy->getSpawnPoint() % 2) == 1) {
            if(this->borderReachedOdd(*movingEnemy)) {
                this->enemies.erase(this->enemies.begin());
                delete movingEnemy;
            } else {
                movingEnemy->move(1.f, 0.f);
            }
        } else {
        // Moving Left
            if(this->borderReachedEven(*movingEnemy)) {
                this->enemies.erase(this->enemies.begin());
                delete movingEnemy;
            } else {
                movingEnemy->move(-1.f, 0.f);
            }
        }
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
        this->player->setPosition((this->playfield->getBounds().left) + (this->playfield->getBounds().width) - (this->player->getBounds().width) - 5, this->player->getBounds().top);
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
 *  @brief 
 * 
 */
void Game::upadteEnemies() {
    this->spawnTimer += 0.5f;
    if(this->spawnTimer >= this->spawnTimerMax) {
        this->spawnTimer = 0.f;
        this->spawnEnemies();
    }
    this->moveEnemy();
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

    for(auto enemy : this->enemies) {
        enemy->render(*this->window);
    }

    this->player->render(*this->window);

    this->window->display();

}
