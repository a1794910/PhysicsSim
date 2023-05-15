#ifndef BOUND_H
#define BOUND_H
#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>

// structure to store the result of two objects colliding
struct collision_result {
    float MTV_len;
    sf::Vector2f axis;
    bool belongs_to;
    int beg_vert_index;
};

// structure representing a line in 2D space
struct line {
    sf::Vector2f dir;
    sf::Vector2f off;
};

class bound {
public:
    bound();
    bound(sf::Vector2f pos, sf::Vector2f size, sf::ConvexShape bound_verts);
    ~bound();

    // add force to the current force value
    void apply_force(sf::Vector2f F);

    // detect wether this bound collides with an other bound
    collision_result collides_with(bound* other);

    // get the point of collision
    sf::Vector2f get_collision_pt(sf::RenderWindow* window, bound* other, collision_result res);

    // getters
    int get_vert_count();
    sf::Vector2f* get_verts();
    sf::Vector2f get_vert(int i);
    sf::Vector2f get_normal(int index);
    sf::Vector2f get_normal(sf::Vector2f vertex);
    int get_normal_count();
    sf::Vector2f get_net_force();
    float get_mass();
    sf::Vector2f get_pos();
    sf::Vector2f get_half_sizes();

    // setters
    void set_force(sf::Vector2f force);
    void set_mass(float m);
    void set_pos(sf::Vector2f pos);
    void set_rot(float angle);

    // debug tools
    void dbg_draw_collision_pos(sf::RenderWindow* window, sf::Vector2f collision_pos);
    void dbg_draw_bound(sf::RenderWindow* window);
    void dbg_draw_normal(sf::RenderWindow* window, sf::Vector2f normal);
    void dbg_draw_normals(sf::RenderWindow* window);

    // math functions
    void normalize(sf::Vector2f& vec);
    sf::Vector2f normalize(sf::Vector2f vec);
    float Dot(sf::Vector2f a, sf::Vector2f b);
    sf::Vector2f rotate(sf::Vector2f vec, float angle);

private:
    // private member functions
    sf::Vector2f project_onto_axis(sf::Vector2f axis);

    int sign(float num);

    // attributes
    sf::Vector2f pos;
    float rot;
    sf::Vector2f scale;

    sf::Vector2f net_F;
    sf::Vector2f* verts;
    int verts_count;
    int normal_count;
    float mass;
};

#endif
