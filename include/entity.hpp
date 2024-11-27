#ifndef ENTITY_HPP
    #define ENTITY_HPP
    #include "movement_component.hpp"
    #include "animation_component.hpp"
    #include "hitbox_component.hpp"

    class entity
    {
        public:

            entity();
            virtual ~entity();

            virtual void update(const float &dt);
            virtual void render(sf::RenderTarget &target);

            
            void move(const float &dt, const float dir_x, const float dir_y);

            void set_texture(sf::Texture &texture);

            void create_movement_component(const float max_velocity, const float acceleration, const float deceleration);
            void create_animation_component(sf::Texture &texture_sheet);
            void create_hitbox_component(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);


            virtual const sf::Vector2f& get_position() const;

            void set_position(const float x, const float y);

        private:
            void init_variables();
 
        protected:

            Movement_component *movement_component;
            Animation_component *animation_component;
            Hitbox_component *hitbox_component;
            sf::Sprite sprite;

    };
#endif