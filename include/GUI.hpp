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
        sf::Texture spritesheetTexture;
        sf::Sprite sprite;

        int numFrames;
        sf::Time frameDuration;

        int frameWidth;
        int frameHeight;

        sf::IntRect frameRect;

        sf::Time totalTime;
        int currentFrame;

        void initVariables();
        void initSprite();

        void loadSpriteSheetTexture();

    public:

        GUI();
        ~GUI();

        void setFrameRect(const int currentFrame);
        void setSpritePosition(const float x, const float y);

        void update(sf::Time deltaTime);
        void render(sf::RenderTarget* target);
};