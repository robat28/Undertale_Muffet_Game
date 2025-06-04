#include "Game.hpp"


/**
 *  Private Functions
 */


/**
 *  @brief Initializes all Variables of the Game class with default values.
 */
void Game::initVariables() {
    srand(time(NULL));
    // Window
    this->windowSizeX = this->window->getSize().x;
    this->windowSizeY = this->window->getSize().y;
    // Playfield
    this->playfieldCenterX = 0.f;
    this->playfieldCenterY = 0.f;
    this->playfieldPosX = 0.f;
    this->playfieldPosY = 0.f;
    this->borderThickness = this->playfield->getBorderThickness();
    // Animation 
    this->spritePosX = 0.f;
    this->spritePosY = 0.f;
    // Player
    this->playerStartPosX = 0.f;
    this->playerStartPosY = 0.f;
    this->playerPositionX = 0.f;
    // Cooldowns
    this->buttonCooldownMax = 5.5f;
    this->buttonCooldown = this->buttonCooldownMax;
    this->iFramesMax = 60.f;
    this->iFrames = iFramesMax;
    this->impactFrames = 0.f;
    // Spawner
    this->spawnTimerMax = 15.f;
    this->spawnTimer = 0.f;
    // Enemy
    this->enemyDamage = 4.f;
    std::vector<Enemy*> enemies = {};
    // Deafeat Variables
    this->defeatFlag = NORMAL;
    this->gameOverTimer = 0;
    this->gameOver = false;
    this->switchToDFScreen = false;
}


/**
 * @brief Calculate the right Position for the Playfield and also sets the postion of the Playfield and the Position of
 * the three layers of levels.
 */
void Game::initPlayfield() {
    this->playfieldCenterX = this->windowSizeX / 2.f;
    this->playfieldCenterY = this->windowSizeY / 1.4f;

    this->playfieldPosX = playfieldCenterX - (this->playfield->getWidth() / 2.f - this->borderThickness);
    this->playfieldPosY = playfieldCenterY - (this->playfield->getHeight() / 2.f - this->borderThickness);

    this->playfield->setPosition(playfieldPosX, playfieldPosY);
    this->playfield->setLevelPositions(this->playfield->getBounds().position.x, playfieldCenterY);
}


/**
 * @brief Sets the position of the Muffet animation right above the palyfield.
 * @remark Dividend of setSpritePosition().y is a wild guess but it looks good.
 */
void Game::initGUI() {
    this->spritePosX = this->windowSizeX / 2.f - this->gui->getSpriteWidth() / 2.f;
    this->spritePosY = this->windowSizeY / 1.75f - this->gui->getSpriteHeight();
    this->gui->setSpritePosition(this->spritePosX, this->spritePosY);

    this->gui->setHPBarPosition(this->playfieldPosX + this->playfield->getWidth() / 4.f, this->playerStartPosY + this->playfield->getHeight() / 2.f + 25.f);
    this->gui->setPlayerNamePosition(this->playfieldPosX - this->gui->getPlayerNameSizeX() / 2, this->playerStartPosY + this->playfield->getHeight() / 2 + this->gui->getPlayerNameSizeY() * 1.4f);
    this->gui->setTimerPosition(this->windowSizeX / 2.f, this->windowSizeY - 30.f);
}


/**
 * @brief Sets the spawn position of the player in the middle of the Playfield on the second level.
 */
void Game::initPlayer() {
    this->playerStartPosX = this->window->getSize().x / 2.f - this->player->getWidth() / 2.f;
    this->playerStartPosY = this->playfield->getBounds().position.y + this->playfield->getHeight() / 2 - this->player->getHeight() / 2.f;
    this->player->setPosition(this->playerStartPosX, this->playerStartPosY);
}


/**
 * @brief Initializes all constant values after initialization of all objects.
 */
