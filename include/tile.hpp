#ifndef TILE_HPP
    #define TILE_HPP
    #include "gui.hpp"


    enum Tile_type
    {
        DEFFAULT = 0,
        DAMAGING,
        DOODAD
    };

    class Tile
    {
        public:
            Tile();
            Tile(int grid_x, int grid_y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collision = false, short type = Tile_type::DEFFAULT);
            virtual ~Tile();

            void update();
            void render(sf::RenderTarget& target);

            const std::string get_as_string() const;
            const sf::Vector2f& get_position() const;
            const bool intersect(const sf::FloatRect bounds) const;
            const bool &get_collision() const;
            const sf::FloatRect get_global_bounds() const;
            //accessors
            const short &get_type() const;

        private:
            
        protected:

            sf::RectangleShape shape;
            short type;
            bool collision;
    };

#endif