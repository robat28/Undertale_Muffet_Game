#include "Menu.hpp"

/**
 *  Private Functions
 */

void Menu::initMenu() {
    this->loadFont(); 

    this->text1.setString("Play");
    this->text1.setFont(font);
    this->text1.setCharacterSize(40);
    this->text1.setOrigin(this->text1.getGlobalBounds().getSize().x / 2, this->text1.getGlobalBounds().getSize().y / 2);
    this->text1.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.4f));

    this->text2.setString("Quit");
    this->text2.setFont(font);
    this->text2.setCharacterSize(40);
    this->text2.setOrigin(this->text2.getGlobalBounds().getSize().x / 2, this->text2.getGlobalBounds().getSize().y / 2);
    this->text2.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.6f));

    this->text3.setString("Scores");
    this->text3.setFont(font);
    this->text3.setCharacterSize(20);
    this->text3.setOrigin(this->text3.getGlobalBounds().getSize().x / 2, this->text3.getGlobalBounds().getSize().y / 2);
    this->text3.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.9f));

    this->selected = 0;
}

void Menu::loadFont() {
    if (!this->font.loadFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
        std::cout << "FONT LOADING ERROR::GUI::fonts/ingame-hud-font.ttf" << '\n';
    }
}

void Menu::updateTextStyles() {
    this->text1.setStyle(sf::Text::Regular);
    this->text2.setStyle(sf::Text::Regular);
    this->text3.setStyle(sf::Text::Regular);

    if (selected == 0) {
        this->text1.setStyle(sf::Text::Underlined);
    } else if (selected == 1) {
        this->text2.setStyle(sf::Text::Underlined);
    } else if (selected == 2) {
        this->text3.setStyle(sf::Text::Underlined);
    }
}

/**
 *  Public Functions
 */

Menu::Menu(std::string dataDir, sf::RenderWindow *window) {
    this->dataDir = dataDir;
    this->window = window;
}

int Menu::Run() {
    this->running = true;
    this->initMenu();

    while (running) {
        // Verifying events
        while (this->window->pollEvent(evnt)) {
            // Window closed
            if (evnt.type == sf::Event::Closed) {
                return (-1);
            }
            // Key pressed
            if (evnt.type == sf::Event::KeyPressed) {
                switch (evnt.key.code) {
                    case sf::Keyboard::W:
                        if(selected > 0)
                            selected -= 1;
                        break;
                    case sf::Keyboard::S:
                        if(selected < 2)
                        selected += 1;
                        break;
                    case sf::Keyboard::Return:
                        if(selected == 0) {
                            // Start Game
                            return (1);
                        } else if(selected == 1) {
                            // Quit
                            return (-1);
                        } else if(selected == 2) {
                            // Scores TODO
                            //return (2);
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        this->updateTextStyles();
   
        // Clearing screen
        this->window->clear();
        // Drawing
        this->window->draw(text1);
        this->window->draw(text2);
        this->window->draw(text3);

        this->window->display();
    }

    // Never reaching this point normally, but just in case, exit the
    // application
    return (-1);
}