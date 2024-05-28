#include "DefeatMenu.hpp"

/**
 *  Private Functions
 */

void DefeatMenu::initGameOverText() {
    this->gameOverTextTop.setFont(this->font);
    this->gameOverTextTop.setString("Game");
    this->gameOverTextTop.setCharacterSize(120);
    this->gameOverTextTop.setOrigin(this->gameOverTextTop.getLocalBounds().width / 2, this->gameOverTextTop.getLocalBounds().height / 2);

    this->gameOverTextBottom.setFont(this->font);
    this->gameOverTextBottom.setString("Over");
    this->gameOverTextBottom.setCharacterSize(120);
    this->gameOverTextBottom.setOrigin(this->gameOverTextBottom.getLocalBounds().width / 2, this->gameOverTextBottom.getLocalBounds().height / 2);

    this->selected = 0;
}

void DefeatMenu::loadFont() {
    if (!this->font.loadFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
        std::cout << "FONT LOADING ERROR::GUI::fonts/ingame-hud-font.ttf" << '\n';
    }
}

void DefeatMenu::setGameOverVisibility(const int& visibility) {
    if(visibility*2 < 255) {
        this->gameOverTextTop.setFillColor(sf::Color(255, 255, 255, visibility * 2));
        this->gameOverTextBottom.setFillColor(sf::Color(255, 255, 255, visibility * 2));
    }
}

void DefeatMenu::setGameOverTextPosition(const int& x, const int& y) {
    this->gameOverTextTop.setPosition(x, y);
    this->gameOverTextBottom.setPosition(x , y + this->gameOverTextTop.getGlobalBounds().height + 10.f);
}

void DefeatMenu::render(sf::RenderTarget& target) {
    target.draw(this->gameOverTextTop);
    target.draw(this->gameOverTextBottom);
    target.draw(this->text1);
    target.draw(this->text2);
}

void DefeatMenu::updateTextStyles() {
    this->text1.setStyle(sf::Text::Regular);
    this->text2.setStyle(sf::Text::Regular);

    if (selected == 0) {
        this->text1.setStyle(sf::Text::Underlined);
    } else if (selected == 1) {
        this->text2.setStyle(sf::Text::Underlined);
    }
}

/**
 *  Public Functions
 */

DefeatMenu::DefeatMenu(std::string dataDir, sf::RenderWindow* window) {
    this->dataDir = dataDir;
    this->window = window;
}

int DefeatMenu::Run() {
    this->running = true;

    this->loadFont(); 
    this->initGameOverText();
    this->setGameOverTextPosition(this->window->getSize().x / 2, this->window->getSize().y / 5);

    this->text1.setString("RETRY");
    this->text1.setFont(font);
    this->text1.setCharacterSize(30);
    this->text1.setOrigin(this->text1.getGlobalBounds().getSize().x / 2, this->text1.getGlobalBounds().getSize().y / 2);
    this->text1.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.7f));

    this->text2.setString("EXIT");
    this->text2.setFont(font);
    this->text2.setCharacterSize(30);
    this->text2.setOrigin(this->text2.getGlobalBounds().getSize().x / 2, this->text2.getGlobalBounds().getSize().y / 2);
    this->text2.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.85f));

    while(this->running) {
         while (this->window->pollEvent(evnt)) {
            // Window closed
            if (evnt.type == sf::Event::Closed) {
                return (-1);
            }
            // Key pressed
            if (evnt.type == sf::Event::KeyPressed) {
                switch (evnt.key.code) {
                    case sf::Keyboard::Escape:
                        return (-1);
                    case sf::Keyboard::W:
                        if(selected > 0)
                            selected -= 1;
                        break;
                    case sf::Keyboard::S:
                        if(selected < 1)
                        selected += 1;
                        break;
                    case sf::Keyboard::Return:
                        if(selected == 0) {
                            // Start Game again
                            // TODO Restart game
                            return (1);
                        } else if(selected == 1) {
                            // Return to Home Screen
                            // TODO Restart Game
                            return (0);
                        }
                    default:
                        break;
                }
            }
        }

        this->updateTextStyles();
   
        this->window->clear();

        this->render(*this->window);

        this->window->display();
    }

    return (-1);
}

