#ifndef MOVEMENT_COMPONENT_HPP
    #define MOVEMENT_COMPONENT_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    



    enum movement_states {
        IDLE = 0,
        MOVING,
        MOVING_LEFT,
        MOVING_RIGHT,
        MOVING_UP,
        MOVING_DOWN
    };

    class Movement_component
    { 
        public:

            Movement_component(sf::Sprite &sprite, float max_velocity, float acceleration, float deceleration);
            virtual ~Movement_component();

            const bool get_state(const short unsigned state) const;

            void update(const float &dt);
            void move(const float dir_x, const float dir_y, const float &dt);

            const sf::Vector2f &get_velocity() const;
            const float &get_max_velocity() const;

        private:

            float max_velocity;
            float acceleration; 
            float deceleration;
            
            sf::Vector2f velocity;

            sf::Sprite &sprite;
    };

#endif