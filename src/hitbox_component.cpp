#include "../include/stdafx.hpp"
#include "../include/hitbox_component.hpp"



Hitbox_component::Hitbox_component(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height) :
    sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    this->next_position.left = 0.f;
    this->next_position.top = 0.f;
    this->next_position.width = width;
    this->next_position.height = height;

    this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(-1.f);
    this->hitbox.setOutlineColor(sf::Color::Green);
}

Hitbox_component::~Hitbox_component()
{

}

void Hitbox_component::update()
{
    this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void Hitbox_component::render(sf::RenderTarget &target)
{
    target.draw(this->hitbox);
}

bool Hitbox_component::intersect(const sf::FloatRect& f_rect)
{
    return this->hitbox.getGlobalBounds().intersects(f_rect);
}

const sf::Vector2f &Hitbox_component::get_position() const
{
    return this->hitbox.getPosition();
}

const sf::FloatRect Hitbox_component::get_global_bounds() const
{
    return this->hitbox.getGlobalBounds();
}

const sf::FloatRect &Hitbox_component::get_next_position(const sf::Vector2f &velocity)
{
    this->next_position.left = this->hitbox.getPosition().x + velocity.x;
    this->next_position.top = this->hitbox.getPosition().y + velocity.y;
    
    return this->next_position;
}
void Hitbox_component::set_position(sf::Vector2f &position)
{
    this->hitbox.setPosition(position);
    this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void Hitbox_component::set_position(const float x, const float y)
{
    this->hitbox.setPosition(x, y);
    this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}
