#include "sim.h"

physics_sim::physics_sim() {
    gravity = sf::Vector2f(0.0f, 9.8f);
}
physics_sim::~physics_sim() {

}

bool physics_sim::add(static_obj* elem) {
    elems.push_back(elem);
    return true;
}

void physics_sim::end_sim_frame() {
    delta_time = sim_clk.getElapsedTime();
}

void physics_sim::update_sim(sf::RenderWindow* window) {

    for (int i = 0; i < elems.size(); ++i) {

        // apply force due to gravity
        elems[i]->get_bound()->apply_force(gravity * elems[i]->get_bound()->get_mass());
        elems[i]->get_bound()->dbg_draw_collision_pos(window, elems[i]->get_bound()->get_pos());

        // check collision
        sf::Vector2f displacement(0.0f, 0.0f);
        for (int j = 0; j < elems.size(); ++j) {
            if (i != j) {
                collision_result response = elems[i]->get_bound()->collides_with(elems[j]->get_bound());
                if (response.axis.x != 0.0f || response.axis.y != 0.0f) { // if a direction is non zero, bounds have collided

                    elems[i]->get_bound()->dbg_draw_normal(window, response.axis); // debug

                    // move bound outside other bound
                    displacement += response.axis * response.MTV_len;

                    // apply response force
                        //TODO

                    // get point of collision and resolve angular kinematics
                    sf::Vector2f col_pos = elems[i]->get_bound()->get_collision_pt(window, elems[j]->get_bound(), response);

                    elems[i]->get_bound()->dbg_draw_collision_pos(window, col_pos); // debug
                }
            }
        }

        elems[i]->move_obj(displacement);

        // let objects move
        elems[i]->on_update(delta_time.asSeconds());

        // reset force
        elems[i]->get_bound()->set_force(sf::Vector2f(0.0f, 0.0f));

        elems[i]->get_bound()->dbg_draw_bound(window); // debug

    }

}

void physics_sim::begin_sim_frame() {
    sim_clk.restart();
}
