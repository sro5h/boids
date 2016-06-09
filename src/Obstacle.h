#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Types.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace boids
{
class Obstacle
{
public:
	sf::Vector2f position;
	sf::Color color;
	float size;

	Obstacle(const sf::Vector2f& position, float size = 50);
	~Obstacle();

};
}

#endif // !OBSTACLE_H
