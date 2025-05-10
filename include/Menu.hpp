#pragma once

#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>

class Menu : public cScreen{
    private:

        std::string dataDir;
        sf::RenderWindow* window;

        bool running;
        sf::Font font;
        std::unique_ptr<sf::Text> text1;
        std::unique_ptr<sf::Text> text2;
        std::unique_ptr<sf::Text> text3;
        int selected;

        void initMenu();
        void loadFont();
        void updateTextStyles();


    public:

        Menu(std::string dataDir, sf::RenderWindow *window);

        virtual int Run();

};