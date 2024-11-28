#include "../include/stdafx.hpp"
#include "../include/tile_map.hpp"


Tile_map::Tile_map(float grid_size_f, unsigned width, unsigned height, std::string texture_file)
{
    this->grid_size_f = grid_size_f;
    this->grid_size_u = static_cast<unsigned>(this->grid_size_f);
    this->max_size_world_grid.x = width;
    this->max_size_world_grid.y = height;
    this->max_size_world.x = static_cast<float>(width) * grid_size_f;
    this->max_size_world.y = static_cast<float>(height) * grid_size_f;
    this->layers = 1;
    this->texture_file = texture_file;

    this->map.resize(this->max_size_world_grid.x, std::vector<std::vector<Tile*>>());
    for (size_t x = 0; x < this->max_size_world_grid.x; x++)
    {
        for (size_t y = 0; y < this->max_size_world_grid.y; y++)
        {
            this->map[x].resize(this->max_size_world_grid.y, std::vector<Tile*>());

            for (size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers, NULL);
            }
        }
    }
    if(!this->tile_sheet.loadFromFile(texture_file))
        std::cout << "error tilemap failed to load texturefile: " << texture_file << std::endl;

    this->collision_box.setSize(sf::Vector2f(grid_size_f, grid_size_f));
    this->collision_box.setFillColor(sf::Color(255,0,0,50));
    this->collision_box.setOutlineColor(sf::Color::Red);
    this->collision_box.setOutlineThickness(1.f);
}

Tile_map::~Tile_map()
{
    this->clear();
}

void Tile_map::update()
{

}

void Tile_map::render(sf::RenderTarget &target, entity* entity)
{
    for (auto &x : this->map)
    {
        for (auto &y : x)
        {
            for (auto *z : y)
            {
                if (z != NULL)
                {
                    z->render(target);
                    if (z->get_collision())
                    {
                        this->collision_box.setPosition(z->get_position());
                        target.draw(this->collision_box);
                    }
                    
                }
            }
        }
    }
}

void Tile_map::add_tile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect, const bool& collision, const short& type)
{
    if (x < this->max_size_world_grid.x && x >= 0 &&
        y < this->max_size_world_grid.y && y >= 0 &&
        z < layers && z >= 0)
    {
        if (this->map[x][y][z] == NULL)
        {
            this->map[x][y][z] = new Tile(x, y, this->grid_size_f, this->tile_sheet, texture_rect, collision, type);
            std::cout << "DEBUG: ADDED TILE" << std::endl;
        }
    }
}

void Tile_map::remove_tile(const unsigned x, const unsigned y, const unsigned z)
{
    if (x < this->max_size_world_grid.x && x >= 0 &&
        y < this->max_size_world_grid.y && y >= 0 &&
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

void Tile_map::save_to_file(const std::string file_name)
{

    /* format:

        basic:
        size x y
        grid_size
        layers
        texture_file

        all tiles:
        grid_pos x y layer, texture_rect x y, collision, type
    */

    std::ofstream out_file;

    out_file.open(file_name);

    if(out_file.is_open())
    {
        out_file <<this->max_size_world_grid.x << " " <<  this->max_size_world_grid.y << "\n"
        << this->grid_size_u << "\n"
        << this->layers << "\n"
        << this->texture_file << "\n";

        for (size_t x = 0; x < this->max_size_world_grid.x; x++)
        {
            for (size_t y = 0; y < this->max_size_world_grid.y; y++)
            {
                for (size_t z = 0; z < this->layers; z++)
                {
                    if (this->map[x][y][z])
                        out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->get_as_string() << " ";
                }
            }
        }
    }
    else
    {
        std::cout << "error: tilemap could not save to filename: " << file_name << std::endl; 
    }

    out_file.close();
}

void Tile_map::load_from_file(const std::string file_name)
{
    /* format:

        basic:
        size x y
        grid_size
        layers
        texture_file

        all tiles:
        grid_pos x y, texture_rect x y, collision, type
    */

    std::ifstream in_file;

    in_file.open(file_name);

    if(in_file.is_open())
    {
        sf::Vector2u size;
        unsigned grid_size = 0;
        unsigned layers = 0;
        std::string texture_file = "";
        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;
        unsigned tr_x = 0;
        unsigned tr_y = 0;
        bool collision = false;
        short type = 0;

        //basics
        in_file >> size.x >> size.y >> grid_size >> layers >> texture_file;
    
        //tiles
        this->grid_size_f = static_cast<float>(grid_size);
        this->grid_size_u = grid_size;
        this->max_size_world_grid.x = size.x;
        this->max_size_world_grid.y = size.y;
        this->layers = layers;
        this->texture_file = texture_file;

        this->clear();

        this->map.resize(this->max_size_world_grid.x, std::vector<std::vector<Tile*>>());
        for (size_t x = 0; x < this->max_size_world_grid.x; x++)
        {
            for (size_t y = 0; y < this->max_size_world_grid.y; y++)
            {
                this->map[x].resize(this->max_size_world_grid.y, std::vector<Tile*>());

                for (size_t z = 0; z < this->layers; z++)
                {
                    this->map[x][y].resize(this->layers, NULL);
                }
            }
        }
        if(!this->tile_sheet.loadFromFile(texture_file))
        {
            std::cout << "error tilemap failed to load texturefile: " << texture_file << std::endl;
        }

        //load all tiles
        while(in_file >> x >> y >> z >> tr_x >> tr_y >> collision >> type)
        {
            this->map[x][y][z] = new Tile(x, y, this->grid_size_f, this->tile_sheet, sf::IntRect(tr_x, tr_y, this->grid_size_u, this->grid_size_u), collision, type);
        }
    }
    else
    {
        std::cout << "error: tilemap could not load from filename: " << file_name << std::endl; 
    }

    in_file.close();
}

void Tile_map::update_collision(entity *entity)
{
    //world bounds
    if(entity->get_position().x < 0.f)
    {
        entity->set_position(0.f, entity->get_position().y);
    }
    else if(entity->get_position().x > this->max_size_world.x)
    {
        entity->set_position(this->max_size_world.x, entity->get_position().y);
    }
    if(entity->get_position().y < 0.f)
    {
        entity->set_position(entity->get_position().x, 0.f);
    }
    else if(entity->get_position().y > this->max_size_world.y)
    {
        entity->set_position(entity->get_position().x, this->max_size_world.y);
    }

    //tiles
    
}

void Tile_map::clear()
{
    for (size_t x = 0; x < this->max_size_world_grid.x; x++)
    {
        for (size_t y = 0; y < this->max_size_world_grid.y; y++)
        {
            for (size_t z = 0; z < this->layers; z++)
            {
                delete this->map[x][y][z];
                this->map[x][y][z] = NULL;
            }
            this->map[x][y].clear();
        }
        this->map[x].clear();
    }
    this->map.clear();
    //std::cout << this->map.size() << std::endl;
}
