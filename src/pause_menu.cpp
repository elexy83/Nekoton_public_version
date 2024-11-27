#include "../include/stdafx.hpp"
#include "../include/pause_menu.hpp"


Pause_menu::Pause_menu(sf::RenderWindow &window, sf::Font &font) : font(font)
{
    this->background.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)
        )
    );
    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    this->container.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / 4.f,
            static_cast<float>(window.getSize().y) -60.f
        )
    );
    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 30.f);

    this->menu_text.setFont(font);
    this->menu_text.setFillColor(sf::Color(255,255,255,200));
    this->menu_text.setCharacterSize(60);
    this->menu_text.setString("PAUSED");
    this->menu_text.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.f - this->menu_text.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 40.f
    );
}

Pause_menu::~Pause_menu()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); it++) {
        delete it->second;
    }
}

void Pause_menu::update(const sf::Vector2i& mouse_pos_window)
{
    for (auto &i : this->buttons)
        i.second->update(mouse_pos_window);
}

void Pause_menu::render(sf::RenderTarget &target)
{
    target.draw(this->background);
    target.draw(this->container);
    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target.draw(this->menu_text);
}

void Pause_menu::add_button(const std::string key, float y, const std::string text)
{
    float width = 250.f;
    float height = 50.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
    this->buttons[key] = new gui::button(
        x, y, width, height, &this->font,
        text, 30, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200)
    );
}

const bool Pause_menu::is_button_pressed(const std::string key)
{
    return this->buttons[key]->is_pressed();
}

std::map<std::string, gui::button *> &Pause_menu::get_buttons()
{
    return this->buttons;
}
