#include "DefeatMenu.hpp"


/**
 *  Private Functions
 */


/**
 * @brief Initializes all variables of the Defeatmenu.
 */
void DefeatMenu::initVariables() {
    this->selected = RETRY;
    this->iconDistanceToText = 65.f;
}


/**
 * @brief Initializes the variables for the Game Over text.
 */
void DefeatMenu::initGameOverText() {
    this->gameOverText_TOP = std::make_unique<sf::Text>(this->font);
    this->gameOverText_TOP->setString("Game");
    this->gameOverText_TOP->setCharacterSize(120);
    this->gameOverText_TOP->setOrigin({this->gameOverText_TOP->getLocalBounds().size.x / 2, this->gameOverText_TOP->getLocalBounds().size.y / 2});

    this->gameOverText_BOTTOM = std::make_unique<sf::Text>(this->font);
    this->gameOverText_BOTTOM->setString("Over");
    this->gameOverText_BOTTOM->setCharacterSize(120);
    this->gameOverText_BOTTOM->setOrigin({this->gameOverText_BOTTOM->getLocalBounds().size.x / 2, this->gameOverText_BOTTOM->getLocalBounds().size.y / 2});
    
    this->setGameOverTextPosition(this->window->getSize().x, this->window->getSize().y);
}


/**
 * @brief Initializes the variables for the menu text.
 */
void DefeatMenu::initMenuText() {
    this->text_RETRY = std::make_unique<sf::Text>(this->font);
    this->text_RETRY->setString("RETRY");
    this->text_RETRY->setCharacterSize(30);

    this->text_EXIT = std::make_unique<sf::Text>(this->font);
    this->text_EXIT->setString("EXIT");
    this->text_EXIT->setCharacterSize(30);

    this->setMenuTextPosition(this->window->getSize().x, this->window->getSize().y);
} 


/**
 * @brief Initializes the variables of the selection icon. 
 */
void DefeatMenu::initIcon() {
    this->icon = std::make_unique<sf::Sprite>(this->texture);
    this->icon->scale({0.035f, 0.035f});

    this->icon->setOrigin({this->icon->getGlobalBounds().size.x / 2, this->icon->getGlobalBounds().size.y / 2});
    this->icon->setPosition({this->text_RETRY->getPosition().x - this->text_RETRY->getGlobalBounds().size.x / 2, this->text_RETRY->getPosition().y - this->icon->getGlobalBounds().size.y / 2});
}


/**
 * @brief Initializes the variables for the visual time string of the previous run.
 */
void DefeatMenu::initFinalTime() {
    this->finalTime = std::make_unique<sf::Text>(this->font);
    this->finalTime->setString("00:00:00"); 
    this->finalTime->setCharacterSize(20);

    this->finalTime->setPosition({this->window->getSize().x / 2 - this->finalTime->getGlobalBounds().size.x / 2, this->gameOverText_BOTTOM->getPosition().y + this->gameOverText_BOTTOM->getGlobalBounds().size.y + 25.f});
    this->finalTime->setFillColor({128,128,128,255});
}


/**
 * @brief Loads the font of the defeat menu text. Returns error message if it can not find the directory.
 */
void DefeatMenu::loadFont() {
    if (!this->font.openFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
        std::cout << "FONT LOADING ERROR::DEFEATMENU::fonts/ingame-hud-font.ttf" << '\n';
    }
}


/**
 * @brief Loads the selection icon of the defeat menu. Returns error message if it can not find the directory.
 */
void DefeatMenu::loadTexture() {
    if (!this->texture.loadFromFile(this->dataDir + "textures/selection_icon.png")) {
        std::cout << "FONT LOADING ERROR::DEFEATMENU::textures/selection_icon.png" << '\n';
    }
}


/**
 * @brief Helper method to easier set the position of the "GAME OVER". 
 */
void DefeatMenu::setGameOverTextPosition(const float& x, const float& y) {
    this->gameOverText_TOP->setPosition({x / 2, y / 5});
    this->gameOverText_BOTTOM->setPosition({x / 2, (y / 5) + this->gameOverText_TOP->getGlobalBounds().size.y + 10.f});
}


/**
 * @brief Helper method to easier set the position of the menu text. 
 */
void DefeatMenu::setMenuTextPosition(const float& x, const float& y) {
    this->text_RETRY->setPosition(sf::Vector2f(x / 2 - this->text_RETRY->getGlobalBounds().size.x / 2, y * 0.7f));
    this->text_EXIT->setPosition(sf::Vector2f(x / 2 - this->text_EXIT->getGlobalBounds().size.x / 2, y * 0.85f));
}


/**
 * @brief Draws the defeat menu.
 */
void DefeatMenu::render() {
    this->window->clear();
    this->window->draw(*this->gameOverText_TOP);
    this->window->draw(*this->gameOverText_BOTTOM);
    this->window->draw(*this->text_RETRY);
    this->window->draw(*this->text_EXIT);
    this->window->draw(*this->icon);
    this->window->draw(*this->finalTime);
    this->window->display();
}


/**
 * @brief Updates the selected option.
 */
void DefeatMenu::updateSelection() {
    if (selected == RETRY) {
        this->icon->setPosition({this->text_RETRY->getPosition().x - this->iconDistanceToText, this->text_RETRY->getPosition().y + this->text_RETRY->getGlobalBounds().size.y / 2 - this->icon->getGlobalBounds().size.y / 2});
    } else if (selected == EXIT) {
        this->icon->setPosition({this->text_EXIT->getPosition().x - this->iconDistanceToText, this->text_EXIT->getPosition().y + this->text_EXIT->getGlobalBounds().size.y / 2 - this->icon->getGlobalBounds().size.y / 2});
    }
}


/**
 *  Public Functions
 */


/**
 * @brief Constructor of DefeatMenu.
 */
DefeatMenu::DefeatMenu(std::string dataDir, sf::RenderWindow* window) {
    this->dataDir = dataDir;
    this->window = window;

    this->loadFont(); 
    this->loadTexture();

    this->initVariables();
    this->initGameOverText();
    this->initMenuText();
    this->initIcon();
    this->initFinalTime();

    this->gui = new GUI(this->dataDir, this->window);
}


/**
 * @brief Sets the run time after the player lost the game. 
 */
void DefeatMenu::setTime(const std::string& time) {
    this->finalTime->setString(time);
}


/**
 * @brief The cScreen main loop. Handles all events on the defeat menu. 
 */
int DefeatMenu::Run() {
    this->selected = RETRY;
    this->gui->playGameOverSound();

    while(true) {
         while (const std::optional evnt = window->pollEvent()) {
            // Window closed
            if (evnt->is<sf::Event::Closed>()) {
                return (-1);
            }
            // Key pressed
            if (const auto* keyPressed = evnt->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    // Close Programm (Escape)
                    case sf::Keyboard::Scancode::Escape:
                        return (-1);
                    // Go up (W)
                    case sf::Keyboard::Scancode::W:
                        if(selected == EXIT)
                            selected = RETRY;
                        break;
                    // Go down (S)
                    case sf::Keyboard::Scancode::S:
                        if(selected == RETRY)
                        selected = EXIT;
                        break;
                    // Select (Enter)
                    case sf::Keyboard::Scancode::Enter:
                        if(selected == 0) {
                            // Start Game again
                            this->gui->stopGameOverSound();
                            return (1);
                        } else if(selected == 1) {
                            // Return to Home Screen
                            this->gui->stopGameOverSound();
                            return (0);
                        }
                    default:
                        break;
                }
            }
        }

        // Updates the screen
        this->updateSelection();   
        this->render();
    }

    return (-1);
}

