#pragma once

#include <iostream>
#include "cScreen.hpp"

#include "SFML/Graphics.hpp"

class Menu : public cScreen{
    private:

        std::string dataDir;
        sf::RenderWindow* window;

        sf::Event evnt;
        bool running;
        sf::Font font;
        sf::Text text1;
        sf::Text text2;
        sf::Text text3;
        int selected;

        void initMenu();
        void loadFont();
        void updateTextStyles();


    public:

        Menu(std::string dataDir, sf::RenderWindow *window);

        virtual int Run();

};