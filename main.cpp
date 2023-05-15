#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "renderer.h"

#include "static_obj.h"
#include "dynamic_obj.h"

#include "sim.h"

int main() {
    renderer r(400, 400, 2);

    physics_sim s;

    sf::ConvexShape polygon;
    polygon.setPointCount(5);
    polygon.setPoint(0, sf::Vector2f(-1, -1));
    polygon.setPoint(1, sf::Vector2f(-1, 1));
    polygon.setPoint(2, sf::Vector2f(1, 1));
    polygon.setPoint(3, sf::Vector2f(1, -1));
    polygon.setPoint(4, sf::Vector2f(-1, -1));

    sf::ConvexShape polygon2;
    polygon2.setPointCount(7);
    polygon2.setPoint(0, sf::Vector2f(0.5, 0.5));
    polygon2.setPoint(1, sf::Vector2f(1, 0));
    polygon2.setPoint(2, sf::Vector2f(0.5, -0.5));
    polygon2.setPoint(3, sf::Vector2f(-0.5, -0.5));
    polygon2.setPoint(4, sf::Vector2f(-1, 0));
    polygon2.setPoint(5, sf::Vector2f(-0.5, 0.5));
    polygon2.setPoint(6, sf::Vector2f(0.5, 0.5));

    dynamic_obj obj1(polygon, sf::Vector2f(200, 40), sf::Vector2f(50, 50));
    dynamic_obj obj4(polygon2, sf::Vector2f(20, 40), sf::Vector2f(50, 50));
    static_obj obj2(polygon, sf::Vector2f(200, 350), sf::Vector2f(300, 50));

    s.add(&obj1);
    s.add(&obj2);
    s.add(&obj4);

    float rotation = 3.14159f/4.0f;
    obj1.set_rot(rotation);
    char prev_key = ' ';

    while (!r.close_flag())
    {
        r.begin_frame();

        s.begin_sim_frame();

        user_input_event a = r.poll_input_events();

        switch (a.key) {
            case '`':
            {
                if (a.key != prev_key) {
                    dynamic_obj* n = new dynamic_obj(polygon, a.pos, sf::Vector2f(50, 50));
                    s.add(n);
                    prev_key = a.key;
                }
            }
            break;
            default:
                prev_key = ' ';
        }

        s.update_sim(r.get_window());

        r.render();

        s.end_sim_frame();
    }

    return 0;
}
