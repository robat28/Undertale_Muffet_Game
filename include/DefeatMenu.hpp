#pragma once

#include "cScreen.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

#include "Game.hpp"
#include "GUI.hpp"

class DefeatMenu : public cScreen {
    private:
        std::string dataDir;
        bool running;
        sf::RenderWindow* window;
        std::unique_ptr<sf::Text> text1;
        std::unique_ptr<sf::Text> text2;
        sf::Font font;
        int selected;
        GUI* gui;

        // Game Over Screen
        std::unique_ptr<sf::Text> gameOverTextTop;
        std::unique_ptr<sf::Text> gameOverTextBottom;

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