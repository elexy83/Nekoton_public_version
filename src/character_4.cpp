#include "../include/stdafx.hpp"
#include "../include/character_4.hpp"



character_4::character_4(float x, float y, sf::Texture &texture_sheet)
{
    this->init_variables();

    this->set_position(x, y);

    this->create_hitbox_component(this->sprite, 0.f, 0.f, 90.f, 90.f);
    this->create_movement_component(850.f, 800.f, 300.f);
    this->create_animation_component(texture_sheet);

    this->animation_component->add_animation("IDLE", 10.f, 0, 0, 0, 0, 90, 90);
    this->animation_component->add_animation("WALK", 5.f, 0, 0, 0, 0, 90, 90);
    this->animation_component->add_animation("ATTACK", 5.f, 0, 0, 3, 0, 90, 90);
}

character_4::~character_4()
{

}

void character_4::update(const float &dt)
{
    
    this->movement_component->update(dt);

    this->update_attack();

    this->update_animation(dt);
    
    this->hitbox_component->update(); 
}

void character_4::update_animation(const float &dt)
{
    if (this->attaking)
    {
        if(this->animation_component->play("ATTACK", dt, true))
            this->attaking = false;
    }
    if (this->movement_component->get_state(IDLE))
    {
        this->animation_component->play("IDLE", dt);
    }
    else if (this->movement_component->get_state(MOVING_LEFT))
    {
        this->sprite.setOrigin(90.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->animation_component->play("WALK", dt, this->movement_component->get_velocity().x, this->movement_component->get_max_velocity());
    }
    else if (this->movement_component->get_state(MOVING_RIGHT))
    {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animation_component->play("WALK", dt, this->movement_component->get_velocity().x, this->movement_component->get_max_velocity());
    }
    else if (this->movement_component->get_state(MOVING_UP))
    {
        this->animation_component->play("WALK", dt, this->movement_component->get_velocity().y, this->movement_component->get_max_velocity());
    }
    else if (this->movement_component->get_state(MOVING_DOWN))
    {
        this->animation_component->play("WALK", dt, this->movement_component->get_velocity().y, this->movement_component->get_max_velocity());
    }
}

void character_4::update_attack()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->attaking = true;
    }
}

void character_4::init_variables()
{
    this->attaking = false;
}

void character_4::init_component()
{

}