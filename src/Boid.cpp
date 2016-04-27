#include "Boid.h"
#include <math.h>

namespace boids
{
Boid::Boid(const sf::Vector2f& position, float size)
	: position(position), size(size), velocity(0.0f, 0.0f)
{
	color = sf::Color(52, 152, 219);
}

Boid::~Boid()
{

}


//void Boid::draw(sf::RenderTarget& target)
//{
//	sf::CircleShape shape(size*0.5f, 3);
//	shape.setOrigin(size*0.5f, size*0.5f);
//	float rad = std::atan2f(velocity.y, velocity.x) + PI/2;
//	shape.setRotation(static_cast<float>(rad_to_deg(rad)));
//	shape.setFillColor(color);
//	shape.setPosition(position);
//
//	/*sf::Vertex line[] =
//	{
//		sf::Vertex(position, sf::Color::Green),
//		sf::Vertex(position + velocity, sf::Color::Green)
//	};
//
//	sf::RectangleShape line2(sf::Vector2f(1, 30));
//	line2.setPosition(position);
//	line2.setRotation(static_cast<float>(rad_to_deg(rad)));*/
//
//	target.draw(shape);
//	/*target.draw(line, 2, sf::Lines);
//	target.draw(line2);*/
//}
}