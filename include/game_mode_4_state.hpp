#ifndef GAME_STATE_4_HPP
    #define GAME_STATE_4_HPP
    #include "state.hpp"
    #include "character_4.hpp"
    #include "pause_menu.hpp"
    #include "tile_map.hpp"

    class game_mode_4_state : public state
    {
        public:

            game_mode_4_state(State_data* state_data); 
            virtual ~game_mode_4_state(); 

            void update(const float &dt);
            void render(sf::RenderTarget *target = nullptr);
            void update_input(const float &dt);
            void update_player_input(const float &dt);
            void update_pause_menu_buttons();

        private:

            Pause_menu* p_menu;
            character_4 *Chara_4;
            sf::Font font;

            Tile_map *tile_map;

            void init_font();
            void init_key_binds();
            void init_texture();
            void init_paused_menu();
            void init_character();
            void init_tile_map();
    };

#endif