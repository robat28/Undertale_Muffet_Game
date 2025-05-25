#ifndef _PLAYFIELD_
#define _PLAYFIELD_

#include <SFML/Graphics.hpp>

class Playfield {
    private:

        // Playfield
        sf::RectangleShape playfield;

        // Private Functions
        void initPlayfield();
        void initLevels();

    public:

        // Container of graphical Levels
        std::vector<sf::RectangleShape> levels;

        // Constructor 
        Playfield();

        // Getter
        const float getHeight() const;
        const float getWidth() const;
        const sf::FloatRect getBounds() const;
        const float getBorderThickness() const;

        // Setter
        void setPosition(const float& x, const float& y);
        void setLevelPositions(const float& x, const float& y);

        // Public Functions
        void render(sf::RenderTarget& target);
};

#endif