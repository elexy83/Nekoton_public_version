#ifndef TILE_MAP_HPP
    #define TILE_MAP_HPP
    
    #include "tile.hpp"

    class Tile_map
    {
        public: 

            Tile_map(float grid_size_f, unsigned width, unsigned height);
            virtual ~Tile_map();

            void update();
            void render(sf::RenderTarget& target);

            void add_tile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
            void remove_tile(const unsigned x, const unsigned y, const unsigned z);

            const sf::Texture* get_tile_sheet() const ;

        private:

            unsigned grid_size_u;
            float grid_size_f;
            unsigned layers;
            std::vector<std::vector<std::vector<Tile *>>> map;
            sf::Vector2u max_size;
            sf::Texture tile_sheet;
    };

#endif