void Game::initConst() {
    // Playfield
    this->leftPlayfieldBorder = this->playfield->getBounds().position.x + this->borderThickness;
    this->rightPlayfieldBorder = this->playfield->getBounds().position.x + this->playfield->getBounds().size.x - this->borderThickness;
    // Enemy
    this->oddEnemyBorder = this->playfield->getBounds().position.x + 1.25 * this->playfield->getBounds().size.x;
    this->evenEnemyBorder = this->playfield->getBounds().position.x - (this->playfield->getBounds().size.x / 4) - this->spawner->getEnemySize();
}


/**
 * @brief Updates the frame of the Muffet animation. 
 */
void Game::updateDeltaTime() {
    this->deltaTime = deltaClock.restart();
    this->gui->updateSprite(deltaTime);
}


/**
 * @brief 
 */
void Game::updateTimer() {
    this->gui->updateVisualTimer(this->clock);
}


/**
 * @brief Handles the movement of the player in every direction.
 * @remark Can only press UP and DOWN if canPressButton is true (cooldown is up). 
 */
void Game::updateInput() {
    // Get the players position
    this->playerPositionX = this->player->getBounds().position.x;
    
    // Can move only if your alive
    if(this->player->getHp() > 0.f) {
        // Moving LEFT
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
            this->player->move(-1.f, 0.f);
        } 
        // Moving RIGHT
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
                this->player->move(1.f, 0.f);
        }
        // Moving UP
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) && this->canPressButton()) {
            switch(this->player->getCurrentLevel()) {
                case TOP: 
                    break;
                case MIDDLE: 
                    this->player->setNewLevel(TOP);
                    this->player->setPosition(this->playerPositionX, playfieldCenterY - (this->playfield->getBounds().size.y / 4) - (this->player->getHeight() / 2));
                    break;
                case BOTTOM:
                    this->player->setNewLevel(MIDDLE);
                    this->player->setPosition(this->playerPositionX, playfieldCenterY - (this->player->getHeight() / 2));
                    break;
                default:
                    break;
            }
        }
        // Moving DOWN
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) && this->canPressButton())  {
            switch(this->player->getCurrentLevel()) {
                case TOP: 
                    this->player->setNewLevel(MIDDLE);
                    this->player->setPosition(this->playerPositionX, playfieldCenterY - (this->player->getHeight() / 2));
                    break;
                case MIDDLE: 
                    this->player->setNewLevel(BOTTOM);
                    this->player->setPosition(this->playerPositionX, (playfieldCenterY + this->playfield->getBounds().size.y / 4) - (this->player->getHeight() / 2));
                    break;
                case BOTTOM:
                    break;
                default:
                    break;
            }
        }   
    }

    // Collision check
    this->updateCollisionPlayfield(); 
    this->updateCollisionEnemy();
}


/**
 *  @brief If the Player touches the Border on the left or right of the Playfield, the Players position gets set to his previous one, 
 *  so he can't move any further.
 */
void Game::updateCollisionPlayfield() {
    //Left
    if(this->player->getBounds().position.x <= this->leftPlayfieldBorder) {
        this->player->setPosition(this->playfield->getBounds().position.x + this->borderThickness, this->player->getBounds().position.y);
    }
    //Right
    else if(this->player->getBounds().position.x + this->player->getBounds().size.x > this->rightPlayfieldBorder) {
        this->player->setPosition((this->playfield->getBounds().position.x) + (this->playfield->getBounds().size.x) - (this->player->getBounds().size.x) - this->borderThickness, 
        this->player->getBounds().position.y);
    }
}


/**
 * @brief Handles actions functionally and visually when colliding with an enemy.
 * @remark iFrames in int for mod-operator.
 */
