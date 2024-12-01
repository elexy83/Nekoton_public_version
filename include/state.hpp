#ifndef STATE_HPP
    #define STATE_HPP
    #include "dwarf.hpp"
    #include "graphics_settings.hpp"

    class dwarf;
    class Graphics_settings;
    class state;
    class State_data
    {
        public:

            State_data() {};

            float grid_size;
            sf::RenderWindow *window;
            std::map<std::string, int>* supported_keys;
            std::stack<state*>* states;
            Graphics_settings* gfx_settings;
    };
    
    class state
    { 
        public:
            state(State_data* state_data);
            virtual ~state();

            const bool &get_quit() const;
            const bool get_key_time();

            virtual void update(const float &dt) = 0;
            virtual void render(sf::RenderTarget *target = nullptr) = 0;
            virtual void update_mouse_position(sf::View* view = NULL);
            virtual void update_input(const float &dt) = 0;
            void end_state();
            void pause_state();
            void unpaused_state();
            virtual void update_key_time(const float &dt);

            
        protected:

            std::stack<state*>* states;
            sf::Vector2i mouse_pose_screen;
            sf::Vector2i mouse_pose_window;
            sf::Vector2f mouse_pose_view;
            sf::Vector2i mouse_pos_grid;

            State_data *state_data;

            sf::RenderWindow *window;
            bool quit;
            bool paused;
            float key_time;
            float key_time_max;
            float grid_size;

            std::map<std::string, int>* supported_keys;
            std::map<std::string, int> key_binds;

            std::map<std::string, sf::Texture> textures;

            virtual void init_key_binds() = 0;
    };
#endif