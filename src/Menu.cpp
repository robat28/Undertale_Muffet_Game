#include "Menu.hpp"

/**
 *  Private Functions
 */


/**
 * @brief Initializes all variables of the menu.
 */
void Menu::initVariables() {
    this->textSize = 40;
    this->selected = PLAY;
    this->iconDistanceToText = 65.f;
}


/**
 * @brief Initializes the variables of the menu text.
 */
void Menu::initMenu() {
    this->text_PLAY = std::make_unique<sf::Text>(this->font);
    this->text_PLAY->setString("Play");
    this->text_PLAY->setCharacterSize(this->textSize);
    this->text_PLAY->setPosition(sf::Vector2f(this->window->getSize().x / 2 - this->text_PLAY->getGlobalBounds().size.x / 2, this->window->getSize().y * 0.4f));

    this->text_QUIT = std::make_unique<sf::Text>(this->font);
    this->text_QUIT->setString("Quit");
    this->text_QUIT->setCharacterSize(this->textSize);
    this->text_QUIT->setPosition(sf::Vector2f(this->window->getSize().x / 2 - this->text_QUIT->getGlobalBounds().size.x / 2, this->window->getSize().y * 0.6f));

    this->text_SCORES = std::make_unique<sf::Text>(this->font);
    this->text_SCORES->setString("Scores");
    this->text_SCORES->setCharacterSize(this->textSize * 0.75f);
    this->text_SCORES->setPosition(sf::Vector2f(this->window->getSize().x / 2 - this->text_SCORES->getGlobalBounds().size.x / 2, this->window->getSize().y * 0.9f));
}


/**
 * @brief Initializes the variables of the selection icon.
 */
void Menu::initIcon() {
    this->icon = std::make_unique<sf::Sprite>(this->texture);
    this->icon->scale({0.035f, 0.035f});

    this->icon->setOrigin({this->icon->getGlobalBounds().size.x / 2, this->icon->getGlobalBounds().size.y / 2});
    this->icon->setPosition({this->text_PLAY->getPosition().x - this->text_PLAY->getGlobalBounds().size.x / 2, this->text_PLAY->getPosition().y - this->icon->getGlobalBounds().size.y / 2});
}


/**
 * @brief Loads the font of the menu text. Returns error message if it can not find the directory.
 */
void Menu::loadFont() {
    if (!this->font.openFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
        std::cout << "FONT LOADING ERROR::GUI::fonts/ingame-hud-font.ttf" << '\n';
    }
}


/**
 * @brief Loads the selection icon of the menu. Returns error message if it can not find the directory.
 */
void Menu::loadTexture() {
    if (!this->texture.loadFromFile(this->dataDir + "textures/selection_icon.png")) {
        std::cout << "FONT LOADING ERROR::GUI::textures/selection_icon.png" << '\n';
    }
}


/**
 * @brief Changes the selected option of the menu.
 */
void Menu::updateSelection() {
    if (selected == PLAY) {
        this->icon->setPosition({this->text_PLAY->getPosition().x - this->iconDistanceToText, this->text_PLAY->getPosition().y + this->text_PLAY->getGlobalBounds().size.y / 2 - this->icon->getGlobalBounds().size.y / 2});
    } else if (selected == QUIT) {
        this->icon->setPosition({this->text_QUIT->getPosition().x - this->iconDistanceToText, this->text_QUIT->getPosition().y + this->text_QUIT->getGlobalBounds().size.y / 2 - this->icon->getGlobalBounds().size.y / 2});
    } else if (selected == SCORES) {
        this->icon->setPosition({this->text_SCORES->getPosition().x - this->iconDistanceToText, this->text_SCORES->getPosition().y + this->text_SCORES->getGlobalBounds().size.y / 2 - this->icon->getGlobalBounds().size.y / 2});
    }
}


/**
 * @brief Draws the objects on the screen.
 */
void Menu::render() {
    // Clearing screen
    this->window->clear();
    // Drawing
    this->window->draw(*this->text_PLAY);
    this->window->draw(*this->text_QUIT);
    this->window->draw(*this->text_SCORES);
    this->window->draw(*this->icon);

    this->window->display();
}


/**
 *  Public Functions
 */


/**
 * @brief Constructor of Menu.
 */
Menu::Menu(std::string dataDir, sf::RenderWindow *window) {
    this->dataDir = dataDir;
    this->window = window;

    this->loadFont(); 
    this->loadTexture();

    this->initVariables();
    this->initMenu();
    this->initIcon();
}


/**
 * @brief The cScreen main loop. Handles all events on the defeat menu. 
 */
int Menu::Run() {
    this->selected = PLAY;

    while (true) {
        // Verifying events
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
                    case sf::Keyboard::Scancode::W:
                        if(this->selected == QUIT)
                            this->selected =  PLAY;
                        else if(this->selected == SCORES) {
                            this->selected =  QUIT;
                        } 
                        break;
                    case sf::Keyboard::Scancode::S:
                        if(this->selected == PLAY)
                            this->selected =  QUIT;
                        else if(this->selected == QUIT) {
                            this->selected =  SCORES;
                        } 
                        break;
                    case sf::Keyboard::Scancode::Enter:
                        if(this->selected == 0) {
                            // Start Game
                            return (1);
                        } else if(this->selected == 1) {
                            // Quit
                            return (-1);
                        } else if(this->selected == 2) {
                            // Scores TODO
                            //return (2);
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        this->updateSelection();
        this->render();
    }

    // Never reaching this point normally, but just in case, exit the application
    return (-1);
}