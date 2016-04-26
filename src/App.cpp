#include "App.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <random>

namespace boids
{
App::App(uint16 width, uint16 height)
	: width(width), height(height)
{
	window.create(sf::VideoMode(width + 2*MARGIN, height + 2*MARGIN), "Boids v0.1");
}

App::~App()
{

}


void App::addBoid()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	//std::uniform_real_distribution<float> sizedist(7, 15);
	//float size = sizedist(mt);
	float size = 10;
	std::uniform_real_distribution<float> xdist(MARGIN, width - size);
	std::uniform_real_distribution<float> ydist(MARGIN, height - size);
	std::uniform_int_distribution<int> colordist(0, 255);

	boids.push_back(Boid(sf::Vector2f(xdist(mt), ydist(mt)), sf::Color(colordist(mt), colordist(mt), colordist(mt))/*, size*/));
}

void App::addBoid(const sf::Vector2f& position)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	//std::uniform_real_distribution<float> sizedist(7, 15);
	//float size = sizedist(mt);
	std::uniform_int_distribution<int> colordist(0, 255);

	boids.push_back(Boid(position, sf::Color(colordist(mt), colordist(mt), colordist(mt))/*, size*/));
}


void App::handleEvent(sf::Event& ev)
{
	if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::A)
	{
		addBoid();
	}
	else if(ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
	{
		addBoid(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y)));
	}
}

void App::update(float dt)
{
	std::cout << "FPS: " << 1/dt << std::endl;
}

void App::draw()
{
	// Draw bounds
	{
		sf::Vertex bounds[] =
		{
			sf::Vertex(sf::Vector2f(MARGIN, MARGIN), sf::Color::White),
			sf::Vertex(sf::Vector2f(static_cast<float>(width) + MARGIN, MARGIN), sf::Color::White),
			sf::Vertex(sf::Vector2f(static_cast<float>(width) + MARGIN, static_cast<float>(height) + MARGIN), sf::Color::White),
			sf::Vertex(sf::Vector2f(MARGIN, static_cast<float>(height) + MARGIN), sf::Color::White),
			sf::Vertex(sf::Vector2f(MARGIN, MARGIN), sf::Color::White)
		};
		window.draw(bounds, 5, sf::LinesStrip);
	}

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