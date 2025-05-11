# include "GameScreen.hpp"

//
GameScreen::GameScreen(std::string dataDir, sf::RenderWindow *window) {
    this->dataDir = dataDir;
    this->window = window;
}

int GameScreen::Run() {

    this->game = std::make_unique<Game>(this->dataDir, this->window);
    return game->Run();
}