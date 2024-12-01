#ifndef HOME_1_STATE_HPP
    #define HOME_1_STATE_HPP
    #include "gui.hpp"
    #include "graphics_settings.hpp"
    #include "settings_state.hpp"

    class Home_1_state : public state
    {
        public: 

            Home_1_state(State_data* state_data); 
            virtual ~Home_1_state();

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