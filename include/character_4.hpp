#ifndef CHARACTER_4_HPP
    #define CHARACTER_4_HPP
    #include "entity.hpp"

    class character_4 : public entity
    {
        public:
            
            character_4(float x, float y,  sf::Texture &texture_sheet);
            virtual ~character_4();
            virtual void update(const float &dt);

            void update_animation(const float &dt);
            void update_attack();

        private:

            void init_variables(); 
            void init_component();

            bool attaking;
    }; 
#endif