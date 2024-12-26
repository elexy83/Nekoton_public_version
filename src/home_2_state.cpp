#include "../include/stdafx.hpp"
#include "../include/home_2_state.hpp"
#include "../include/chose_character_2_state.hpp"


Home_2_state::Home_2_state(State_data* state_data): state(state_data)
{
    this->init_key_binds();
    this->init_font();
    this->init_button();
    
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Blue);
}

Home_2_state::~Home_2_state()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); it++) {
        delete it->second;
    }
}

void Home_2_state::update(const float &dt)
{
    this->update_mouse_position();
    this->update_key_time(dt);
    this->update_input(dt);
    this->update_button();
}

void Home_2_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->render_button(*target);
}

void Home_2_state::update_input(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Close"))) && this->get_key_time()) {
        this->states->push(new chose_character_2_state(this->state_data));
    }  
}

void Home_2_state::update_button()
{
    for (auto it : this->buttons)
    {
        it.second->update(this->mouse_pose_window);
    }

    if (this->buttons["BACK"]->is_pressed() && this->get_key_time()) {
        this->states->push(new chose_character_2_state(this->state_data));
    }

    if (this->buttons["GAMEMODE_2_STATE"]->is_pressed() && this->get_key_time()) {
        this->states->push(new game_mode_2_state(this->state_data));
    }
}

void Home_2_state::render_button(sf::RenderTarget &target)
{
    for (auto it : this->buttons)
    {
        it.second->render(target);
    }
}

void Home_2_state::init_key_binds()
{
    std::ifstream ifs;
    ifs.open("Config/main_menu_keys");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key_2 = "";

        while (ifs >> key >> key_2) {
            this->key_binds[key] = this->supported_keys->at(key_2);
        }
    }
    ifs.close();
}

void Home_2_state::init_font()
{
    if (!this->font.loadFromFile("fonts/Lato-Bold.ttf")) {
        throw("ERROR IN HOME_2_STATE: can not load font");
    }
}

void Home_2_state::init_button()
{
    this->buttons["GAMEMODE_2_STATE"] = new gui::button(
        this->state_data->gfx_settings->resolution.width * 0.02604,
        this->state_data->gfx_settings->resolution.height * 0.78703,
        this->state_data->gfx_settings->resolution.width * 0.10416,
        this->state_data->gfx_settings->resolution.height * 0.09259,
        &this->font, "PLAY",
        this->state_data->gfx_settings->resolution.width * 0.01302,
        sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    this->buttons["BACK"] = new gui::button(
        0.f,
        0.f,
        this->state_data->gfx_settings->resolution.width * 0.078125,
        this->state_data->gfx_settings->resolution.height * 0.04629,
        &this->font, "BACK",
        this->state_data->gfx_settings->resolution.width * 0.01302,
        sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));
}