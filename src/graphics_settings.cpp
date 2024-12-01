#include "../include/stdafx.hpp"
#include "../include/graphics_settings.hpp"


Graphics_settings::Graphics_settings()
{
    this->title = "DEFAULT";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->vsync = false;
    this->framerate_limit = 500;
    this->context_settings.antialiasingLevel = 0;
    this->video_modes = sf::VideoMode::getFullscreenModes();
}

void Graphics_settings::save_to_file(const std::string path)
{
    std::ofstream ofs;
    ofs.open(path);

    if (ofs.is_open()) 
    {
        ofs << this->title;
        ofs << this->resolution.width;
        ofs << this->resolution.height;
        ofs << this->fullscreen;
        ofs << this->framerate_limit;
        ofs << this->vsync;
        ofs << this->context_settings.antialiasingLevel;
    }
    else
    {
        std::cerr << "Erreur: impossible d'ouvrir le fichier de configuration Config/graphics" << std::endl;
        exit(EXIT_FAILURE);
    }
    ofs.close();
}

void Graphics_settings::load_to_file(const std::string path)
{
    std::ifstream ifs;
    ifs.open(path);
   
    if (ifs.is_open())
    {
        std::getline(ifs, this->title);
        ifs >> this->resolution.width;
        ifs >> this->resolution.height;
        ifs >> this->fullscreen;
        ifs >> this->framerate_limit;
        ifs >> this->vsync;
        ifs >> this->context_settings.antialiasingLevel;
    }
    else
    {
        std::cerr << "Erreur: impossible d'ouvrir le fichier de configuration Config/window" << std::endl;
        exit(EXIT_FAILURE);
    }
    ifs.close();
}
