#ifndef _MAIN_
#define _MAIN_

#include "Menu.hpp"
#include "GameScreen.hpp"
#include "DefeatMenu.hpp"
#include "ScoresScreen.hpp"


int main(int argc, char** argv) {
    
    /**
     *  @brief Find the directory of files.
     */
    std::string dataDir = argv[0];
    dataDir.erase(dataDir.rfind("/"));
    dataDir.append("/../");
    

    /**
     *  @brief Initializes and sets all Properties of the window.
     *  @remark FramerateLimit is at 60 Frames, so the game appears same on all devices.
     */
    sf::VideoMode vMode = sf::VideoMode({1000, 750});
    std::string title = "Muffet Game";

    sf::RenderWindow* window = new sf::RenderWindow(vMode, title, sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);


    /**
     * @brief Loads the image and sets the image as an icon for the game.
     */
    auto image = sf::Image{};
    if(!image.loadFromFile(dataDir + "/textures/game_icon.png")) {
        std::cout << "IMAGE LOADING ERROR::MAIN::game_icon.png" << '\n';
    }
    window->setIcon({image.getSize().x, image.getSize().y}, image.getPixelsPtr());


    /**
     * @brief Applications variables and screen preparation.
     */
    Menu menu(dataDir, window);
    GameScreen gamescreen(dataDir, window);
    ScoresScreen scorescreen(dataDir, window);
    DefeatMenu defMenu(dataDir, window);
    std::vector<cScreen*> screens;
    int screen = 0;
    std::string currentTime = "-";

    screens.push_back(&menu);
    screens.push_back(&gamescreen);
    screens.push_back(&scorescreen);
    screens.push_back(&defMenu);

    // Runs application until it returns -1.
    while(screen >= 0) {
        // Delivers the time of the previous run to the defeat menu and to the scores screen.
        if(screen == 3) {
            currentTime = gamescreen.getTime();
            defMenu.setTime(currentTime);
            scorescreen.deliverTime(currentTime);
        }
        screen = screens[screen]->Run();
    }

    return 0;
}

#endif