#ifndef TILE_MAP_HPP
    #define TILE_MAP_HPP
    
    #include "tile.hpp"
    #include "entity.hpp"

    class Tile_map
    {
        public: 

            Tile_map(float grid_size_f, int width, int height, std::string texture_file);
            virtual ~Tile_map();

            void update();
            void render(sf::RenderTarget& target, entity* entity = NULL);

            void add_tile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool &collision, const short &type);
            void remove_tile(const int x, const int y, const int z);

            const sf::Texture* get_tile_sheet() const ;

            void save_to_file(const std::string file_name);
            void load_from_file(const std::string file_name);

            void update_collision(entity* entity, const float &dt);

        private:

            void clear();
            int grid_size_i;
            float grid_size_f;
            int layers;
            std::string texture_file;
            std::vector<std::vector<std::vector<Tile *>>> map;
            sf::Vector2i max_size_world_grid;
            sf::Vector2f max_size_world;
            sf::Texture tile_sheet;
            sf::RectangleShape collision_box;
            int from_x;
            int to_x;
            int from_y;
            int to_y;
            int layer;
    };

#endif