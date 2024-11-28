#ifndef GAME_STATE_2_HPP
    #define GAME_STATE_2_HPP
    #include "state.hpp"
    #include "character_2.hpp"
    #include "pause_menu.hpp"
    #include "tile_map.hpp"

    class game_mode_2_state : public state
    {
        public:

            game_mode_2_state(State_data* state_data); 
            virtual ~game_mode_2_state(); 

            void update(const float &dt);
            void render(sf::RenderTarget *target = nullptr);
            void update_input(const float &dt);
            void update_player_input(const float &dt);
            void update_pause_menu_buttons();
            void update_view(const float &dt);
            void update_tile_map(const float& dt);

        private:

            Pause_menu* p_menu;
            character_2 *Chara_2;
            sf::Font font;

            Tile_map *tile_map;

            sf::View view;
            sf::RenderTexture render_texture;
            sf::Sprite render_sprite;

            void init_font();
            void init_view();
            void init_key_binds();
            void init_texture();
            void init_paused_menu();
            void init_character();
            void init_tile_map();
    };

#endif