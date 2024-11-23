#include "../include/stdafx.hpp"
#include "../include/game.hpp"
#include "../include/main_menu_state.hpp"

game::game()
{
    this->init_variables();
    this->init_graphics_settings();
    this->init_window();
    this->init_keys();
    this->init_state_data();
    this->init_states();
}

game::~game()
{
    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}



const bool game::runnnig()
{
    return this->window->isOpen();
}

void game::update()
{
    this->poll_events();

    if (!this->states.empty()) {
        this->states.top()->update(this->dt);

        if (this->states.top()->get_quit()) {
            this->states.top()->end_state();
            delete this->states.top();
            this->states.pop();
        }
        
    } else {
        this->window->close();
    }
}

void game::update_dt()
{
    this->dt = this->dt_clock.restart().asSeconds();
}

void game::render()
{
    
    this->window->clear(sf::Color::Black);

    if (!this->states.empty()) {
        this->states.top()->render();
    }
    
    this->window->display();
}


void game::poll_events()
{
    while(this->window->pollEvent(this->event)) {
        switch (this->event.type) 
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            default:
                break;
        }
    }
}

void game::init_variables() 
{
    this->window = nullptr;
    this->dt = 0.f;
    this->grid_size = 32.f;
}

void game::init_graphics_settings()
{
    this->gfx_settings.load_to_file("Config/graphics");
}

void game::init_state_data()
{
    this->state_data.window = this->window;
    this->state_data.gfx_settings = &this->gfx_settings;
    this->state_data.supported_keys = &this->supported_keys;
    this->state_data.states = &this->states;
    this->state_data.grid_size = this->grid_size;
}

void game::init_window()
{
    
    if (this->gfx_settings.fullscreen)
        this->window = new sf::RenderWindow(this->gfx_settings.resolution, this->gfx_settings.title, sf::Style::Fullscreen, this->gfx_settings.context_settings);
    else 
        this->window = new sf::RenderWindow(this->gfx_settings.resolution, this->gfx_settings.title, sf::Style::Titlebar |sf::Style::Resize | sf::Style::Close, this->gfx_settings.context_settings);

    this->window->setFramerateLimit(this->gfx_settings.framerate_limit);
    this->window->setVerticalSyncEnabled(this->gfx_settings.vsync);
}

void game::init_keys()
{
    std::ifstream ifs;
    ifs.open("Config/supported_keys");

    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value) {
            this->supported_keys[key] = key_value;
        }
    }
    ifs.close();
}

void game::init_states()
{
    this->states.push(new main_menu_state(&this->state_data));
}
