#ifndef EDITOR_STATE_HPP
    #define EDITOR_STATE_HPP
    #include "state.hpp"
    #include "gui.hpp"
    #include "pause_menu.hpp"
    #include "tile_map.hpp"

    class state;
    class Gui;
    class Pause_menu;
    class Tile_map;

    class Editor_state: public state
    {
       public: 

            Editor_state(State_data* state_data); 
            virtual ~Editor_state(); 

            void update(const float &dt);
            void render(sf::RenderTarget *target = nullptr);
            void update_input(const float &dt);
            void update_gui();
            void update_button();
            void render_button(sf::RenderTarget &target);
            void render_gui(sf::RenderTarget &target);
            void update_pause_menu_buttons();
            
        private:

            sf::Font font;
            Pause_menu* p_menu;
            Tile_map *tile_map;

            sf::RectangleShape selector_rect;
            
            std::map<std::string, gui::button*> buttons;
            void init_key_binds();
            void init_font();
            void init_button();
            void init_paused_menu();
            void init_gui();
            void init_tile_map();
    };

#endif