#include "../include/stdafx.hpp"
#include "../include/game_mode_1_state.hpp"
#include "../include/home_1_state.hpp"
#include "../include/chose_character_1_state.hpp"

game_mode_1_state::game_mode_1_state(State_data* state_data) 
    :state(state_data)
{
    this->init_key_binds();
    this->init_texture();
    this->init_dwarf();
}

game_mode_1_state::~game_mode_1_state()
{
   
}

void game_mode_1_state::update(const float &dt)
{
    this->update_mouse_position();
    this->update_input(dt); 
    this->Dwarf->update(dt);
}

void game_mode_1_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }
}

void game_mode_1_state::update_input(const float &dt)
{
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Left")))) {
        this->Dwarf->move(dt, -1.f, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Right")))){
        this->Dwarf->move(dt, 1.f, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Down")))){
       this->Dwarf->move(dt, 0.f, 1.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Up")))) {
        this->Dwarf->move(dt, 0.f, -1.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Close")))) {
        this->end_state();
    }  
}

void game_mode_1_state::init_key_binds()
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

void game_mode_1_state:: init_texture()
{
    
    if (!this->textures["dwarf_top"].loadFromFile("assets/mini_index.png"))
        throw "Error Dwarf_top texture not loaded";
}

void game_mode_1_state::init_dwarf()
{

}