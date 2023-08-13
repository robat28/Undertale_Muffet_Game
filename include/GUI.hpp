#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

class GUI {
    private:

        // Animation Variables
        int numFrames;
        int frameLength;
        sf::Time frameDuration;
        sf::IntRect frameRect;
        int currentFrame;

        // Texture of Animation
        sf::Texture spritesheetTexture;
        sf::Sprite sprite;

        // Timer
        sf::Time totalTime;
        
        // Private Functions
        void initAnimationVariables();
        void initSprite();
        void loadSpriteSheetTexture();

    public:

        // Constructor
        GUI();

        // Destructor
        ~GUI();

        // Setter
        void setSpritePosition(const float& x, const float& y);
        void setFrameRect(const int& currentFrame);

        // Public Functions
        void updateSprite(sf::Time& deltaTime);
        void render(sf::RenderTarget& target);
};