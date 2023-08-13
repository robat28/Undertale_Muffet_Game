#pragma once

#include "GUI.hpp"

class Playfield {
    private:

        sf::RectangleShape playfield;

        // Private Functions
        void initPlayfield();
        void initLevels();

    public:

        // Container of graphical Levels
        std::vector<sf::RectangleShape> levels;

        // Constructor 
        Playfield();

        // Destructor
        ~Playfield();

        // Getter
        const sf::FloatRect getBounds() const;
        const float getHeight() const;
        const float getWidth() const;

        // Setter
        void setPosition(const float& x, const float& y);
        void setLevelPositions(const float& x, const float& y);

        // Public Functions
        void render(sf::RenderTarget* target);
};