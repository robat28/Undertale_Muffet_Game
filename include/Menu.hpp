#ifndef _MENU_
#define _MENU_

#include "cScreen.hpp"
#include <iostream>

enum SELECTED {PLAY, QUIT, SCORES};

class Menu : public cScreen{
    private:
    
        std::string dataDir;

        // Window
        sf::RenderWindow* window;

        // Font and Text
        sf::Font font;
        std::unique_ptr<sf::Text> text_PLAY;
        std::unique_ptr<sf::Text> text_QUIT;
        std::unique_ptr<sf::Text> text_SCORES;
        SELECTED selected;
        int textSize;

        // Icon
        sf::Texture texture;
        std::unique_ptr<sf::Sprite> icon;
        float iconDistanceToText;

        // Private Functions
        void initVariables();
        void initMenu();
        void initIcon();
        void loadFont();
        void loadTexture();
        void updateSelection();
        void render();

    public:

        // Constructor
        Menu(std::string dataDir, sf::RenderWindow *window);

        // cScreen function
        virtual int Run();
};

# endif