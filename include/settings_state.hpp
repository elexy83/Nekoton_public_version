#ifndef SETTINGS_STATE_HPP
    #define SETTINGS_STATE_HPP
    #include "state.hpp"
    #include "gui.hpp"
    #include "main_menu_state.hpp"

    class Settings_state : public state
    {
        public:

            Settings_state(State_data* state_data);
            virtual ~Settings_state();

            void update(const float &dt);
            void render(sf::RenderTarget *target = nullptr);
            void update_input(const float &dt);
            void update_gui(const float &dt);
            void render_gui(sf::RenderTarget &target);

        private: 

            sf::Font font;
            sf::RectangleShape background;
            
            std::map<std::string, gui::button*> buttons;
            std::map<std::string, gui::Drop_down_list*> drop_down_list;
            sf::Text option_text;
            std::vector<sf::VideoMode> modes;

            void init_key_binds();
            void init_font();
            void init_gui();
            void init_text();
            void init_variable();
        
    };

#endif