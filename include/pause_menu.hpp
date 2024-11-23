#ifndef PAUSE_MENU_HPP
    #define PAUSE_MENU_HPP
    
    #include "gui.hpp"

    class Pause_menu
    {
        public:

            Pause_menu(sf::RenderWindow &window, sf::Font &font);
            virtual ~Pause_menu();
            
            void update(const sf::Vector2f& mouse_pos);
            void render(sf::RenderTarget& target);
            void add_button(const std::string key,float y, const std::string text);
            const bool is_button_pressed(const std::string key);

            std::map<std::string, gui::button*>& get_buttons();

        private:

            sf::RectangleShape background;
            sf::RectangleShape container;
            
            std::map<std::string, gui::button*> buttons;

            sf::Font& font;
            sf::Text menu_text;
    };

#endif