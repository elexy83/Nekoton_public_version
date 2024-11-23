#ifndef GUI_HPP
    #define GUI_HPP
    
   

    enum button_states
    {
        Btn_idle = 0,
        Btn_hover,
        Btn_active
    };

namespace gui
{
    class button
    {
        public:

            button(float x, float y, float width, float height,
                sf::Font *font, std::string text, float text_size,
                sf::Color idle_color, sf::Color hover_color, sf::Color active_color, short unsigned id = 0);
            virtual ~button();

            void render(sf::RenderTarget &target);
            void update(const sf::Vector2f &mouse_pos);

            const bool is_pressed();
            const std::string get_text() const;
            const short unsigned& get_id() const;
           

            void set_text(const std::string text);
            void set_id(const short unsigned id);

        private:

            short unsigned button_state;
            short unsigned id;

            sf::RectangleShape shape;
            sf::Font *font;
            sf::Text text;
            sf::Color idle_color;
            sf::Color hover_color;
            sf::Color active_color;
    };


//=================================================


    class Drop_down_list
    {
        public:

            Drop_down_list(float x, float y, float width, float height,sf::Font& font, std::string list[], unsigned nb_element, unsigned default_index = 0);
            ~Drop_down_list();
            void render(sf::RenderTarget &target);
            void update(const sf::Vector2f &mouse_pos, const float& dt);
            const bool get_key_time();
            const unsigned short &get_active_element_id();
            void update_key_time(const float& dt);

        private:
            
            gui::button* active_element;
            std::vector<gui::button*> list;
            sf::Font& font;
            bool show_list;
            float key_time;
            float key_time_max;
    };

    class Texture_selector
    {
        public:

            Texture_selector(float x, float y, float width, float height, float grid_size, const sf::Texture* texture_sheet);
            ~Texture_selector();

            void update(const sf::Vector2i& mouse_pos_window);
            void render(sf::RenderTarget &target);

            const bool& get_active() const;
            const sf::IntRect& get_texture_rect() const;

        private:

            sf::RectangleShape bounds;
            sf::Sprite sheet;
            sf::RectangleShape selector;
            sf::Vector2u mouse_pos_grid;
            sf::IntRect texture_rect;
            float grid_size;
            bool active;
    };
}
    
#endif