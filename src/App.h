#ifndef APP_H
#define APP_H

#include "Types.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace boids
{
class App
{
private:
	sf::RenderWindow window;

	void handleEvent(sf::Event& ev);
	void update(float dt);

public:
	App(uint16 width, uint16 height);
	~App();

	int run();
};
}

#endif // !APP_H
