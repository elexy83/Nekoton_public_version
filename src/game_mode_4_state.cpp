#include "../include/stdafx.hpp"
#include "../include/game_mode_4_state.hpp"
#include "../include/character_4.hpp"
#include "../include/chose_character_4_state.hpp"



game_mode_4_state::game_mode_4_state(State_data* state_data)
    :state(state_data)
{
    this->init_key_binds();
    this->init_font();
    this->init_texture();
    this->init_paused_menu();
    this->init_character();
    this->init_tile_map();
}

game_mode_4_state::~game_mode_4_state()
{
    delete this->p_menu;
    delete this->Chara_4;
    delete this->tile_map;
}

void game_mode_4_state::update(const float &dt)
{

    this->update_mouse_position();
    this->update_key_time(dt);
    this->update_input(dt);

    if (!this->paused)
    {
        this->update_player_input(dt); 
        this->Chara_4->update(dt);
    }
    else
    {
        this->p_menu->update(this->mouse_pose_view);
    }
}

void game_mode_4_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }

    //this->map.render(*target);

    this->Chara_4->render(*target);

    if (this->paused)
    {
        this->p_menu->render(*target);
        this->update_pause_menu_buttons();
    }
}

void game_mode_4_state::update_player_input(const float &dt)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Left")))) {
        this->Chara_4->move(dt, -1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Right")))){
        this->Chara_4->move(dt, 1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Down")))){
       this->Chara_4->move(dt, 0.f, 1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Up")))) {
        this->Chara_4->move(dt, 0.f, -1.f);
    }
}

void game_mode_4_state::update_pause_menu_buttons()
{
    if (this->p_menu->is_button_pressed("EXIT_STATE")&& this->get_key_time())
    {
        this->states->push(new chose_character_4_state(this->state_data));
    }
}

void game_mode_4_state::update_input(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Close"))) && this->get_key_time())
    {
        if (!this->paused)
            this->pause_state();
        else
            this->unpaused_state();
    }   
}

void game_mode_4_state::init_key_binds()
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

void game_mode_4_state::init_texture()
{
    
    if (!this->textures["mini_index"].loadFromFile("assets/toutes_les_mini_index.png"))
        throw "Error Dwarf_top texture not loaded";
}

void game_mode_4_state::init_paused_menu()
{
    this->p_menu = new Pause_menu(*this->window, this->font);
    
    this->p_menu->add_button("EXIT_STATE", 800.f, "QUIT");
}

void game_mode_4_state::init_character()
{
    this->Chara_4 = new character_4(100, 100, this->textures["mini_index"]);
}

void game_mode_4_state::init_tile_map()
{
    this->tile_map = new Tile_map(this->state_data->grid_size, 10, 10);
}

void game_mode_4_state::init_font()
{
    if (!this->font.loadFromFile("fonts/Lato-Bold.ttf")) {
        throw("ERROR IN GAME_MODE_4_STATE : can not load font");
    }
}