#include "ScoresScreen.hpp"


/**
 * Private Functions
 */


/**
 * @brief Initializes all variables of the scores screen.
 */
void ScoresScreen::initVariables() {
    this->charSize = 25;
    this->iconDistanceToText = 65.f; 
    this->rankDistanceToScore = 65.f;
    this->topPosition = this->window->getSize().y * 0.15f;
    this->offsetY = 0.f;
    this->newHighscore = false;
}


/**
 * @brief Initializes the scores of the vector.
 */
void ScoresScreen::initScores() {
    this->createFile();
    this->initScoresFromFile();
    
    for(int i = 1; i < 6; i++) {
        this->highscores[i].setCharacterSize(this->charSize);
        this->highscores[i].setFillColor({128,128,128,255});
        this->highscores[i].setPosition({this->window->getSize().x / 2 - this->highscores[i].getGlobalBounds().size.x / 2, this->topPosition + this->offsetY});
        this->offsetY += this->highscores[i].getGlobalBounds().size.x / 3;
    }
    this->offsetY += this->highscores[1].getGlobalBounds().size.x / 3;
    
    this->seperator = std::make_unique<sf::Text>(this->font);
    this->seperator->setString("---Latest Time:---");
    this->seperator->setCharacterSize(this->charSize);
    this->seperator->setPosition({this->window->getSize().x / 2 - this->seperator->getGlobalBounds().size.x / 2, this->topPosition + this->offsetY});
    this->offsetY += this->highscores[1].getGlobalBounds().size.x / 3;

    // The latest time
    this->highscores[0].setCharacterSize(this->charSize);
    this->highscores[0].setFillColor({128,128,128,255});
    this->highscores[0].setPosition({this->window->getSize().x / 2 - this->highscores[0].getGlobalBounds().size.x / 2, this->topPosition + this->offsetY});
    this->offsetY += this->highscores[1].getGlobalBounds().size.x / 3;
}


/**
 * @brief Initializes the highscore vector with the values of the file.
 */
void ScoresScreen::initScoresFromFile() {
    std::ifstream file("scores.txt");
    std::string line;
    if(file) {
        while(getline(file, line)) {
            sf::Text score(this->font);
            score.setString(line);
            this->highscores.push_back(score);
        }
        file.close();
    } else std::cout << "Unable to open scores.txt";
}


/**
 * @brief Initializes the viusal ranks on the screen.
 */
void ScoresScreen::initRankingText() {
    for (int i = 1; i < 6; i++) {
        sf::Text rank(this->font);
        rank.setString(std::to_string(i) + ".");
        rank.setCharacterSize(this->charSize);
        rank.setPosition({this->highscores[i].getPosition().x - this->rankDistanceToScore, this->highscores[i].getPosition().y});
        this->rankings.push_back(rank);
    }
}


/**
 * @brief Initializes the text for the exit selcetion option.
 */
void ScoresScreen::initExitText() {
    this->text_EXIT = std::make_unique<sf::Text>(this->font);
    this->text_EXIT->setString("EXIT");
    this->text_EXIT->setCharacterSize(20);

    this->text_EXIT->setPosition({this->window->getSize().x / 2 - this->text_EXIT->getGlobalBounds().size.x / 2, this->window->getSize().y * 0.85f});
}


/**
 * @brief Initializes the variables of the selection icon. 
 */
void ScoresScreen::initIcon() {
    this->icon = std::make_unique<sf::Sprite>(this->texture);
    this->icon->scale({0.035f, 0.035f});

    this->icon->setOrigin({this->icon->getGlobalBounds().size.x / 2, this->icon->getGlobalBounds().size.y / 2});
    this->icon->setPosition({this->text_EXIT->getPosition().x - this->iconDistanceToText, this->text_EXIT->getPosition().y - this->icon->getGlobalBounds().size.y / 2 + this->icon->getGlobalBounds().getCenter().y / 2});
}


