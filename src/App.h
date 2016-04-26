#ifndef APP_H
#define APP_H

#include "Types.h"
#include "Boid.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#define MARGIN 10

namespace boids
{
class App
{
private:
	uint16 width;
	uint16 height;
	sf::RenderWindow window;
	std::vector<Boid> boids;

	void addBoid();
	void addBoid(const sf::Vector2f& position);

	void handleEvent(sf::Event& ev);
	void update(float dt);
	void draw();

public:
	App(uint16 width, uint16 height);
	~App();

	int run();
};
}

#endif // !APP_H
