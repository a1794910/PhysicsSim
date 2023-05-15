#include "static_obj.h"

static_obj::static_obj(sf::ConvexShape verts, sf::Vector2f position, sf::Vector2f size) : collider(position, size, verts) {
    gfx = sf::ConvexShape(verts.getPointCount());
    float half_width = size.x / 2.0f;
    float half_height = size.y / 2.0f;
    for (int i = 0; i < verts.getPointCount(); ++i) {
        gfx.setPoint(i, sf::Vector2f(verts.getPoint(i).x * half_width + position.x, verts.getPoint(i).y * half_height + position.y));
    }
}
static_obj::~static_obj() {

}

void static_obj::on_update(float delta) {

}

bound* static_obj::get_bound() {
    return &collider;
}
sf::Vector2f static_obj::get_pos() {
    return collider.get_pos();
}

void static_obj::set_pos(sf::Vector2f new_pos) {
    collider.set_pos(new_pos);
}
void static_obj::set_rot(float new_rot) {
    collider.set_rot(new_rot);
    
    rotate_gfx(collider.get_pos(), new_rot);
}
bool static_obj::set_vel(sf::Vector2f to) {
    return false;
}
void static_obj::set_acc(sf::Vector2f to) {

}

sf::Vector2f static_obj::get_vel() {
    return sf::Vector2f(0.0f, 0.0f);
}
sf::Vector2f static_obj::get_acc() {
    return sf::Vector2f(0.0f, 0.0f);
}

void static_obj::move_obj(sf::Vector2f to) {

}
