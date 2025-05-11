#include "DefeatMenu.hpp"

/**
 *  Private Functions
 */

void DefeatMenu::initGameOverText() {
    this->loadFont(); 

    this->gameOverTextTop = std::make_unique<sf::Text>(this->font);
    this->gameOverTextTop->setString("Game");
    this->gameOverTextTop->setCharacterSize(120);
    this->gameOverTextTop->setOrigin({this->gameOverTextTop->getLocalBounds().size.x / 2, this->gameOverTextTop->getLocalBounds().size.y / 2});

    this->gameOverTextBottom = std::make_unique<sf::Text>(this->font);
    this->gameOverTextBottom->setString("Over");
    this->gameOverTextBottom->setCharacterSize(120);
    this->gameOverTextBottom->setOrigin({this->gameOverTextBottom->getLocalBounds().size.x / 2, this->gameOverTextBottom->getLocalBounds().size.y / 2});

    this->selected = 0;
}

void DefeatMenu::loadFont() {
    if (!this->font.openFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
        std::cout << "FONT LOADING ERROR::GUI::fonts/ingame-hud-font.ttf" << '\n';
    }
}

void DefeatMenu::setGameOverVisibility(const int& visibility) {
    if(visibility*2 < 255) {
        this->gameOverTextTop->setFillColor(sf::Color(255, 255, 255, visibility * 2));
        this->gameOverTextBottom->setFillColor(sf::Color(255, 255, 255, visibility * 2));
    }
}

void DefeatMenu::setGameOverTextPosition(const int& x, const int& y) {
    this->gameOverTextTop->setPosition({static_cast<float>(x), static_cast<float>(y)});
    this->gameOverTextBottom->setPosition({static_cast<float>(x) , y + this->gameOverTextTop->getGlobalBounds().size.y + 10.f});
}

void DefeatMenu::render(sf::RenderTarget& target) {
    target.draw(*this->gameOverTextTop);
    target.draw(*this->gameOverTextBottom);
    target.draw(*this->text1);
    target.draw(*this->text2);
}

void DefeatMenu::updateTextStyles() {
    this->text1->setStyle(sf::Text::Regular);
    this->text2->setStyle(sf::Text::Regular);

    if (selected == 0) {
        this->text1->setStyle(sf::Text::Underlined);
    } else if (selected == 1) {
        this->text2->setStyle(sf::Text::Underlined);
    }
}

/**
 *  Public Functions
 */

DefeatMenu::DefeatMenu(std::string dataDir, sf::RenderWindow* window) {
    this->dataDir = dataDir;
    this->window = window;

    this->gui = new GUI(this->dataDir);
}

int DefeatMenu::Run() {
    this->window->clear();
    this->window->display();
    
    this->running = true;

    this->initGameOverText();
    this->setGameOverTextPosition(this->window->getSize().x / 2, this->window->getSize().y / 5);
    this->gui->playGameOverSound();

    this->text1 = std::make_unique<sf::Text>(this->font);
    this->text1->setString("RETRY");
    this->text1->setCharacterSize(30);
    this->text1->setOrigin({this->text1->getGlobalBounds().size.x / 2, this->text1->getGlobalBounds().size.y / 2});
    this->text1->setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.7f));

    this->text2 = std::make_unique<sf::Text>(this->font);
    this->text2->setString("EXIT");
    this->text2->setCharacterSize(30);
    this->text2->setOrigin({this->text2->getGlobalBounds().size.x / 2, this->text2->getGlobalBounds().size.y / 2});
    this->text2->setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.85f));

    while(this->running) {
         while (const std::optional evnt = window->pollEvent()) {
            // Window closed
            if (evnt->is<sf::Event::Closed>()) {
                return (-1);
            }
            // Key pressed
            if (const auto* keyPressed = evnt->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Escape:
                        return (-1);
                    case sf::Keyboard::Scancode::W:
                        if(selected > 0)
                            selected -= 1;
                        break;
                    case sf::Keyboard::Scancode::S:
                        if(selected < 1)
                        selected += 1;
                        break;
                    case sf::Keyboard::Scancode::Enter:
                        if(selected == 0) {
                            // Start Game again
                            // TODO Restart game
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

        this->updateTextStyles();
   
        this->window->clear();

        this->render(*this->window);

        this->window->display();
    }

    return (-1);
}

