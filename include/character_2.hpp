#ifndef CHARACTER_2_HPP
    #define CHARACTER_2_HPP
    #include "entity.hpp"

    class character_2 : public entity
    {
        public:
            
            character_2(float x, float y,  sf::Texture &texture_sheet);
            virtual ~character_2();
            virtual void update(const float &dt);

            void update_animation(const float &dt);
            void update_attack();

            void render(sf::RenderTarget& target);

        private:

            void init_variables(); 
            void init_component();

            bool attaking;
    }; 
#endif