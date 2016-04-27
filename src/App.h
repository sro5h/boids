#ifndef APP_H
#define APP_H

#include "Types.h"
#include "Boid.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

namespace boids
{
class App
{
private:
	uint16 width;
	uint16 height;
	float worldwidth;
	float worldheight;
	sf::RenderWindow window;
	std::vector<Boid*> boidslist;

	void addBoid();
	void addBoid(const sf::Vector2f& position);

	sf::Vector2f rule1(Boid* b);
	sf::Vector2f rule2(Boid* b);
	sf::Vector2f rule3(Boid* b);

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
