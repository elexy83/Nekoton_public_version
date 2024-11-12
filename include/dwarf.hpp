#ifndef DWARF_HPP
    #define DWARF_HPP
    #include "entity.hpp"

    class dwarf : public entity
    {
        public:
            
            dwarf(float x, float y,  sf::Texture &texture);
            virtual ~dwarf();

        private:


            void init_variables(); 
            void init_component();
    };
#endif