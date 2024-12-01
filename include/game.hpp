#ifndef GAME_HPP
    #define GAME_HPP
    #include "main_menu_state.hpp"

    class game
    {
        public:

            game();
            virtual ~game(); 

            void run();


            void update();
            void update_dt();
            void render();
            void poll_events();
            

        private:


            std::stack<state*> states;
            sf::RenderWindow* window;
            sf::Event event;
            sf::Vector2i mouse_pos_window;
            sf::Clock dt_clock;


            Graphics_settings gfx_settings;
            State_data state_data;

            float dt;
            std::map<std::string, int> supported_keys;

            float grid_size;

            void init_graphics_settings();
            void init_state_data();
            void init_variables();
            void init_window(); 
            void init_keys();
            void init_states();
    };

#endif


