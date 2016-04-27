#ifndef BOID_H
#define BOID_H

#include "Types.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace boids
{
class Boid
{
public:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Color color;
	float size;

	Boid(const sf::Vector2f& position, float size = 20);
	~Boid();
};
}

#endif // !BOID_H
