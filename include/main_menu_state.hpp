#ifndef MAIN_MENU_STATE_HPP
    #define MAIN_MENU_STATE_HPP
    #include "chose_character_1_state.hpp"
    #include "editor_state.hpp"
    #include "gui.hpp"
    #include "settings_state.hpp"
    #include "graphics_settings.hpp"

    class main_menu_state : public state
    {
        public: 

            main_menu_state(State_data* state_data); 
            virtual ~main_menu_state(); 

            void update(const float &dt);
            void render(sf::RenderTarget *target = nullptr);
            void update_input(const float &dt);
            void update_button();
            void render_button(sf::RenderTarget &target);

        private:

            sf::Font font;
            sf::RectangleShape background;
            std::map<std::string, gui::button*> buttons;
            
            void init_key_binds();
            void init_font();
            void init_button();
    };
#endif