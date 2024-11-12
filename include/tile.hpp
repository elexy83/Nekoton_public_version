#ifndef TILE_HPP
    #define TILE_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include "gui.hpp"

    class Tile
    {
        public:
            Tile();
            Tile(float x, float y, float grid_size_f);
            virtual ~Tile();

            void update();
            void render(sf::RenderTarget& target);

        private:
            
        protected:

            sf::RectangleShape shape;
    };

#endif