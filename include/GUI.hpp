#ifndef _GUI_
#define _GUI_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>


class GUI {
    private:
        std::string dataDir;

        // Window and Display
        sf::RenderWindow* window;

        // Time Variables
        sf::Time totalTime;
        sf::Time frameDuration;
        sf::Time elapsedTime;
        std::unique_ptr<sf::Text> time;

        // Animation Variables
        sf::IntRect frameRect;
        int numFrames;
        int frameLength;
        int currentFrame;

        // Animation texture
        sf::Texture spritesheetTexture;
        std::unique_ptr<sf::Sprite> sprite;

        // HP-Bar Variables
        sf::Font font;
        std::unique_ptr<sf::Text> healthText;
        std::unique_ptr<sf::Text> playerName;
        sf::RectangleShape healthBarRemaining;
        sf::RectangleShape healthBarLost;

        // Sounds
        sf::Music ingameOST;
        sf::SoundBuffer hitBuffer; 
        sf::SoundBuffer defeatBuffer;
        sf::SoundBuffer gameOverBuffer;
        std::unique_ptr<sf::Sound> hitSound;
        std::unique_ptr<sf::Sound> defeatSound;
        std::unique_ptr<sf::Sound> gameOverTheme;
        
        // Private Functions
        void initVariables();
        void initSprite();
        void initSounds();
        void initHealthText();
        void initHealthBar();
        void initPlayerName();
        void initTimer();
        void loadSpriteSheetTexture();
        void loadSounds();
        void loadMusic();
        void loadFont();

    public:

        // Constructor
        GUI(std::string dataDir, sf::RenderWindow* window);

        // Getter
        const float getSpriteWidth() const;
        const float getSpriteHeight() const;
        const float getPlayerNameSizeX() const;
        const float getPlayerNameSizeY() const;
        const float getTimerSizeX() const;
        const float getTimerSizeY() const;
        const std::string getFinalTimer() const;

        // Setter
        void setSpritePosition(const float& x, const float& y);
        void setHPBarPosition(const float& x, const float& y);
        void setPlayerNamePosition(const float& x, const float& y);
        void setTimerPosition(const float& x, const float& y);
        void setFrameRect(const int& currentFrame);
        void setHpString(const int& currentHp);
        void setSizeHPRemaining(sf::Vector2f size);

        // Public Functions
        void playMusic();
        void stopMusic();
        void playGameOverSound();
        void stopGameOverSound();
        void playHitSound();
        void playDefeatSound();
        void updateVisualTimer(sf::Clock& clock);

        void updateSprite(sf::Time& deltaTime);
        void render();
};

#endif