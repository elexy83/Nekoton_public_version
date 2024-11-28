#ifndef TILE_MAP_HPP
    #define TILE_MAP_HPP
    
    #include "tile.hpp"
    #include "entity.hpp"

    class Tile_map
    {
        public: 

            Tile_map(float grid_size_f, unsigned width, unsigned height, std::string texture_file);
            virtual ~Tile_map();

            void update();
            void render(sf::RenderTarget& target, entity* entity = NULL);

            void add_tile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool &collision, const short &type);
            void remove_tile(const unsigned x, const unsigned y, const unsigned z);

            const sf::Texture* get_tile_sheet() const ;

            void save_to_file(const std::string file_name);
            void load_from_file(const std::string file_name);

            void update_collision(entity* entity);

        private:

            void clear();
            unsigned grid_size_u;
            float grid_size_f;
            unsigned layers;
            std::string texture_file;
            std::vector<std::vector<std::vector<Tile *>>> map;
            sf::Vector2u max_size_world_grid;
            sf::Vector2f max_size_world;
            sf::Texture tile_sheet;
            sf::RectangleShape collision_box;
    };

#endif