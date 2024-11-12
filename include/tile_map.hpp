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

            void add_tile();
            void remove_tile();

        private:

            unsigned grid_size_u;
            float grid_size_f;
            unsigned layers;
            std::vector<std::vector<std::vector<Tile *>>> map;
            sf::Vector2u max_size;
    };

#endif