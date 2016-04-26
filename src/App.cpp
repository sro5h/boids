#include "App.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <random>

namespace boids
{
App::App(uint16 width, uint16 height)
	: width(width), height(height)
{
	window.create(sf::VideoMode(width, height), "Boids v0.1");

	boids.push_back(Boid(sf::Vector2f(30, 30), sf::Color::Cyan));
}

App::~App()
{

}


void App::addBoid()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> xdist(0, width);
	std::uniform_real_distribution<float> ydist(0, height);
	std::uniform_int_distribution<int> colordist(0, 255);

	boids.push_back(Boid(sf::Vector2f(xdist(mt), ydist(mt)), sf::Color(colordist(mt), colordist(mt), colordist(mt))));
}

void App::addBoid(const sf::Vector2f& position)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> colordist(0, 255);

	boids.push_back(Boid(position, sf::Color(colordist(mt), colordist(mt), colordist(mt))));
}


void App::handleEvent(sf::Event& ev)
{
	if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::A)
		addBoid();
}

void App::update(float dt)
{
	std::cout << "FPS: " << 1/dt << std::endl;
}

void App::draw()
{
	for(auto& boid : boids)
	{
		boid.draw(window);
	}
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
		draw();
		window.display();
	}

	return 0;
}
}