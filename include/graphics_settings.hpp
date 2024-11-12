#ifndef GRAPHICS_SETTINGS_HPP
    #define GRAPHICS_SETTINGS_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>

class Graphics_settings
{
    public:

        Graphics_settings();

        sf::VideoMode resolution;
        bool fullscreen;
        bool vsync;
        unsigned framerate_limit;
        sf::ContextSettings context_settings;
        std::vector<sf::VideoMode> video_modes;
        std::string title;

        void save_to_file(const std::string path);
        void load_to_file(const std::string path);
       
};
#endif