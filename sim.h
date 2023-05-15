#ifndef SIM_H
#define SIM_H
#include <vector>

#include <SFML/Graphics.hpp>

#include "static_obj.h"
#include "dynamic_obj.h"

class physics_sim {
public:
    physics_sim();
    ~physics_sim();

    bool add(static_obj* elem);

    void begin_sim_frame();

    void update_sim(sf::RenderWindow* window);

    void end_sim_frame();

private:
    std::vector<static_obj*> elems;

    sf::Vector2f gravity;

    sf::Time delta_time;
    sf::Clock sim_clk;
};

#endif
