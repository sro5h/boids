#include "App.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <random>

namespace boids
{
App::App(uint16 width, uint16 height)
	: width(width), height(height), worldwidth(width*0.5f), worldheight(height*0.5f)
{
	window.create(sf::VideoMode(width, height), "Boids v0.1", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings());
	sf::View view;
	view.reset(sf::FloatRect(-worldwidth, -worldheight, width, height));
	/*view.setViewport(sf::FloatRect(1.0f, 1.0f, 1.0f, 1.0f));*/
	window.setView(view);

	addBoid(sf::Vector2f(0, 0));
}

App::~App()
{
	while(boidslist.size() > 0)
	{
		if(boidslist.back() != nullptr)
			delete boidslist.back();
		boidslist.pop_back();
	}
}


void App::addBoid()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	float size = 20;
	std::uniform_real_distribution<float> xdist(-worldwidth + size, worldwidth - size);
	std::uniform_real_distribution<float> ydist(-worldheight + size, worldheight - size);

	boidslist.push_back(new Boid(sf::Vector2f(xdist(mt), ydist(mt))));
}

void App::addBoid(const sf::Vector2f& position)
{
	std::random_device rd;
	std::mt19937 mt(rd());


	boidslist.push_back(new Boid(position));
}


sf::Vector2f App::rule1(Boid* b)
{
	sf::Vector2f center(0.0f, 0.0f);

	for(auto& boid : boidslist)
	{
		if(boid != b)
		{
			center = center + boid->position;
		}
	}
	if(boidslist.size() > 1)
		center = center * (1.f/(boidslist.size()-1.f));
	return (center - b->position) * (1.f/100.f);
}


void App::handleEvent(sf::Event& ev)
{
	if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::A)
	{
		addBoid();
	}
	else if(ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
	{
		addBoid(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x - worldwidth), static_cast<float>(sf::Mouse::getPosition(window).y - worldheight)));
	}
}

void App::update(float dt)
{
	sf::Vector2f v1, v2, v3;

	for(auto& boid : boidslist)
	{
		v1 = rule1(boid);
		/*
		v2 = rule2(boid);
		v3 = rule3(boid);
		*/

		boid->velocity = boid->velocity + v1 /*+ v2 + v3*/;
		boid->position = boid->position + (boid->velocity * dt);
	}

	std::cout << "FPS: " << 1/dt << std::endl;
}

void App::draw()
{
	for(auto& boid : boidslist)
	{
		float size = boid->size;
		sf::Vector2f velocity = boid->velocity;
		sf::Vector2f position = boid->position;

		sf::CircleShape shape(size*0.5f, 3);
		shape.setOrigin(size*0.5f, size*0.5f);
		float rad = std::atan2f(velocity.y, velocity.x) + static_cast<float>(PI/2);
		shape.setRotation(static_cast<float>(rad_to_deg(rad)));
		shape.setFillColor(boid->color);
		shape.setPosition(position);

		window.draw(shape);
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