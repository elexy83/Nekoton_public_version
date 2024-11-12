#include "../include/stdafx.hpp"
#include "../include/settings_state.hpp"

Settings_state::Settings_state(State_data *state_data) : state(state_data)
{
    this->init_variable();
    this->init_key_binds();
    this->init_font();  
    this->init_gui();
    this->init_text();
 
    
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Blue);
}

Settings_state::~Settings_state()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); it++) {
        delete it->second;
    }

    auto it2 = this->drop_down_list.begin();
    for (it2 = this->drop_down_list.begin(); it2 != this->drop_down_list.end(); it2++) {
        delete it2->second;
    }
}

void Settings_state::update(const float &dt)
{
    this->update_mouse_position();
    this->update_key_time(dt);
    this->update_input(dt);
    this->update_gui(dt);
}

void Settings_state::render(sf::RenderTarget* target)
{
    if (!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->render_gui(*target);
    target->draw(this->option_text);
}

void Settings_state::update_input(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("Close")))&& this->get_key_time()) {
        this->states->push(new main_menu_state(this->state_data));
    }  
}

void Settings_state::update_gui(const float &dt)
{
    for (auto it : this->buttons)
    {
        it.second->update(this->mouse_pose_view);
    }

    if (this->buttons["EXIT"]->is_pressed() && this->get_key_time())
    {
        this->states->push(new main_menu_state(this->state_data));
    }

    if (this->buttons["APPLY"]->is_pressed() && this->get_key_time())
    {
        this->state_data->gfx_settings->resolution = this->modes[this->drop_down_list["RESOLUTION"]->get_active_element_id()];
        this->window->create(this->state_data->gfx_settings->resolution, this->state_data->gfx_settings->title, sf::Style::Default);
    }

    for (auto it : this->drop_down_list)
    {
        it.second->update(this->mouse_pose_view, dt);
    }
}

void Settings_state::render_gui(sf::RenderTarget &target)
{
    for (auto it : this->buttons)
    {
        it.second->render(target);
    }

    for (auto it : this->drop_down_list)
    {
        it.second->render(target);
    }
}

void Settings_state::init_key_binds()
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

void Settings_state::init_font()
{
    if (!this->font.loadFromFile("fonts/Lato-Bold.ttf")) {
        throw("ERROR IN SETTINGS_STATE : can not load font"); 
    }
}

void Settings_state::init_gui()
{
    this->buttons["EXIT"] = new gui::button(
        0.f, 0.f, 150.f, 50.f, &this->font,
       "BACK", 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200)
    );

    this->buttons["APPLY"] = new gui::button(
        800.f, 0.f, 250.f, 50.f, &this->font,
       "APPLY", 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200)
    );

    std::vector<std::string> modes_str;

    for(auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    
    this->drop_down_list["RESOLUTION"] = new gui::Drop_down_list(800, 200, 150, 50, font, modes_str.data(), modes_str.size());
}

void Settings_state::init_text()
{
    this->option_text.setFont(font);
    this->option_text.setPosition(sf::Vector2f(100.f, 450.f));
    this->option_text.setCharacterSize(30.f);
    this->option_text.setFillColor(sf::Color(255, 255, 255, 200));


    this->option_text.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n");
}

void Settings_state::init_variable()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}