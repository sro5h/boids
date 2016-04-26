#include "Boid.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace boids
{
Boid::Boid(const sf::Vector2f& position, const sf::Color& color)
	: position(position), color(color)
{

}

Boid::~Boid()
{

}


void Boid::setPosition(const sf::Vector2f& position)
{
	this->position = position;
}

sf::Vector2f Boid::getPosition()
{
	return position;
}

void Boid::setColor(const sf::Color& color)
{
	this->color = color;
}


void Boid::draw(sf::RenderTarget& target)
{
	sf::CircleShape shape(BOID_SIZE);
	shape.setFillColor(color);
	shape.setPosition(position);
	target.draw(shape);
}
}