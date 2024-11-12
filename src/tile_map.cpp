#include "../include/stdafx.hpp"
#include "../include/tile_map.hpp"


Tile_map::Tile_map(float grid_size_f, unsigned width, unsigned height)
{
    this->grid_size_f = grid_size_f;
    this->grid_size_u = static_cast<unsigned>(this->grid_size_f);
    this->max_size.x = width;
    this->max_size.y = height;
    this->layers = 1;

    this->map.resize(this->max_size.x);
    for (size_t x = 0; x < this->max_size.x; x++)
    {
        this->map.push_back(std::vector<std::vector<Tile*>>());

        for (size_t y = 0; y < this->max_size.y; y++)
        {
            this->map[x].resize(this->max_size.y);
            this->map[x].push_back(std::vector<Tile*>());

            for (size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers);
                this->map[x][y].push_back(nullptr);
            }
        }
    }
}

Tile_map::~Tile_map()
{
    for (size_t x = 0; x < this->max_size.x; x++)
    {
        for (size_t y = 0; y < this->max_size.y; y++)
        {
            for (size_t z = 0; z < this->layers; z++)
            {
                delete this->map[x][y][z];
            }
        }
    }
}

void Tile_map::update()
{

}

void Tile_map::render(sf::RenderTarget &target)
{
    for (auto &x : this->map)
    {
        for (auto &y : x)
        {
            for (auto *z : y)
            {
                if (z != nullptr)
                    z->render(target);
            }
        }
    }
}

void Tile_map::add_tile()
{

}

void Tile_map::remove_tile()
{

}
