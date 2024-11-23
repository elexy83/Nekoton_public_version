#include "../include/stdafx.hpp"
#include "../include/tile_map.hpp"



Tile_map::Tile_map(float grid_size_f, unsigned width, unsigned height)
{
    this->grid_size_f = grid_size_f;
    this->grid_size_u = static_cast<unsigned>(this->grid_size_f);
    this->max_size.x = width;
    this->max_size.y = height;
    this->layers = 1;

    this->map.resize(this->max_size.x, std::vector<std::vector<Tile*>>());
    for (size_t x = 0; x < this->max_size.x; x++)
    {
        for (size_t y = 0; y < this->max_size.y; y++)
        {
            this->map[x].resize(this->max_size.y, std::vector<Tile*>());

            for (size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers, NULL);
            }
        }
    }
    if(!this->tile_sheet.loadFromFile("assets/Map01.png"))
        std::cout << "error tilemap failed to load tile_test.png" << std::endl;
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
                if (z != NULL)
                    z->render(target);
            }
        }
    }
}

void Tile_map::add_tile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect)
{
    if (x < this->max_size.x && x >= 0 &&
        y < this->max_size.y && y >= 0 &&
        z < layers && z >= 0)
    {
        if (this->map[x][y][z] == NULL)
        {
            this->map[x][y][z] = new Tile(x * this->grid_size_f, y * this->grid_size_f, this->grid_size_f, this->tile_sheet, texture_rect);
            std::cout << "DEBUG: ADDED TILE" << std::endl;
        }
    }
}

void Tile_map::remove_tile(const unsigned x, const unsigned y, const unsigned z)
{
    if (x < this->max_size.x && x >= 0 &&
        y < this->max_size.y && y >= 0 &&
        z < layers && z >= 0)
    {
        if (this->map[x][y][z]!= NULL)
        {
            delete this->map[x][y][z];
            this->map[x][y][z] = NULL;
            std::cout << "DEBUG: REMOVED TILE" << std::endl;
        }
    }
}

const sf::Texture *Tile_map::get_tile_sheet() const
{
    return &this->tile_sheet;
}
