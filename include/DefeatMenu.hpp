#pragma once

#include "cScreen.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "GUI.hpp"

class DefeatMenu : public cScreen {
    private:
        std::string dataDir;
        bool running;
        sf::Event evnt;
        sf::RenderWindow* window;
        sf::Text text1;
        sf::Text text2;
        sf::Font font;
        int selected;

        // Game Over Screen
        sf::Text gameOverTextTop;
        sf::Text gameOverTextBottom;

        void initGameOverText();
        void loadFont();

        void setGameOverVisibility(const int& visibility);
        void setGameOverTextPosition(const int& x, const int& y);

        void render(sf::RenderTarget& window);

        void updateTextStyles();


    public:
        DefeatMenu(std::string dataDir, sf::RenderWindow* window);

        virtual int Run();
};