void Game::updateCollisionEnemy() {
    // Actions after colliding with an enemy
    if(this->player->getHp() > 0) {
        if(this->iFrames <= this->iFramesMax) {
            this->iFrames += 1;
            // Makes player visible 
            if((this->iFramesMax - 5  > this->iFrames) && this->iFrames % 10 == 0) {
                this->player->setColor(255, 255, 255 ,255);
            } 
            // Makes player transparent
            else if((this->iFramesMax - 5  > this->iFrames) && this->iFrames % 5 == 0) {
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
        }        
    }
    
    // Actions when colliding with an enemy 
    if(this->iFrames >= this->iFramesMax) {
        for(Enemy* enemy : this->spawner->getEnemyVector()) {
            // Player gets hit
            if(this->player->getBounds().findIntersection(enemy->getBounds())) {
                this->iFrames = 0.f;
                this->player->takeDamage(this->enemyDamage);
                this->gui->setSizeHPRemaining(sf::Vector2f(35.f * this->player->getHp() / this->player->getHpMax(), 30.f));
                this->gui->setHpString(this->player->getHp());

                if(this->player->getHp() <= 0) {
                    this->gameOver = true;
                    this->deathAction();
                }
                
                // Should not play with death
                this->gui->playHitSound();
            }
        }
    }
}


/** 
 * @brief Increases the buttonCooldown if the Button got pressed and set to 0.f. Gets called (buttonCooldownMax / buttonCooldown) times till 
 * buttonCooldown is up.
 */
void Game::updateButtonCooldown() {
    if(this->buttonCooldown < this->buttonCooldownMax) {
        this->buttonCooldown += 0.5f;
    }
}


/**
 * @brief Updates the spawning and moving of enemeis.
 */
void Game::updateEnemies() {
    this->spawnTimer += 0.5f;
    if(this->spawnTimer >= this->spawnTimerMax) {
        this->spawnTimer = 0.f;
        this->spawner->spawnEnemiesRandom(this->window, this->playfield, this->dataDir);
    }
    this->moveEnemy();
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
 * @brief Helping method to animate the "shaking" of the screen when hit.
 */
void Game::shakeScreen() {
    if(this->impactFrames == 0.f) {
        this->impactFrames = 2.f;
    }
    this->playfield->setPosition(playfieldPosX - this->impactFrames, playfieldPosY - this->impactFrames);
    this->playfield->setLevelPositions(this->playfield->getBounds().position.x - this->impactFrames, playfieldCenterY - this->impactFrames);
    this->player->setPosition(this->player->getBounds().position.x - this->impactFrames, this->player->getBounds().position.y - this->impactFrames);
    this->gui->setSpritePosition(this->spritePosX - this->impactFrames, this->spritePosY - this->impactFrames);

    for(Enemy* enemy : this->spawner->getEnemyVector()) {
        enemy->setPosition(enemy->getBounds().position.x - this->impactFrames, enemy->getBounds().position.y - this->impactFrames);
    }
}


/**
 * @brief Helping method to reset the shaking of one instance and reduce the amplitude.
 */
void Game::resetScreen() {
    this->playfield->setPosition(playfieldPosX, playfieldPosY);
    this->playfield->setLevelPositions(this->playfield->getBounds().position.x, playfieldCenterY);
    this->player->setPosition(this->player->getBounds().position.x + this->impactFrames, this->player->getBounds().position.y + this->impactFrames);
    this->gui->setSpritePosition(this->spritePosX, this->spritePosY);

    for(Enemy* enemy : this->spawner->getEnemyVector()) {
        enemy->setPosition(enemy->getBounds().position.x + this->impactFrames, enemy->getBounds().position.y + this->impactFrames);
    }

    this->impactFrames -= 1.f;
}


/**
 * @brief Moves odd enemies right (+1) and even enemies left (-1).
 */
void Game::moveEnemy() {     
    auto& enemies = this->spawner->getEnemyVector();
    for (auto it = enemies.begin(); it != enemies.end();) {
        Enemy* enemy = *it;
        bool shouldRemove = false;
        // Move right
        if (enemy->getSpawnPoint() % 2 == 1) {
            if (this->borderReachedOdd(*enemy))
                shouldRemove = true;
            else
                enemy->move(1.f, 0.f);
        // Move left
        } else {
            if (this->borderReachedEven(*enemy))
                shouldRemove = true;
            else
                enemy->move(-1.f, 0.f);
        }
        // deletes enemy after enemy reached the border
        if (shouldRemove) {
            it = enemies.erase(it);
            delete enemy;
        } else {
            ++it;
        }
    }    
}


/**
 * @brief Checks for enemies with odd spawn position if they reached their given border border.
 */
bool Game::borderReachedOdd(Enemy& movingEnemy) const {
    if(movingEnemy.getBounds().position.x >= this->oddEnemyBorder) {
            return true;
    } else {
        return false;
    }
}


/**
 * @brief Checks for enemies with even spawn position if they reached their given border border.
 */
bool Game::borderReachedEven(Enemy& movingEnemy) const {
     if(movingEnemy.getBounds().position.x <= this->evenEnemyBorder) {
            return true;
    } else {
        return false;
    }
}   


/**
 * @brief Handles all one-time actions after losing all HP.
 */
void Game::deathAction() {
    this->gui->stopMusic();
}


/**
 * @brief Handles the death animation for transition to the deafeat screen.
 */
void Game::deathAnimation() {
    // Update
    if(this->gameOverTimer < 125) {
        this->gameOverTimer += 1;
    }
    // Break the Heart
    if(this->gameOverTimer == 30 && defeatFlag == NORMAL) {
        this->gameOverTimer = 0;
        this->player->setDefeatTexture();
        this->gui->playDefeatSound();
        this->defeatFlag = BROKEN;
    // Fading
    } else if(this->gameOverTimer >= 80 && this->defeatFlag == 1) {
        this->player->setColor(255,255,255,250 - this->gameOverTimer * 2);
    }
    // Reset timer after heart completely vanished
    if(this->gameOverTimer == 125 && this->defeatFlag == BROKEN) {
        this->gameOverTimer = 0;
        this->defeatFlag = VANISHED;
    }
    // Switch to Defeat Menu
    if(this->gameOverTimer == 30 && this->defeatFlag == VANISHED) {
        this->switchToDFScreen = true;
    }
}


/**
 *  Public Functions
 */


/**
 * @brief Constructor of Game object.
 * @remark The Order of the init functions is important, else you can get seg fault.
 */
Game::Game(std::string dataDir, sf::RenderWindow *window) {
    this->dataDir = dataDir;
    this->window = window;

    this->playfield = new Playfield();
    this->gui = new GUI(this->dataDir, this->window);
    this->player = new Player(this->dataDir);
    this->spawner = new Spawner();

    this->initVariables();
    this->initPlayfield();
    this->initPlayer();
    this->initGUI();
    this->initConst();

    this->gui->playMusic();
}


/**
 * @brief Destroy the Game object.
 */
Game::~Game() {
    // Just in case
    this->spawner->deleteEnemies();

    delete this->playfield;
    delete this->gui;
    delete this->player;
    delete this->spawner;
}


/**
 * @brief Get the Final Time object
 */
const std::string Game::getFinalTime() const {
    return this->gui->getFinalTimer();
}


/**
 *  @brief The update function of the main method. Executes all update function of the game to update every frame.
 */
void Game::update() {
    if(!gameOver) {
        this->updateDeltaTime();
        this->updateTimer();
        this->updateInput();
        this->updateButtonCooldown();
        this->updateEnemies();
    }
}


/**
 * @brief The render function of the main method. Draws every object every frame after it got updated to simulate movement.
 * @remark The order of the function is important.
 *          1. window->clear();
 *          2. All render functions
 *          3. window->display(); 
 *          First, you clear the window and draw the same object at differnet places and after you display the window on your screen. 
 */
void Game::render() {
    this->window->clear();

    if(!gameOver) {
        this->playfield->render(*this->window);
        this->gui->render();
        this->spawner->render(*this->window);
        this->player->render(*this->window);
    } else {
        this->player->render(*this->window);
        this->deathAnimation();
    }

    this->window->display();
}




