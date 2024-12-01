#include "../include/stdafx.hpp"
#include "../include/chose_character_3_state.hpp"
#include "../include/chose_character_2_state.hpp"
#include "../include/chose_character_4_state.hpp"
#include "../include/main_menu_state.hpp"
#include "../include/home_3_state.hpp"


chose_character_3_state::chose_character_3_state(State_data* state_data)
    :state(state_data)
{
    this->init_key_binds();
    this->init_font();
    this->init_button();
    
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Blue);
}

chose_character_3_state::~chose_character_3_state()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); it++) {
        delete it->second;
    }
}

void chose_character_3_state::update(const float &dt)
{
    this->update_mouse_position();
    this->update_key_time(dt);
    this->update_input(dt);
    this->update_button();
}

void chose_character_3_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->render_button(*target);
}

void chose_character_3_state::update_input(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Close"))) && this->get_key_time()) {
        this->states->push(new main_menu_state(this->state_data));
    }  
}

void chose_character_3_state::update_button()
{
    for (auto it : this->buttons)
    {
        it.second->update(this->mouse_pose_window);
    }

    if (this->buttons["BACK"]->is_pressed() && this->get_key_time()) {
        this->states->push(new main_menu_state(this->state_data));
    }

    if (this->buttons["GAMEMODE_3_STATE"]->is_pressed() && this->get_key_time()) {
        this->states->push(new Home_3_state(this->state_data));
    }

    if (this->buttons["CHOOSE_GAMEMODE_2_STATE"]->is_pressed() && this->get_key_time()) {
        this->states->push(new chose_character_2_state(this->state_data));
    }

    if (this->buttons["CHOOSE_GAMEMODE_4_STATE"]->is_pressed() && this->get_key_time()) {
        this->states->push(new chose_character_4_state(this->state_data));
    }
}

void chose_character_3_state::render_button(sf::RenderTarget &target)
{
    for (auto it : this->buttons)
    {
        it.second->render(target);
    }
}

void chose_character_3_state::init_key_binds()
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

void chose_character_3_state::init_font()
{
    if (!this->font.loadFromFile("fonts/Lato-Bold.ttf")) {
        throw("ERROR IN CHOSE_CHARACTER_3_STATE : can not load font");
    }
}

void chose_character_3_state::init_button()
{
    this->buttons["GAMEMODE_3_STATE"] = new gui::button(950.f, 200.f, 550.f, 150.f, &this->font,
        "NEW GAME 3", 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    this->buttons["CHOOSE_GAMEMODE_2_STATE"] = new gui::button(0.f, 450.f, 100.f, 100.f, &this->font,
        "<", 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    this->buttons["CHOOSE_GAMEMODE_4_STATE"] = new gui::button(1820.f, 450.f, 100.f, 100.f, &this->font,
        ">", 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    this->buttons["BACK"] = new gui::button(0.f, 0.f, 150.f, 50.f, &this->font,
        "BACK", 20, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));
}