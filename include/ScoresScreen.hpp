#ifndef _SCORESSCREEN_
#define _SCORESSCREEN_

#include "cScreen.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


class ScoresScreen : public cScreen {
    private:

        std::string dataDir;

        // Window and Display
        sf::RenderWindow* window;

        // Text
        sf::Font font;
        std::unique_ptr<sf::Text> text_EXIT;
        std::unique_ptr<sf::Text> seperator;
        float iconDistanceToText;
        float topPosition;
        float offsetY;

        // Icon
        sf::Texture texture;
        std::unique_ptr<sf::Sprite> icon;

        // Highscores
        std::vector<sf::Text> highscores;
        bool newHighscore;

        // Private Functions
        void initVariables();
        void initScores();
        void initScoresFromFile();
        void initLatestTime();
        void initExitText();
        void initIcon();
        void loadFont();
        void loadTexture();
        void createFile();
        void updateHighscores(const std::string& time);

        // Draw Function
        void render();

    public:

        // Constructor
        ScoresScreen(std::string dataDir, sf::RenderWindow* window);
        
        // cScreen function
        virtual int Run();

        // Setter
        void deliverTime(const std::string& time);
};

#endif