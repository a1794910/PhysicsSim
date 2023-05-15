#ifndef DYNAMIC_OBJ_H
#define DYNAMIC_OBJ_H

#include "obj.h"
#include "static_obj.h"

class dynamic_obj : public static_obj {
public:
    dynamic_obj(sf::ConvexShape verts, sf::Vector2f position, sf::Vector2f size);
    ~dynamic_obj();

    void on_update(float delta) override;

    void move_obj(sf::Vector2f to) override;

    void set_acc(sf::Vector2f to) override;
    bool set_vel(sf::Vector2f to) override;

    sf::Vector2f get_vel() override;
    sf::Vector2f get_acc() override;
protected:
    sf::Vector2f vel;
    sf::Vector2f acc;
};

#endif
