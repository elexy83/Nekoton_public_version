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
   
    target.draw(this->sprite);

    if (this->hitbox_component)
        this->hitbox_component->render(target);

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

void entity::set_position(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}
