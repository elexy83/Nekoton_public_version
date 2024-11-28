#include "../include/stdafx.hpp"
#include "../include/tile.hpp"



Tile::Tile()
{
    this->collision = false;
    this->type = 0;

}

Tile::Tile(unsigned grid_x, unsigned grid_y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collision, short type)
{
    this->shape.setSize(sf::Vector2f(grid_size_f, grid_size_f));
    this->shape.setFillColor(sf::Color::White);
   // this->shape.setOutlineThickness(1.f);
   // this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setPosition(static_cast<float>(grid_x) * grid_size_f, static_cast<float>(grid_y) * grid_size_f);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(texture_rect);
    

    this->collision = collision;
    this->type = type;
}

Tile::~Tile()
{

}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}

const std::string Tile::get_as_string() const
{

    std::stringstream ss;

    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;
    return ss.str();
}

const sf::Vector2f &Tile::get_position() const
{
    return this->shape.getPosition();
}

const bool &Tile::get_collision() const
{
    return this->collision;
}