#ifndef STATIC_OBJ_H
#define STATIC_OBJ_H

#include "obj.h"
#include "bound.h"

class static_obj : public obj {
public:
    static_obj(sf::ConvexShape verts, sf::Vector2f position, sf::Vector2f size);
    virtual ~static_obj();

    void on_update(float delta) override;

    virtual void move_obj(sf::Vector2f to);

    bound* get_bound();
    sf::Vector2f get_pos();

    void set_pos(sf::Vector2f new_pos);
    void set_rot(float new_rot);
    virtual bool set_vel(sf::Vector2f to);
    virtual void set_acc(sf::Vector2f to);

    virtual sf::Vector2f get_vel();
    virtual sf::Vector2f get_acc();
protected:
    bound collider;
};

#endif
