#include "../include/stdafx.hpp"
#include "../include/entity.hpp"





entity::entity()
{
    this->init_variables();
}

entity::~entity()
{
    delete this->movement_component;
    delete this->animation_component;
    delete this->hitbox_component;
}

void entity::update(const float &dt)
{
    if (this->movement_component)
        this->movement_component->update(dt);
}

void entity::render(sf::RenderTarget &target)
{

}

void entity::init_variables()
{
    this->movement_component = NULL;
    this->animation_component = NULL;
    this->hitbox_component = NULL;
}

void entity::move(const float &dt, const float dir_x, const float dir_y)
{
    
    if (this->movement_component)
    {
        this->movement_component->move(dir_x, dir_y, dt);
    }
}

void entity::stop_velocity()
{
    if (this->movement_component)
    this->movement_component->stop_velocity();
}

void entity::stop_velocity_x()
{
    if (this->movement_component)
        this->movement_component->stop_velocity_x();
}

void entity::stop_velocity_y()
{
    if (this->movement_component)
        this->movement_component->stop_velocity_y();
}  

void entity::set_texture(sf::Texture &texture)
{
    this->sprite.setTexture(texture);
}

void entity::create_movement_component(const float max_velocity, const float acceleration, const float deceleration)
{
    this->movement_component = new Movement_component(this->sprite, max_velocity, acceleration, deceleration);
}

void entity::create_animation_component(sf::Texture &texture_sheet)
{
    this->animation_component = new Animation_component(this->sprite, texture_sheet);
}

void entity::create_hitbox_component(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height)
{
    this->hitbox_component = new Hitbox_component(sprite, offset_x, offset_y, width, height);
}

const sf::Vector2f &entity::get_position() const
{
    if (this->hitbox_component)
    {
        return this->hitbox_component->get_position();
    }

    return this->sprite.getPosition();
}

const sf::FloatRect entity::get_global_bounds() const
{
    if(this->hitbox_component)
        return this->hitbox_component->get_global_bounds();
    return this->sprite.getGlobalBounds();
}

const sf::Vector2i entity::get_grid_position(const int grid_size_i) const
{
    if(this->hitbox_component)
    {
        return sf::Vector2i(
            static_cast<int>(this->hitbox_component->get_position().x) / grid_size_i,
            static_cast<int>(this->hitbox_component->get_position().y) / grid_size_i);
    }
    return sf::Vector2i(
        static_cast<int>(this->sprite.getPosition().x) / grid_size_i,
        static_cast<int>(this->sprite.getPosition().y) / grid_size_i);
}

const sf::FloatRect entity::get_next_position_bounds(const float &dt) const
{
    if(this->hitbox_component && this->movement_component)
    {
        return this->hitbox_component->get_next_position(this->movement_component->get_velocity() * dt);
    }
    return sf::FloatRect(-1.f,-1.f,-1.f,-1.f);
}

void entity::set_position(const float x, const float y)
{
    if (this->hitbox_component)
    {
        this->hitbox_component->set_position(x, y);
    }
    else
    {
        this->sprite.setPosition(x, y);
    }
}
