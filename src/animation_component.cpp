#include "../include/stdafx.hpp"
#include "../include/animation_component.hpp"



Animation_component::Animation_component(sf::Sprite& sprite, sf::Texture& texture_sheet)
    :sprite(sprite), textureSheet(texture_sheet), last_animation(NULL), priority_animation(NULL)
{

}

Animation_component::~Animation_component()
{
    for (auto &i: this->animations)
    {
        delete i.second;
    }
} 

void Animation_component::add_animation(const std::string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
    this->animations[key] = new Animation(this->sprite, this->textureSheet, animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

const bool& Animation_component::play(const std::string key, const float &dt, const bool priority)
{
    if (this->priority_animation)
    {
        if (this->priority_animation == this->animations[key])
        {
            if (this->last_animation != this->animations[key])
            {
                if (this->last_animation == NULL)
                {
                    this->last_animation = this->animations[key];
                }
                else
                {
                    this->last_animation->reset();
                    this->last_animation = this->animations[key];
                }
            }

            if (this->animations[key]->play(dt))
            {
                this->priority_animation = NULL;
            }
        }
    }
    else
    {
        if (priority)
        {
            this->priority_animation = this->animations[key];
        }
        if (this->last_animation != this->animations[key])
        {
            if (this->last_animation == NULL)
            {
                this->last_animation = this->animations[key];
            }
            else
            {
                this->last_animation->reset();
                this->last_animation = this->animations[key];
            }
        }
        this->animations[key]->play(dt);
    }
    
    return this->animations[key]->is_done();
    
}

const bool& Animation_component::play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority)
{
    if (this->priority_animation)
    {
        if (this->priority_animation == this->animations[key])
        {
            if (this->last_animation != this->animations[key])
            {
                if (this->last_animation == NULL)
                {
                    this->last_animation = this->animations[key];
                }
                else
                {
                    this->last_animation->reset();
                    this->last_animation = this->animations[key];
                }
            }

            if (this->animations[key]->play(dt, abs(modifier/modifier_max)))
            {
                this->priority_animation = NULL;
            }
        }
    }
    else
    {
        if (priority)
        {
            this->priority_animation = this->animations[key];
        }
        if (this->last_animation != this->animations[key])
        {
            if (this->last_animation == NULL)
            {
                this->last_animation = this->animations[key];
            }
            else
            {
                this->last_animation->reset();
                this->last_animation = this->animations[key];
            }
        }
        this->animations[key]->play(dt, abs(modifier/modifier_max));
    }
    return this->animations[key]->is_done();
}

const bool& Animation_component::is_done(const std::string key)
{
    return this->animations[key]->is_done();
}
