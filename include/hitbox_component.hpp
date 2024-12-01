#ifndef HITBOX_COMPONENT_HPP
    #define HITBOX_COMPONENT_HPP
    
  

    class Hitbox_component
    {
    
    
        public:
            Hitbox_component(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);
            virtual ~Hitbox_component();

            void update();
            void render(sf::RenderTarget& target);

            bool intersect(const sf::FloatRect& f_rect);

            const sf::Vector2f &get_position() const;
            virtual const sf::FloatRect get_global_bounds() const;
            const sf::FloatRect& get_next_position(const sf::Vector2f& velocity);

            void set_position(sf::Vector2f& position);
            void set_position(const float x, const float y);

        private:

            sf::RectangleShape hitbox;
            sf::FloatRect next_position;
            sf::Sprite &sprite;
            float offsetX;
            float offsetY;

            
    };
#endif