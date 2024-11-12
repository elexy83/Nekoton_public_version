#ifndef HITBOX_COMPONENT_HPP
    #define HITBOX_COMPONENT_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
  

    class Hitbox_component
    {
    
    
        public:
            Hitbox_component(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);
            virtual ~Hitbox_component();

            void update();
            void render(sf::RenderTarget& target);

            bool check_intersect(const sf::FloatRect& f_rect);

        private:

            sf::RectangleShape hitbox;
            sf::Sprite &sprite;
            float offsetX;
            float offsetY;

            
    };
#endif