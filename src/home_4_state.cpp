#include "../include/stdafx.hpp"
#include "../include/home_4_state.hpp"
#include "../include/chose_character_4_state.hpp"


Home_4_state::Home_4_state(State_data* state_data): state(state_data)
{
    this->init_key_binds();
    this->init_font();
    this->init_button();
    
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Blue);
}

Home_4_state::~Home_4_state()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); it++) {
        delete it->second;
    }
}

void Home_4_state::update(const float &dt)
{
    this->update_mouse_position();
    this->update_key_time(dt);
    this->update_input(dt);
    this->update_button();
}

void Home_4_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->render_button(*target);
}

void Home_4_state::update_input(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Close"))) && this->get_key_time()) {
        this->states->push(new chose_character_4_state(this->state_data));
    }  
}

void Home_4_state::update_button()
{
    for (auto it : this->buttons)
    {
        it.second->update(this->mouse_pose_window);
    }

    if (this->buttons["BACK"]->is_pressed() && this->get_key_time()) {
        this->states->push(new chose_character_4_state(this->state_data));
    }

    // if (this->buttons["GAMEMODE_4_STATE"]->is_pressed() && this->get_key_time()) {
    //     this->states->push(new game_mode_4_state(this->state_data));
    // }
}

void Home_4_state::render_button(sf::RenderTarget &target)
{
    for (auto it : this->buttons)
    {
        it.second->render(target);
    }
}

void Home_4_state::init_key_binds()
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

void Home_4_state::init_font()
{
    if (!this->font.loadFromFile("fonts/Lato-Bold.ttf")) {
        throw("ERROR IN HOME_4_STATE: can not load font");
    }
}

void Home_4_state::init_button()
{
    this->buttons["GAMEMODE_4_STATE"] = new gui::button(50.f, 850.f, 200.f, 100.f, &this->font,
        "PLAY", 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    this->buttons["BACK"] = new gui::button(0.f, 0.f, 150.f, 50.f, &this->font,
        "BACK", 20, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));
}