#include "../include/stdafx.hpp"
#include "../include/movement_component.hpp"





Movement_component::Movement_component(sf::Sprite &sprite, float max_velocity, float acceleration, float deceleration)
    :sprite(sprite), max_velocity(max_velocity), acceleration(acceleration), deceleration(deceleration)
{
    this->max_velocity = max_velocity;
   
}

Movement_component::~Movement_component()
{

}

const bool Movement_component::get_state(const short unsigned state) const
{
    switch (state)
    {

    case IDLE:

        if (this->velocity.x == 0.f && this->velocity.y == 0.f)
            return true;

        break;

    case MOVING:
        
        if (this->velocity.x != 0.f || this->velocity.y != 0.f)
            return true;

        break;

    case MOVING_LEFT:

        if (this->velocity.x < 0.f)
            return true;

        break;

    case MOVING_RIGHT:

        if (this->velocity.x > 0.f)
            return true;

        break;

    case MOVING_DOWN:

        if (this->velocity.y > 0.f)
            return true;

        break;

    case MOVING_UP:
        
        if (this->velocity.y < 0.f)
            return true;
        
        break;
    }
    return false;
}

void Movement_component::stop_velocity()
{
    // reset the velocity to 0

    this->velocity.x = 0.f;
    this->velocity.y = 0.f;
}

void Movement_component::stop_velocity_x()
{
    // reset the velocity x to 0
    this->velocity.x = 0.f;
}

void Movement_component::stop_velocity_y()
{
    // reset the velocity y to 0
    this->velocity.y = 0.f;
}

void Movement_component::update(const float &dt)
{

    if (this->velocity.x > 0.f)
    {

        if (this->velocity.x > this->max_velocity)
            this->velocity.x = this->max_velocity;

        

        this->velocity.x -= deceleration;
        if (this->velocity.x < 0.f)
            this->velocity.x = 0.f;

    }
    else if(this->velocity.x < 0.f)
    {

        if (this->velocity.x < -this->max_velocity)
            this->velocity.x = -this->max_velocity;
        
        this->velocity.x += deceleration;
        if (this->velocity.x > 0.f)
            this->velocity.x = 0.f; 
    }


    if (this->velocity.y > 0.f)
    {

        if (this->velocity.y > this->max_velocity)
            this->velocity.y = this->max_velocity;

        

        this->velocity.y -= deceleration;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0.f;

    }
    else if(this->velocity.y < 0.f)
    {

        if (this->velocity.y < -this->max_velocity)
            this->velocity.y = -this->max_velocity;
        
        this->velocity.y += deceleration;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0.f;
    }


    this->sprite.move(this->velocity * dt);
}

void Movement_component::move(const float dir_x, const float dir_y, const float &dt)
{
 
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

const sf::Vector2f &Movement_component::get_velocity() const
{
    return this->velocity;
}

const float &Movement_component::get_max_velocity() const
{
    return this->max_velocity;
}