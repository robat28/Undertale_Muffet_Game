#pragma once

#include "Player.hpp"
#include "Playfield.hpp"

class Game {    
    private:

        // Window and Display
        sf::RenderWindow* window;
        sf::Event evnt;
        sf::VideoMode vMode;

        // Render objects
        GUI* gui;
        Playfield* playfield;
        Player* player;

        // Update Time 
        sf::Clock clock;
        sf::Time deltaTime;

        // Private Variables
        float playfieldCenterX;
        float playfieldCenterY;
        float playfieldPosX;
        float playfieldPosY;

        float buttonCooldown;
        float buttonCooldownMax;

        // Private Functions
        void initVariables();
        void initWindow();
        void initPlayfield();
        void initAnimation();
        void initPlayer();

    public:

        // Constructor
        Game();

        // Destructor
        ~Game();

        const bool running() const;
        const bool canPressButton();

        void pollEvents();

        // Update Functions
        void update();
        void updateInput();
        void updateCollisonPlayfield();
        void updateButtonCooldown();
        void updateDeltaTime();

        void render();
};