#ifndef GAME_STATE_1_HPP
    #define GAME_STATE_1_HPP
    #include "state.hpp"

    class game_mode_1_state : public state
    {
        public:

            game_mode_1_state(State_data* state_data); 
            virtual ~game_mode_1_state(); 

            void update(const float &dt);
            void render(sf::RenderTarget *target = nullptr);
            void update_input(const float &dt);

        private:

           
            dwarf *Dwarf;

            void init_key_binds();
            void init_texture();
            void init_dwarf();
    };

#endif