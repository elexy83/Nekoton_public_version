#include "../include/stdafx.hpp"
#include "../include/main_menu_state.hpp"

main_menu_state::main_menu_state(State_data* state_data)
    :state(state_data)
{
    this->init_key_binds();
    this->init_font();  
    this->init_button();
    
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Blue);
}

main_menu_state::~main_menu_state()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); it++) {
        delete it->second;
    }
}

void main_menu_state::update(const float &dt)
{
    this->update_mouse_position();
    this->update_key_time(dt);
    this->update_input(dt);
    this->update_button();

    
}

void main_menu_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->render_button(*target);
}

void main_menu_state::update_input(const float &dt)
{
    
}

void main_menu_state::update_button()
{
    for (auto it : this->buttons)
    {
        it.second->update(this->mouse_pose_view);
    }

    if (this->buttons["EXIT"]->is_pressed() && this->get_key_time()) {
        this->window->close();
    }

    if (this->buttons["CHOSE_STATE"]->is_pressed() && this->get_key_time()) {
        this->states->push(new chose_character_1_state(this->state_data));
    }

    if (this->buttons["SETTINGS_STATE"]->is_pressed()) {
        this->states->push(new Settings_state(this->state_data));
    }

    if (this->buttons["EDITOR_STATE"]->is_pressed() && this->get_key_time()) {
        this->states->push(new Editor_state(this->state_data));
    }
}

void main_menu_state::render_button(sf::RenderTarget &target)
{
    for (auto it : this->buttons)
    {
        it.second->render(target);
    }
}

void main_menu_state::init_key_binds()
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

void main_menu_state::init_font()
{
    if (!this->font.loadFromFile("fonts/Lato-Bold.ttf")) {
        throw("ERROR IN MAIN_MENU_STATE : can not load font");
    }
}

void main_menu_state::init_button()
{
    this->buttons["CHOSE_STATE"] = new gui::button(680.f, 400.f, 550.f, 150.f, &this->font,
        "PLAY", 30, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    this->buttons["SETTINGS_STATE"] = new gui::button(680.f, 600.f, 550.f, 150.f, &this->font,
        "SETTINGS", 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    this->buttons["EXIT"] = new gui::button(680.f, 800.f, 550.f, 150.f, &this->font,
       "QUIT", 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    this->buttons["EDITOR_STATE"] = new gui::button(1500.f, 0.f, 200.f, 50.f, &this->font,
       "EDITOR", 10, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));
}