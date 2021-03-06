#ifndef TYPES_H
#define TYPES_H

#define PI 3.14159265359
#define deg_to_rad(x) (x / (180/PI))
#define rad_to_deg(x) (x * (180/PI))

namespace sf
{
class RenderTarget;
}

namespace boids
{
typedef signed   char int8;
typedef unsigned char uint8;

typedef signed   short int16;
typedef unsigned short uint16;

typedef signed   int in32;
typedef unsigned int uint32;
}

#endif // !TYPES_H
