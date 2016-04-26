#include "App.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

namespace boids
{
App::App(uint16 width, uint16 height)
{
	window.create(sf::VideoMode(width, height), "Boids v0.1");
}

App::~App()
{

}


void App::handleEvent(sf::Event& ev)
{

}

void App::update(float dt)
{
	std::cout << "FPS: " << 1/dt << std::endl;
}


int App::run()
{
	sf::Clock frame_clock;
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();

			handleEvent(event);
		}

		float dt = frame_clock.restart().asSeconds();
		update(dt);

		window.clear(sf::Color(17, 17, 17));
		window.display();
	}

	return 0;
}
}