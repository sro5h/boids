#ifndef BOID_H
#define BOID_H

#include "Types.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#define BOID_SIZE	10

namespace boids
{
class Boid
{
private:
	sf::Vector2f position;
	sf::Color color;

public:
	Boid(const sf::Vector2f& position, const sf::Color& color);
	~Boid();

	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition();
	void setColor(const sf::Color& color);

	void draw(sf::RenderTarget& target);
};
}

#endif // !BOID_H
