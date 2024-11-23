#ifndef ANIMATION_COMPONENT_HPP
    #define ANIMATION_COMPONENT_HPP   

    class Animation_component
    {
        public:

            Animation_component(sf::Sprite& sprite, sf::Texture& texture_sheet);
            ~Animation_component();

            void add_animation(const std::string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

             
            const bool& play(const std::string key, const float &dt, const bool priority = false);
            const bool& play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority = false);

            const bool& is_done(const std::string key);
        private:

            class Animation
            {
                public:
                    Animation(sf::Sprite &sprite, sf::Texture &texture_sheet, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
                        : sprite(sprite) ,textureSheet(texture_sheet), animationTimer(animation_timer), timer(0.f), done(false), width(width), height(height)
                    {
                        this->start_rect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
                        this->current_rect = this->start_rect;
                        this->end_rect = sf::IntRect(frames_x * width, frames_y * height, width, height);

                        this->sprite.setTexture(this->textureSheet, true);
                        this->sprite.setTextureRect(this->start_rect);
                    }

                    const bool& play(const float &dt)
                    {
                        this->done = false;
                        this->timer += 100.f * dt;
                        if (this->timer >= this->animationTimer)
                        {

                            this->timer = 0.f;

                            if (this->current_rect != this->end_rect)
                            {
                                this->current_rect.left += this->width;
                            } 
                            else 
                            {
                                this->current_rect.left = this->start_rect.left;
                                this->done = true;
                            }

                            this->sprite.setTextureRect(this->current_rect);
                        }
                        return this->done;
                    }

                    const bool& play(const float &dt, float mod_percent)
                    {
                        
                        if(mod_percent < 0.5f)
                        {
                            mod_percent = 0.5f;
                        }
                        this->done = false;
                        this->timer += mod_percent * 100.f * dt;
                        if (this->timer >= this->animationTimer)
                        {
                            
                            this->timer = 0.f;
                            if (this->current_rect != this->end_rect)
                            {
                                this->current_rect.left += this->width;
                            } 
                            else 
                            {
                                this->current_rect.left = this->start_rect.left;
                                this->done = true;
                            }

                            this->sprite.setTextureRect(this->current_rect);
                        }
                        return this->done;
                    }
                    
                    void reset()
                    {
                        this->timer = this->animationTimer;
                        this->current_rect = this->start_rect;
                    }

                    const bool& is_done() const
                    {
                     return this->done;
                    }

                    sf::Texture &textureSheet;
                    sf::Sprite& sprite;
                    float animationTimer;
                    float timer;
                    bool done;
                    int width;
                    int height;
                    sf::IntRect start_rect;
                    sf::IntRect end_rect;
                    sf::IntRect current_rect;

            };

            sf::Sprite &sprite;
            sf::Texture &textureSheet;
            std::map<std::string, Animation*> animations;
            Animation* last_animation;
            Animation* priority_animation;
    };

#endif