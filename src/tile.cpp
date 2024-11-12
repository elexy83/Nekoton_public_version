#include "../include/stdafx.hpp"
#include "../include/tile.hpp"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float grid_size_f)
{
    this->shape.setSize(sf::Vector2f(grid_size_f, grid_size_f));
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setPosition(x, y);
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
