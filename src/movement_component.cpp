#include "../include/stdafx.hpp"
#include "../include/movement_component.hpp"

Movement_component::Movement_component(sf::Sprite& sprite, 
	float max_velocity, float acceleration, float deceleration)
	: sprite(sprite), max_velocity(max_velocity),
	acceleration(acceleration), deceleration(deceleration)
{

}


Movement_component::~Movement_component()
{
}


//Accessors

const float & Movement_component::get_max_velocity() const
{
	return this->max_velocity;
}

const sf::Vector2f & Movement_component::get_velocity() const
{
	return this->velocity;
}


//	Functions

const bool Movement_component::get_state(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	}
	return false;
}

void Movement_component::stop_velocity()
{
	/*	Resets the velocity to 0	*/
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void Movement_component::stop_velocity_x()
{
	/*	Resets the velocity X to 0	*/
	this->velocity.x = 0.f;
}

void Movement_component::stop_velocity_y()
{
	/*	Resets the velocity Y to 0	*/
	this->velocity.y = 0.f;
}

void Movement_component::move(const float dir_x, const float dir_y, const float& dt)
{
	//	Acceleration
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;
}

void Movement_component::update(const float & dt)
{
	//	Deceleration and max vel control
	if (this->velocity.x > 0.f) //	Check for positive x
	{	
		//	Max velocity check
		if (this->velocity.x > this->max_velocity) {
			this->velocity.x = this->max_velocity;
		}
		//	Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f) {
			this->velocity.x = 0;
		}
	}
	else if (this->velocity.x < 0.f) //	Check for negative x
	{	
		//	Max velocity check
		if (this->velocity.x < -this->max_velocity) {
			this->velocity.x = -this->max_velocity;
		}
		//	Deceleration x negative
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f) {
			this->velocity.x = 0;
		}
	}

	if (this->velocity.y > 0.f) //	Check for positive y
	{	
		//	Max velocity check
		if (this->velocity.y > this->max_velocity) {
			this->velocity.y = this->max_velocity;
		}
		//	Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f) {
			this->velocity.y = 0;
		}
	}
	else if (this->velocity.y < 0.f) //	Check for negative y
	{	
		//	Max velocity check
		if (this->velocity.y < -this->max_velocity) {
			this->velocity.y = -this->max_velocity;
		}
		//	Deceleration x negative
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f) {
			this->velocity.y = 0;
		}
	}

	//	Final move
	this->sprite.move(this->velocity * dt);	//	Uses velocity
}