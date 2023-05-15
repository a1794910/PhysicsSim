#ifndef OBJ_H
#define OBJ_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class obj {
public:
    virtual ~obj();

    virtual void on_update(float delta) = 0;

    void move_gfx(sf::Vector2f by);
    void move_gfx_to(sf::Vector2f to);
    void rotate_gfx(sf::Vector2f around, float to); // rotates convex shape around point specified by around param

    sf::ConvexShape get_gfx();

    void set_gfx_color(sf::Color col);
protected:
    sf::ConvexShape gfx;
};

#endif
