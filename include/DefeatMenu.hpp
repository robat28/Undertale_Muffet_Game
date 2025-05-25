#ifndef _DEFEATMENU_
#define _DEFEATMENU_

#include "cScreen.hpp"
#include "GUI.hpp"


enum SELECTED_DF {RETRY, EXIT};

class DefeatMenu : public cScreen {
    private:
    
        std::string dataDir;

        // Window and Display
        sf::RenderWindow* window;

        // Font and Text
        sf::Font font;
        std::unique_ptr<sf::Text> text_RETRY;
        std::unique_ptr<sf::Text> text_EXIT;
        SELECTED_DF selected;

        // Icon
        sf::Texture texture;
        std::unique_ptr<sf::Sprite> icon;
        float iconDistanceToText;
        
        // To play Game Over sound
        GUI* gui;

        // Game Over Screen
        std::unique_ptr<sf::Text> gameOverText_TOP;
        std::unique_ptr<sf::Text> gameOverText_BOTTOM;

        // Private Functions
        void initVariables();
        void initGameOverText();
        void initMenuText();
        void initIcon();
        void loadFont();
        void loadTexture();

        // Helping methods
        void setGameOverTextPosition(const float& x, const float& y);
        void setMenuTextPosition(const float& x, const float& y);

        // Draw functions
        void render();
        void updateSelection();

    public:

        // Constructor
        DefeatMenu(std::string dataDir, sf::RenderWindow* window);

        // cScreen function
        virtual int Run();
};

#endif