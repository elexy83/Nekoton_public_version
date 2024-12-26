#include "../include/stdafx.hpp"
#include "../include/editor_state.hpp"
#include "../include/graphics_settings.hpp"



Editor_state::Editor_state(State_data* state_data)
    :state(state_data)
{
    this->init_variables();
    this->init_view();
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
    this->update_mouse_position(&this->view);
    this->update_key_time(dt);
    this->update_input(dt);
    

    if(!this->paused) //unpaused
    {
        this->update_button();
        this->update_gui(dt);
        this->update_editor_input(dt);
    }
    else //paused
    {
        this->p_menu->update(this->mouse_pose_window);
        this->update_pause_menu_buttons();
    }

    this->update_button();
}

void Editor_state::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    target->setView(this->view);
    this->tile_map->render_editor(*target, this->mouse_pos_grid);

    target->setView(this->window->getDefaultView());
    this->render_button(*target);


    this->render_gui(*target);

    if (this->paused)
    {
        target->setView(this->window->getDefaultView());
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


void Editor_state::update_gui(const float& dt)
{
    std::stringstream ss;
    this->texture_selector->update(this->mouse_pose_window, dt);
    if(!this->texture_selector->get_active())
    {
        this->selector_rect.setTextureRect(this->texture_rect);
        this->selector_rect.setPosition(this->mouse_pos_grid.x * this->state_data->grid_size, this->mouse_pos_grid.y * this->state_data->grid_size);
    }

    this->cursor_text.setPosition(this->mouse_pose_view.x + 100.f, this->mouse_pose_view.y - 50.f);
    ss << this->mouse_pose_view.x << " " << this->mouse_pose_view.y <<
        "\n" << this->mouse_pos_grid.x << " " << this->mouse_pos_grid.y <<
        "\n" << this->texture_rect.left << " " << this->texture_rect.top <<
        "\n" << "collision: " << this->collision << 
        "\n" << "type: " << this->type <<
        "\n" << "tiles: " << this->tile_map->get_layer_size(this->mouse_pos_grid.x, this->mouse_pos_grid.y, this->layer);
    this->cursor_text.setString(ss.str());    
}


void Editor_state::update_button()
{
    for (auto it : this->buttons)
    {
        it.second->update(this->mouse_pose_window);
    }
}


void Editor_state::update_editor_input(const float &dt)
{

    //move view
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_CAM_UP"))))
    {
        this->view.move(0.f, -this->cam_speed * dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_CAM_DOWN"))))
    {
        this->view.move(0.f, this->cam_speed * dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_CAM_LEFT"))))
    {
        this->view.move(-this->cam_speed * dt, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_CAM_RIGHT"))))
    {
        this->view.move(this->cam_speed * dt, 0.f);
    }

    //add a tile to the tilemap
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->get_key_time())
    {
        if (!this->side_bar.getGlobalBounds().contains(sf::Vector2f(this->mouse_pose_window)))
        {
            if(!this->texture_selector->get_active())
            {
                this->tile_map->add_tile(this->mouse_pos_grid.x, this->mouse_pos_grid.y, 0, this->texture_rect, this->collision, this->type);
            }
            else
            {
                this->texture_rect = this->texture_selector->get_texture_rect();
            }
        }
    }
    //remove tile for the tilemap
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->get_key_time())
    {   
        if (!this->side_bar.getGlobalBounds().contains(sf::Vector2f(this->mouse_pose_window)))
        {
            if(!this->texture_selector->get_active())
            {
                this->tile_map->remove_tile(this->mouse_pos_grid.x, this->mouse_pos_grid.y, 0);
            }
        }
    }

    //toggle collision
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("COLLISION"))) && this->get_key_time())
    {
        if (this->collision)
        {
            this->collision = false;
        }
        else 
        {
            this->collision = true;
        }
    }
    //toggle type
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("TYPE_INC"))) && this->get_key_time())
    {
        this->type++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("TYPE_DEC"))) && this->get_key_time())
    {
        if(this->type > 0)
            this->type--;
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
    {
        target.setView(this->view);
        target.draw(this->selector_rect);
    }
    target.setView(this->window->getDefaultView());
    this->texture_selector->render(target);
    target.draw(this->side_bar);

    target.setView(this->view);
    target.draw(this->cursor_text);
}

void Editor_state::update_pause_menu_buttons()
{
    if (this->p_menu->is_button_pressed("EXIT_STATE") && this->get_key_time())
    {
        this->end_state();
    }
    if (this->p_menu->is_button_pressed("SAVE") && this->get_key_time())
    {
        this->tile_map->save_to_file("test.mp");
    }
    if (this->p_menu->is_button_pressed("LOAD") && this->get_key_time())
    {
        this->tile_map->load_from_file("test.mp");
    }
}

void Editor_state::init_view()
{
    this->view.setSize(sf::Vector2f(
            static_cast<float>(this->state_data->gfx_settings->resolution.width),
            static_cast<float>(this->state_data->gfx_settings->resolution.height))
        );

    
    this->view.setCenter(static_cast<float>(this->state_data->gfx_settings->resolution.width) / 2.f,
                         static_cast<float>(this->state_data->gfx_settings->resolution.height) / 2.f);
    this->view.zoom(0.75f);
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
    this->p_menu->add_button("SAVE", 700.f, "SAVE");
    this->p_menu->add_button("LOAD", 500.f, "LOAD");
}

void Editor_state::init_gui()
{

    this->side_bar.setSize(sf::Vector2f(96.f , static_cast<float>(this->state_data->gfx_settings->resolution.height)));
    this->side_bar.setFillColor(sf::Color(50, 50, 50, 100));
    this->side_bar.setOutlineColor(sf::Color(200,200,200,150));
    this->side_bar.setOutlineThickness(1.f);


    this->selector_rect.setSize(sf::Vector2f(this->state_data->grid_size, this->state_data->grid_size));
    this->selector_rect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selector_rect.setOutlineThickness(1.f);
    this->selector_rect.setOutlineColor(sf::Color::Green);
    this->selector_rect.setTexture(this->tile_map->get_tile_sheet());
    this->selector_rect.setTextureRect(this->texture_rect);

    // this->map_rect.setSize(sf::Vector2f(this->state_data->grid_size, this->state_data->grid_size));
    // this->map_rect.setFillColor(sf::Color::Transparent);
    // this->map_rect.setOutlineThickness(1.f);
    // this->map_rect.setOutlineColor(sf::Color::White);

    this->texture_selector = new gui::Texture_selector(1100.f, 20.f, 512.f, 512.f, this->state_data->grid_size ,this->tile_map->get_tile_sheet(), this->font, "TS");
    
}

void Editor_state::init_tile_map()
{
    this->tile_map = new Tile_map(this->state_data->grid_size, 20, 13, "assets/Map01.png");
}

void Editor_state::init_variables()
{
    this->texture_rect = sf::IntRect(0, 0, static_cast<int>(this->state_data->grid_size), static_cast<int>(this->state_data->grid_size));
    this->collision = false;
    this->type = Tile_type::DEFFAULT;
    cam_speed = 300.f;
    this->layer = 0;
}

void Editor_state::init_text()
{
    this->cursor_text.setFont(this->font);
    this->cursor_text.setFillColor(sf::Color::White);
    this->cursor_text.setCharacterSize(12);
    this->cursor_text.setPosition(this->mouse_pose_view.x, this->mouse_pose_view.y);
}