#include "../include/stdafx.hpp"
#include "../include/hitbox_component.hpp"



Hitbox_component::Hitbox_component(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height) :
    sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
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

bool Hitbox_component::check_intersect(const sf::FloatRect& f_rect)
{
    return this->hitbox.getGlobalBounds().intersects(f_rect);
}
