#include "../include/stdafx.hpp"
#include "../include/game_mode_2_state.hpp"
#include "../include/home_2_state.hpp"
#include "../include/chose_character_2_state.hpp"
#include "../include/character_2.hpp"

game_mode_2_state::game_mode_2_state(State_data* state_data)
    :state(state_data)
{
    this->init_deffered_render();
    this->init_view();
    this->init_key_binds();
    this->init_font();
    this->init_texture();
    this->init_paused_menu();
    this->init_character();
    this->init_tile_map();
}

game_mode_2_state::~game_mode_2_state()
{
    delete this->p_menu;
    delete this->Chara_2;
    delete this->tile_map;
}

void game_mode_2_state::update(const float &dt)
{

    this->update_mouse_position(&this->view);
    this->update_key_time(dt);
    this->update_input(dt);

    if (!this->paused)
    {
        this->update_view(dt);
        this->update_player_input(dt); 
        this->update_tile_map(dt);
        this->Chara_2->update(dt);
    }
    else
    {
        this->p_menu->update(this->mouse_pose_window);
        this->update_pause_menu_buttons();
    }
}

void game_mode_2_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }
    this->render_texture.clear();

    this->render_texture.setView(this->view);
    this->tile_map->render(this->render_texture, this->Chara_2);

    this->Chara_2->render(this->render_texture);

    if (this->paused)
    {
        this->render_texture.setView(this->render_texture.getDefaultView());
        this->p_menu->render(this->render_texture);   
    }

    //final render
    this->render_texture.display();
    this->render_sprite.setTexture(this->render_texture.getTexture());
    target->draw(this->render_sprite);
}

void game_mode_2_state::update_player_input(const float &dt)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Left")))) {
        this->Chara_2->move(dt, -1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Right")))){
        this->Chara_2->move(dt, 1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Down")))){
       this->Chara_2->move(dt, 0.f, 1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Up")))) {
        this->Chara_2->move(dt, 0.f, -1.f);
    }
}

void game_mode_2_state::update_pause_menu_buttons()
{
    if (this->p_menu->is_button_pressed("EXIT_STATE")&& this->get_key_time())
    {
        this->states->push(new Home_2_state(this->state_data));
    }
}

void game_mode_2_state::update_view(const float &dt)
{
   
    this->view.setCenter(this->Chara_2->get_position());
}

void game_mode_2_state::update_tile_map(const float &dt)
{
    this->tile_map->update();
    this->tile_map->update_collision(this->Chara_2, dt);
}

void game_mode_2_state::update_input(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Close"))) && this->get_key_time())
    {
        if (!this->paused)
            this->pause_state();
        else
            this->unpaused_state();
    }   
}

void game_mode_2_state::init_key_binds()
{

    std::ifstream ifs;
    ifs.open("Config/game_mode_1_keys");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key_2 = "";

        while (ifs >> key >> key_2) {
            this->key_binds[key] = this->supported_keys->at(key_2);
        }
    }
    ifs.close();
}

void game_mode_2_state::init_texture()
{
    
    if (!this->textures["mini_index"].loadFromFile("assets/toutes_les_mini_index.png"))
        throw "Error Dwarf_top texture not loaded";
}

void game_mode_2_state::init_paused_menu()
{
    this->p_menu = new Pause_menu(*this->window, this->font);
    
    this->p_menu->add_button("EXIT_STATE", 800.f, "QUIT");
}

void game_mode_2_state::init_character()
{
    this->Chara_2 = new character_2(100, 100, this->textures["mini_index"]);
}

void game_mode_2_state::init_tile_map()
{
    this->tile_map = new Tile_map(this->state_data->grid_size, 20, 13, "assets/Map01.png");
    this->tile_map->load_from_file("test.mp");
}

void game_mode_2_state::init_deffered_render()
{
    this->render_texture.create(this->state_data->gfx_settings->resolution.width, this->state_data->gfx_settings->resolution.height);
    this->render_sprite.setTexture(this->render_texture.getTexture());
    this->render_sprite.setTextureRect(sf::IntRect(0, 0, this->state_data->gfx_settings->resolution.width, this->state_data->gfx_settings->resolution.height));
}

void game_mode_2_state::init_font()
{
    if (!this->font.loadFromFile("fonts/Lato-Bold.ttf")) {
        throw("ERROR IN GAME_MODE_2_STATE : can not load font");
    }
}

void game_mode_2_state::init_view()
{
    this->view.setSize(sf::Vector2f(this->state_data->gfx_settings->resolution.width, this->state_data->gfx_settings->resolution.height));
    this->view.setCenter(this->state_data->gfx_settings->resolution.width / 2.f,this->state_data->gfx_settings->resolution.height / 2.f);
    this->view.zoom(0.235f);
}