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
        std::string dataDir;

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


        // Sounds
        sf::SoundBuffer hitBuffer;
        sf::Sound hitSound;
        sf::Music music;
        
        // Private Functions
        void initAnimationVariables();

        void initSprite();
        void loadSpriteSheetTexture();

        void initSounds();
        void loadSounds();
        void loadMusic();

    public:

        // Constructor
        GUI(std::string dataDir);

        // Destructor
        ~GUI();

        // Getter
        const float getSpriteWidth() const;
        const float getSpriteHeight() const;
        sf::Sound getHitSound();

        // Setter
        void setSpritePosition(const float& x, const float& y);
        void setNewSpritePosition(const float& x, const float& y);
        void setFrameRect(const int& currentFrame);

        // Public Functions
        void playHitSound();
        void playMusic();
        void updateSprite(sf::Time& deltaTime);
        void render(sf::RenderTarget& target);
};
