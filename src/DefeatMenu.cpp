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

    this->text1.setString("Try Again");
    this->text1.setFont(font);
    this->text1.setCharacterSize(30);
    this->text1.setOrigin(this->text1.getGlobalBounds().getSize().x / 2, this->text1.getGlobalBounds().getSize().y / 2);
    this->text1.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.7f));

    this->text2.setString("Quit");
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
                    default:
                        break;
                }
            }
        }
   
        this->window->clear();

        this->render(*this->window);

        this->window->display();
    }

    


    return (-1);
}

