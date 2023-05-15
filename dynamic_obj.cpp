#include "dynamic_obj.h"

dynamic_obj::dynamic_obj(sf::ConvexShape verts, sf::Vector2f position, sf::Vector2f size) : static_obj(verts, position, size) {

}
dynamic_obj::~dynamic_obj() {

}

void dynamic_obj::on_update(float delta) {
    acc = collider.get_net_force() / collider.get_mass();
    vel += acc * delta;
    collider.set_pos(collider.get_pos() + vel * delta);
    move_gfx(vel * delta);
}

void dynamic_obj::set_acc(sf::Vector2f to) {
    acc = to;
}

bool dynamic_obj::set_vel(sf::Vector2f to) {
    vel = to;
    return true;
}

sf::Vector2f dynamic_obj::get_acc() {
    return acc;
}

sf::Vector2f dynamic_obj::get_vel() {
    return vel;
}

void dynamic_obj::move_obj(sf::Vector2f to) {
    collider.set_pos(collider.get_pos() + to);
    move_gfx(to);
}
