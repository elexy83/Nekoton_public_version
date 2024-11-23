#ifndef TILE_HPP
    #define TILE_HPP
    #include "gui.hpp"

    class Tile
    {
        public:
            Tile();
            Tile(float x, float y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect);
            virtual ~Tile();

            void update();
            void render(sf::RenderTarget& target);

        private:
            
        protected:

            sf::RectangleShape shape;
    };

#endif