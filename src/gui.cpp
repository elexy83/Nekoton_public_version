#include "../include/stdafx.hpp"
#include "../include/gui.hpp"




gui::button::button(float x, float y, float width, float height,
    sf::Font *font, std::string text, float text_size,
    sf::Color idle_color, sf::Color hover_color, sf::Color active_color, short unsigned id)
{

    this->button_state = Btn_idle;
    this->id = id;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(text_size);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width /2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height /2.f
    );

    this->idle_color = idle_color;
    this->hover_color = hover_color;
    this->active_color = active_color;

    this->shape.setFillColor(this->idle_color);
} 

gui::button::~button()
{

}

void gui::button::update(const sf::Vector2i &mouse_pos_window)
{
    this->button_state = Btn_idle;
    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window))) {
        this->button_state = Btn_hover;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->button_state = Btn_active;
        }
    }
    
    switch (this->button_state)
    {
    case Btn_idle:
        this->shape.setFillColor(this->idle_color);
        break;
    case Btn_hover:
        this->shape.setFillColor(this->hover_color);
        break;
    case Btn_active:
        this->shape.setFillColor(this->active_color);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}

const bool gui::button::is_pressed()
{
    if (this->button_state == Btn_active)
        return true;
    return false;
}

const std::string gui::button::get_text() const
{
    return this->text.getString();
}

const short unsigned &gui::button::get_id() const
{
   return this->id;
}



void gui::button::set_text(const std::string text)
{
    this->text.setString(text);
}

void gui::button::set_id(const short unsigned id)
{
    this->id = id;
}
void gui::button::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
    target.draw(this->text);
}










//===================================================================================

gui::Drop_down_list::Drop_down_list(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nb_element, unsigned default_index)
    : font(font), show_list(false), key_time_max(10.f), key_time(0.f)
{
    //unsigned nb_element = sizeof(list) / sizeof(std::string);

     this->active_element = new gui::button(x, y, width, height, &this->font,
            list[default_index], 15, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200));

    for (size_t i = 0; i < nb_element; i++)
    {
        this->list.push_back(
            new gui::button(x, y + ((i+1) * height), width, height, &this->font,
            list[i], 15, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200), i)
        );
    }
}

gui::Drop_down_list::~Drop_down_list()
{
    delete this->active_element;
    for (size_t i = 0; i < this->list.size(); i++)
    {
       delete this->list[i];
    }
    
}

void gui::Drop_down_list::render(sf::RenderTarget &target)
{
    this->active_element->render(target);

    if (this->show_list)
    {
        for(auto &i : this->list)
        {
            i->render(target);
        }
    }
}

void gui::Drop_down_list::update(const sf::Vector2i &mouse_pos_window, const float& dt)
{
    this->update_key_time(dt);

    this->active_element->update(mouse_pos_window);
    if (this->active_element->is_pressed() && this->get_key_time())
    {
        if (this->show_list)
        {
            this->show_list = false;
        }
        else   
            this->show_list = true;
    }

    if(this->show_list)
    {
        for(auto &i : this->list)
        {
            i->update(mouse_pos_window);

            if (i->is_pressed() && this->get_key_time())
            {
                this->show_list = false;
                this->active_element->set_text(i->get_text());
                this->active_element->set_id(i->get_id());
            }
        }
    }
}

const bool gui::Drop_down_list::get_key_time()
{
    if (this->key_time >= this->key_time_max)
    {
        this->key_time = 0.f;
        return true;
    }
    return false;
}

const unsigned short &gui::Drop_down_list::get_active_element_id()
{
    return this->active_element->get_id();
}

void gui::Drop_down_list::update_key_time(const float &dt)
{
    if (this->key_time < this->key_time_max)
        this->key_time += 60.f * dt;
}











//===================================================================================

gui::Texture_selector::Texture_selector(float x, float y, float width, float height, float grid_size, const sf::Texture *texture_sheet, sf::Font &font, std::string text)
    : key_time_max(10.f), key_time(0.f)
{
    this->grid_size = grid_size;
    this->active = false;
    this->hidden = false;
    float offset = 60.f;

    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(x, y);
    this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    this->sheet.setTexture(*texture_sheet);
    this->sheet.setPosition(x, y);

    if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
    {
        this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
    }

    if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
    {
        this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().height, this->sheet.getGlobalBounds().width));
    }

    this->selector.setPosition(x, y);
    this->selector.setSize(sf::Vector2f(grid_size, grid_size));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Blue);

    this->texture_rect.width = static_cast<int>(grid_size);
    this->texture_rect.height = static_cast<int>(grid_size);

    this->hide_btn = new gui::button(
        20.f, 20.f, 50.f, 50.f, &font,
       text, 25, sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200)
    );
}

gui::Texture_selector::~Texture_selector()
{
    delete this->hide_btn;
}

void gui::Texture_selector::update(const sf::Vector2i& mouse_pos_window, const float& dt)
{
    this->update_key_time(dt);
    this->hide_btn->update(mouse_pos_window);

    if (this->hide_btn->is_pressed() && this->get_key_time())
    {
        if (this->hidden)
        {
            this->hidden = false;
        } else {
            this->hidden = true;
        }
    }

    if (!this->hidden)
    {
        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window)))
            this->active = true;
        else
            this->active = false;

        
        if (this->active)
        {
            this->mouse_pos_grid.x = (mouse_pos_window.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->grid_size);
            this->mouse_pos_grid.y = (mouse_pos_window.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->grid_size);
            this->selector.setPosition(
                this->bounds.getPosition().x + this->mouse_pos_grid.x * this->grid_size,
                this->bounds.getPosition().y + this->mouse_pos_grid.y * this->grid_size);

            this->texture_rect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
            this->texture_rect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
        }
    }
}

void gui::Texture_selector::render(sf::RenderTarget &target)
{

    if(!this->hidden)
    {
        target.draw(this->bounds);
        target.draw(this->sheet);

        if (this->active)
            target.draw(this->selector);
    }
    this->hide_btn->render(target);
}

const bool &gui::Texture_selector::get_active() const
{
    return this->active;
}

const sf::IntRect &gui::Texture_selector::get_texture_rect() const
{
    return this->texture_rect;
}

void gui::Texture_selector::update_key_time(const float &dt)
{
    if (this->key_time < this->key_time_max)
        this->key_time += 50.f * dt;
}

const bool gui::Texture_selector::get_key_time()
{
    if (this->key_time >= this->key_time_max)
    {
        this->key_time = 0.f;
        return true;
    }
    return false;
}