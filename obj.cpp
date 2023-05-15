#include "obj.h"

obj::~obj() {

}

sf::ConvexShape obj::get_gfx() {
    return gfx;
}

void obj::move_gfx(sf::Vector2f by) {
    for (int i = 0; i < gfx.getPointCount(); ++i) {
        gfx.setPoint(i, gfx.getPoint(i) + sf::Vector2f(by.x, -by.y));
    }
}
void obj::move_gfx_to(sf::Vector2f to) {
    gfx.setPosition(to);
}

void obj::rotate_gfx(sf::Vector2f around, float to) {
    for (int i = 0; i < gfx.getPointCount(); ++i) {
        sf::Vector2f p = gfx.getPoint(i) - around;
        gfx.setPoint(i, sf::Vector2f(p.x * cos(to) - p.y * sin(to), p.x * sin(to) + p.y * cos(to)) + around);
    }
}

void obj::set_gfx_color(sf::Color col) {
    gfx.setFillColor(col);
}
