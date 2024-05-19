#include "Menu.hpp"
#include "Game.hpp"
#include "DefeatMenu.hpp"

int main(int argc, char** argv) {
    
    // Find the directory of files
    std::string dataDir = argv[0];
    dataDir.erase(dataDir.rfind("/"));
    dataDir.append("/../");
    

    /**
     *  @brief Initializes and sets all Properties of the window.
     *  @remark FramerateLimit is at 60 Frames, so the game appears same on most devices.
     */
    sf::VideoMode vMode = sf::VideoMode(1000, 750);
    std::string title = "Undertale Muffet Minigame";

    sf::RenderWindow* window = new sf::RenderWindow(vMode, title, sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
    //this->window->setIcon()

    Menu menu(dataDir, window);
    Game game(dataDir, window);
    DefeatMenu defMenu(dataDir, window);
    
    // Applications variables and screen preparation
    std::vector<cScreen*> screens;
    int screen = 0;

    screens.push_back(&menu);
    screens.push_back(&game);
    screens.push_back(&defMenu);


    while(screen >= 0) {
        screen = screens[screen]->Run();
    }

    return 0;
}
