#include "../include/stdafx.hpp"
#include "../include/state.hpp"

state::state(State_data* state_data)
{
    this->state_data = state_data;
    this->window = state_data->window;
    this->supported_keys = state_data->supported_keys;
    this->states = state_data->states;
    this->quit = false;
    this->paused = false;
    this->key_time = 0.f;
    this->key_time_max = 10.f;
    this->grid_size = state_data->grid_size;
}

state::~state()
{

}

const bool &state::get_quit() const
{
    return this->quit;
}

const bool state::get_key_time()
{
    if (this->key_time >= this->key_time_max)
    {
        this->key_time = 0.f;
        return true;
    }
    return false;
}

void state::update_mouse_position()
{
    this->mouse_pose_screen = sf::Mouse::getPosition();
    this->mouse_pose_window = sf::Mouse::getPosition(*this->window);
    this->mouse_pose_view = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    this->mouse_pos_grid = sf::Vector2u(
        static_cast<unsigned>(this->mouse_pose_view.x) / static_cast<unsigned>(this->grid_size),
        static_cast<unsigned>(this->mouse_pose_view.y) / static_cast<unsigned>(this->grid_size)
    );
}

void state::end_state()
{
    this->quit = true;
}

void state::pause_state()
{
    this->paused = true;
}

void state::unpaused_state()
{
    this->paused = false;
}

void state::update_key_time(const float &dt)
{
    if (this->key_time < this->key_time_max)
    {
        this->key_time += 60.f * dt;
    }
}