/**
 * @brief Loads the font of the scores screen text. Returns error message if it can not find the directory.
 */
void ScoresScreen::loadFont() {
    if (!this->font.openFromFile(this->dataDir + "fonts/ingame-hud-font.ttf")) {
        std::cout << "FONT LOADING ERROR::SCORESSCREEN::fonts/ingame-hud-font.ttf" << '\n';
    }
}


/**
 * @brief Loads the selection icon of the scores screen. Returns error message if it can not find the directory.
 */
void ScoresScreen::loadTexture() {
    if (!this->texture.loadFromFile(this->dataDir + "textures/selection_icon.png")) {
        std::cout << "FONT LOADING ERROR::DEFEATMENU::textures/selection_icon.png" << '\n';
    }
}


/**
 * @brief Creating the textfile if the game has been started for the first time.
 */
void ScoresScreen::createFile() {
    const std::string filename = "scores.txt";
    std::ifstream check(filename);

    if(!check) {
        std::ofstream create(filename);
        if (create) {
            for(int i = 0; i < 6; i++) {
                create << "00:00:00\n";
            }
            check.close();
        } else std::cout << "Unable to create scores.txt";
    }
}


/**
 * @brief Updates the scoreboard after a player run.
 */
void ScoresScreen::updateHighscores(const std::string& time) {
    // Add latest time to the screen
    this->highscores[0].setString(time);

    // Check if there is a new highscore
    for(int i = 1; i < 6; i++) {
        if(this->highscores[i].getString() < time) {
            this->newHighscore = true;
            break;
        }
    }

    // Updates vector highscores
    if(this->newHighscore) {
        std::vector<std::string> temp;
        
        // Put the values in new vector 
        temp.push_back(time);
        for(int i = 1; i < 6; i++) {
            temp.push_back(this->highscores[i].getString());
        }
        
        std::sort(temp.begin(), temp.end());
        std::reverse(temp.begin(), temp.end());

        for(int i = 1; i < 6; i++) {
            this->highscores[i].setString(temp[i-1]);
        }    
    }
    
    // Writes new time to file
    std::ofstream file("scores.txt");
    if(file) {  
        for (int i = 0; i < 6; ++i) {
            file << highscores[i].getString().toAnsiString() << "\n";
        }
        file.close();
    } else std::cout << "Unable to overwrite scores.txt";
    
    this->newHighscore = false;
}


/**
 * @brief Draws the screen.
 */
void ScoresScreen::render() {
    this->window->clear();
    for(sf::Text rank: this->rankings) {this->window->draw(rank);}
    for(sf::Text score : this->highscores) {this->window->draw(score);}
    this->window->draw(*this->seperator);
    this->window->draw(*this->text_EXIT);
    this->window->draw(*this->icon);
    this->window->display();
}


/**
 * Public Functions
 */


/**
 * @brief Constructor of the scores screen.
 */
ScoresScreen::ScoresScreen(std::string dataDir, sf::RenderWindow* window) {
    this->dataDir = dataDir;
    this->window = window;

    this->loadFont();
    this->loadTexture();

    this->initVariables();
    this->initScores();
    this->initRankingText();
    this->initExitText();
    this->initIcon();
}


/**
 * @brief The cScreen main loop.
 */
int ScoresScreen::Run() {
    while(true) {
         while (const std::optional evnt = window->pollEvent()) {
            // Window closed
            if (evnt->is<sf::Event::Closed>()) {
                return (-1);
            }
            // Key pressed
            if (const auto* keyPressed = evnt->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    // Go back to the main menu
                    case sf::Keyboard::Scancode::Enter:
                        return (0);
                    default:
                        break;
                }
            }
        }

        // Updates the screen
        this->render();
    }

    return (-1);
}


/**
 * @brief Public setter to get the time of the latest run.
 */
void ScoresScreen::deliverTime(const std::string& time) {
    this->updateHighscores(time);
}