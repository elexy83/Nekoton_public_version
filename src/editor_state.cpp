#include "../include/stdafx.hpp"
#include "../include/editor_state.hpp"
#include "../include/graphics_settings.hpp"


Editor_state::Editor_state(State_data* state_data)
    :state(state_data)
{
    this->init_variables();
    this->init_font();
    this->init_text();
    this->init_key_binds();
    this->init_paused_menu();
    this->init_button();
    this->init_tile_map();
    this->init_gui();
}

Editor_state::~Editor_state()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); it++) {
        delete it->second;
    }
    delete this->p_menu;
    delete this->tile_map;
    delete this->texture_selector;
}

void Editor_state::update(const float &dt)
{
    this->update_mouse_position();
    this->update_key_time(dt);
    this->update_input(dt);

    if(!this->paused)
    {
        this->update_button();
        this->update_gui();
        this->update_editor_input(dt);
    }
    else
    {
        this->p_menu->update(this->mouse_pose_view);
        this->update_pause_menu_buttons();
    }

    this->update_button();
}

void Editor_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }
    

    this->tile_map->render(*target);

    this->render_button(*target);
    this->render_gui(*target);

    if (this->paused)
    {
        this->p_menu->render(*target);
    }
    
}

void Editor_state::update_input(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Close"))) && this->get_key_time())
    {
        if (!this->paused)
            this->pause_state();
        else
            this->unpaused_state();
    }
}


void Editor_state::update_gui()
{
    std::stringstream ss;
    this->texture_selector->update(this->mouse_pose_window);
    if(!this->texture_selector->get_active())
    {
        this->selector_rect.setTextureRect(this->texture_rect);
        this->selector_rect.setPosition(this->mouse_pos_grid.x * this->state_data->grid_size, this->mouse_pos_grid.y * this->state_data->grid_size);
    }

    this->cursor_text.setPosition(this->mouse_pose_view.x + 100.f, this->mouse_pose_view.y - 50.f);
    ss << this->mouse_pose_view.x << " " << this->mouse_pose_view.y <<
        "\n" << this->mouse_pos_grid.x << " " << this->mouse_pos_grid.y <<
        "\n" << this->texture_rect.left << " " << this->texture_rect.top;
    this->cursor_text.setString(ss.str());    
}


void Editor_state::update_button()
{
    for (auto it : this->buttons)
    {
        it.second->update(this->mouse_pose_view);
    }
}


void Editor_state::update_editor_input(const float &dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->get_key_time())
    {   
        if(!this->texture_selector->get_active())
        {
            this->tile_map->add_tile(this->mouse_pos_grid.x, this->mouse_pos_grid.y, 0, this->texture_rect);
        }
        else
        {
            this->texture_rect = this->texture_selector->get_texture_rect();
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->get_key_time())
    {   
        if(!this->texture_selector->get_active())
        {
            this->tile_map->remove_tile(this->mouse_pos_grid.x, this->mouse_pos_grid.y, 0);
        }
    }
}


void Editor_state::render_button(sf::RenderTarget &target)
{
     for (auto it : this->buttons)
    {
        it.second->render(target);
    }
}


void Editor_state::render_gui(sf::RenderTarget &target)
{

    if (!this->texture_selector->get_active())
        target.draw(this->selector_rect);

    this->texture_selector->render(target);
    target.draw(this->cursor_text);
}


void Editor_state::update_pause_menu_buttons()
{
    if (this->p_menu->is_button_pressed("EXIT_STATE") && this->get_key_time())
    {
        this->end_state();
    }
}

void Editor_state::init_key_binds()
{
    std::ifstream ifs;
    ifs.open("Config/editor_keys");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key_2 = "";

        while (ifs >> key >> key_2) {
            this->key_binds[key] = this->supported_keys->at(key_2);
        }

    }
    ifs.close();
}

void Editor_state::init_font()
{
    if (!this->font.loadFromFile("fonts/Lato-Bold.ttf")) {
        throw("ERROR IN EDITOR_STATE : can not load font");
    }
}

void Editor_state::init_button()
{
 
}

void Editor_state::init_paused_menu()
{
    this->p_menu = new Pause_menu(*this->window, this->font);
    
    this->p_menu->add_button("EXIT_STATE", 800.f, "QUIT");
}

void Editor_state::init_gui()
{
    this->selector_rect.setSize(sf::Vector2f(this->state_data->grid_size, this->state_data->grid_size));

    this->selector_rect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selector_rect.setOutlineThickness(1.f);
    this->selector_rect.setOutlineColor(sf::Color::Green);

    this->selector_rect.setTexture(this->tile_map->get_tile_sheet());
    this->selector_rect.setTextureRect(this->texture_rect);

    this->texture_selector = new gui::Texture_selector(500.f, 20.f, 512.f, 512.f, this->state_data->grid_size ,this->tile_map->get_tile_sheet());
}

void Editor_state::init_tile_map()
{
    this->tile_map = new Tile_map(this->state_data->grid_size, 10, 10);
}

void Editor_state::init_variables()
{
    this->texture_rect = sf::IntRect(0, 0, static_cast<int>(this->state_data->grid_size), static_cast<int>(this->state_data->grid_size));
}

void Editor_state::init_text()
{
    this->cursor_text.setFont(this->font);
    this->cursor_text.setFillColor(sf::Color::White);
    this->cursor_text.setCharacterSize(12);
    this->cursor_text.setPosition(this->mouse_pose_view.x, this->mouse_pose_view.y);
}