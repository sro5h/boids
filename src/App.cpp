#include "App.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <random>

namespace boids
{
App::App(uint16 width, uint16 height)
	: width(800), height(800), worldwidth(width*0.5f), worldheight(height*0.5f)
{
	window.create(sf::VideoMode(this->width, this->height), "Boids v0.1", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings());
	sf::View view;
	view.reset(sf::FloatRect(-worldwidth, -worldheight, worldwidth*2, worldheight*2));
	/*view.setViewport(sf::FloatRect(1.0f, 1.0f, 1.0f, 1.0f));*/
	window.setView(view);

	addBoid(sf::Vector2f(200, 200), sf::Vector2f(-300, -300));
	addBoid(sf::Vector2f(-200, -200), sf::Vector2f(300, 300));
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
	boidslist.push_back(new Boid(position));
}

void App::addBoid(const sf::Vector2f& position, const sf::Vector2f& velocity)
{
	boidslist.push_back(new Boid(position));
	boidslist.back()->velocity = velocity;
}


sf::Vector2f App::rule1(Boid* b)
{
	if(boidslist.size() > 1)
	{
		sf::Vector2f center;

		for(auto& boid : boidslist)
		{
			if(boid != b)
			{
				center = center + boid->position;
			}
		}
		center = center * (1.f/(boidslist.size()-1.f));
		return (center - b->position) * (1.f/100.f);
	}
	return sf::Vector2f();
}

sf::Vector2f App::rule2(Boid* b)
{
	sf::Vector2f c;

	/*for(auto& boid : boidslist)
	{
		if(boid != b)
		{
			sf::Vector2f delta = boid->position - b->position;
			if(std::sqrt(delta.x * delta.x + delta.y * delta.y) < 100)
			{
				c = c - (boid->position - b->position);
			}
		}
	}*/

	for(auto& boid : boidslist)
	{
		if(boid != b)
		{
			sf::Vector2f delta = boid->position - b->position;
			float len = std::sqrt(delta.x*delta.x + delta.y*delta.y);
			if(len < 50)
				c = c - (delta * 1.f/(len));
		}
	}

	return c;
}

sf::Vector2f App::rule3(Boid* b)
{
	sf::Vector2f pv;

	if(boidslist.size() > 1)
	{
		for(auto& boid : boidslist)
		{
			if(boid != b)
			{
				pv = pv + boid->velocity;
			}
		}
		pv = pv / (boidslist.size() -1.f);
		pv = (pv - b->velocity) / 10.f;
	}
	return pv;
}

void App::handleEvent(sf::Event& ev)
{
	if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::A)
	{
		addBoid();
	}
	else if(ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
	{
		addBoid(window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)));
	}
}

void App::update(float dt)
{
	sf::Vector2f v1, v2, v3;

	for(auto& boid : boidslist)
	{
		v1 = rule1(boid);
		v2 = rule2(boid);
		v3 = rule3(boid);

		boid->velocity = boid->velocity + v1 + v2 + v3;
		boid->position = boid->position + (boid->velocity * dt);
	}

	//std::cout << "FPS: " << 1/dt << std::endl;
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