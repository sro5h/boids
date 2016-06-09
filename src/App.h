#ifndef APP_H
#define APP_H

#include "Types.h"
#include "Boid.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#define EPSILON             0.0000001f
#define BOID_SPEED          5.f
#define MAX_SPEED           70.f
#define MOUSE_ATTRACTION    0.01f
#define MOUSE_REPULSION     1.f
#define REPULSION_DIST      150.f
#define REPULSION_DIST_FACTOR 50.f
#define CENTER_WEIGHT       100.f
#define INFLUENCE_DIST      50.f
#define INFLUENCE_FACTOR    1.5f
#define BOID_ATTRACTION     50.f

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

    bool followMouse;
    bool fleeMouse;

    void addBoid();
    void addBoid(const sf::Vector2f& position);
    void addBoid(const sf::Vector2f& position, const sf::Vector2f& velocity);

    sf::Vector2f rule1(Boid* b);
    sf::Vector2f rule2(Boid* b);
    sf::Vector2f rule3(Boid* b);
    sf::Vector2f rule4(Boid* b);

    void limitVelocities();

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
