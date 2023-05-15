#include "bound.h"

bound::bound() {
    verts = nullptr;
    normal_count = 0;
    net_F = sf::Vector2f(0.0f, 0.0f);
    verts_count = 0;
    rot = 0.0f;
    mass = 1.0f;
}
bound::bound(sf::Vector2f pos, sf::Vector2f size, sf::ConvexShape bound_verts) {
    this->pos = pos;
    rot = 0.0f;
    this->scale = sf::Vector2f(size.x / 2.0f, size.y / 2.0f);
    verts = new sf::Vector2f[bound_verts.getPointCount()];
    for (int i = 0; i < bound_verts.getPointCount(); ++i) {
        verts[i] = bound_verts.getPoint(i);
    }
    normal_count = bound_verts.getPointCount() - 1;
    net_F = sf::Vector2f(0.0f, 0.0f);
    verts_count = bound_verts.getPointCount();
    mass = 1.0f;
}
bound::~bound() {
    if (verts != nullptr) {
        delete[] verts;
    }
}

void bound::apply_force(sf::Vector2f F) {
    net_F += F;
}

collision_result bound::collides_with(bound* other) {

    float min_diff = 100000000.0f;
    sf::Vector2f min_vec(0.0f, 0.0f);
    sf::Vector2f collide_vert(0.0f, 0.0f);
    bool b = 0;
    int v = 0;

    int sgn_x = sign(this->pos.x - other->get_pos().x);
    int sgn_y = -sign(this->pos.y - other->get_pos().y);

    // SAT used for collision between bounds
    // (see link for more info: https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169)
    for (int i = 0; i < normal_count; ++i) {
        sf::Vector2f axis = get_normal(i);
        sf::Vector2f sector1 = this->project_onto_axis(axis);
        sf::Vector2f sector2 = other->project_onto_axis(axis);

        if (sector1.x > sector2.y || sector1.y < sector2.x) {
            // does not overlap
            return (collision_result){0.0f, sf::Vector2f(0.0f, 0.0f), 0, 0};
        }
        else {
            float diff0 = sector1.y - sector2.x;
            float diff1 = sector2.y - sector1.x;
            float diff = (abs(diff0) <= abs(diff1))?(diff0):(diff1);
            if (diff <= min_diff) {
                min_diff = diff;
                min_vec = sf::Vector2f(sgn_x * axis.x, sgn_y * axis.y);
                b = 1;
                v = i;
            }
        }
    }
    for (int i = 0; i < other->get_normal_count(); ++i) {
        sf::Vector2f axis = other->get_normal(i);
        sf::Vector2f sector1 = this->project_onto_axis(axis);
        sf::Vector2f sector2 = other->project_onto_axis(axis);

        if (sector1.x > sector2.y || sector1.y < sector2.x) {
            // does not overlap
            return (collision_result){0.0f, sf::Vector2f(0.0f, 0.0f), 0, 0};
        }
        else {
            float diff0 = sector1.y - sector2.x;
            float diff1 = sector2.y - sector1.x;
            float diff = (abs(diff0) <= abs(diff1))?(diff0):(diff1);
            if (diff <= min_diff) {
                min_diff = diff;
                min_vec = sf::Vector2f(sgn_x * axis.x, sgn_y * axis.y);
                b = 0;
                v = i;
            }
        }
    }

    return (collision_result){min_diff, min_vec, b, v};
}

sf::Vector2f bound::get_collision_pt(sf::RenderWindow* window, bound* other, collision_result res) {
    // finds collision based on the intersection between lines that make up bound

    sf::Vector2f pos(0.0f, 0.0f);

    if (!res.belongs_to) {
        line l1 = (line){sf::Vector2f(-res.axis.y, res.axis.x), sf::Vector2f(other->get_vert(res.beg_vert_index))};

        sf::VertexArray lines(sf::LineStrip, 2);
        int wrap = (res.beg_vert_index + 1) % other->get_vert_count();
        lines[0].position = other->get_vert(res.beg_vert_index);
        lines[1].position = other->get_vert(wrap);
        window->draw(lines);

        for (int i = 0; i < this->verts_count; ++i) {
            int i_wrap = abs((i + 1) % (this->verts_count));
            line l2 = (line){this->get_vert(i_wrap) - this->get_vert(i), this->get_vert(i)};

            if (l2.dir == l1.dir) {
                return sf::Vector2f(-1.0f, 0.0f);
            }

            float t = (l1.dir.x * (l2.off.y - l1.off.y) - l1.dir.y * (l2.off.x - l1.off.x))/(l1.dir.y * l2.dir.x - l1.dir.x * l2.dir.y);
            if (t >= -0.1f && t <= 1.1f) {
                pos = l2.dir * t + l2.off;
            }
        }
    }
    else {
        line l1 = (line){sf::Vector2f(-res.axis.y, res.axis.x), sf::Vector2f(this->get_vert(res.beg_vert_index))};

        sf::VertexArray lines(sf::LineStrip, 2);
        int wrap = (res.beg_vert_index + 1) % this->get_vert_count();
        lines[0].position = this->get_vert(res.beg_vert_index);
        lines[1].position = this->get_vert(wrap);
        window->draw(lines);

        for (int i = 0; i < other->get_vert_count(); ++i) {
            int i_wrap = abs((i + 1) % (other->get_vert_count()));
            line l2 = (line){other->get_vert(i_wrap) - other->get_vert(i), other->get_vert(i)};

            if (l2.dir == l1.dir) {
                return sf::Vector2f(-1.0f, 0.0f);
            }

            float t = (l1.dir.x * (l2.off.y - l1.off.y) - l1.dir.y * (l2.off.x - l1.off.x))/(l1.dir.y * l2.dir.x - l1.dir.x * l2.dir.y);
            if (t >= -0.1f && t <= 1.1f) {
                pos = l2.dir * t + l2.off;
            }
        }
    }

    return pos;
}

int bound::get_vert_count() {
    return verts_count;
}
sf::Vector2f* bound::get_verts() {
    return verts;
}
sf::Vector2f bound::get_vert(int i) {
    if (i < this->verts_count) {
        return sf::Vector2f(rotate(verts[i], rot).x * scale.x + pos.x, rotate(verts[i], rot).y * scale.y + pos.y);
    }
    return sf::Vector2f(0.0f, 0.0f);
}
sf::Vector2f bound::get_normal(int index) {
    int next = (index + 1) % verts_count;
    return get_normal(get_vert(next) - get_vert(index));
}
sf::Vector2f bound::get_normal(sf::Vector2f vertex) {
    return normalize(sf::Vector2f(-vertex.y, vertex.x));
}
int bound::get_normal_count() {
    return normal_count;
}
sf::Vector2f bound::get_net_force() {
    return net_F;
}
float bound::get_mass() {
    return mass;
}
sf::Vector2f bound::get_pos() {
    return pos;
}
sf::Vector2f bound::get_half_sizes() {
    return sf::Vector2f(scale.x / 2.0f, scale.y / 2.0f);
}

void bound::set_force(sf::Vector2f force) {
    net_F = force;
}

void bound::set_mass(float m) {
    mass = m;
}
void bound::set_pos(sf::Vector2f pos) {
    this->pos = pos;
}
void bound::set_rot(float angle) {
    rot = angle;
}

// private member function

float bound::Dot(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}
void bound::normalize(sf::Vector2f& a) {
    a /= sqrtf(Dot(a, a));
}
sf::Vector2f bound::normalize(sf::Vector2f vec) {
    float len = sqrtf(vec.x * vec.x + vec.y * vec.y);
    return sf::Vector2f(vec.x / len, vec.y / len);
}

sf::Vector2f bound::project_onto_axis(sf::Vector2f axis) {

    sf::Vector2f proj;

    float min_val = Dot(axis, sf::Vector2f(rotate(verts[0], rot).x * scale.x + pos.x, rotate(verts[0], rot).y * scale.y + pos.y));
    float max_val = min_val;
    for (int i = 1; i < verts_count; ++i) {
        float p = Dot(axis, sf::Vector2f(rotate(verts[i], rot).x * scale.x + pos.x, rotate(verts[i], rot).y * scale.y + pos.y));
        if (p < min_val) {
            min_val = p;
        }
        else if (p > max_val) {
            max_val = p;
        }
    }

    proj = sf::Vector2f(min_val, max_val);
    return proj;
}

sf::Vector2f bound::rotate(sf::Vector2f vec, float angle) {
    return sf::Vector2f(vec.x * cos(angle) - vec.y * sin(angle), vec.x * sin(angle) + vec.y * cos(angle));
}

int bound::sign(float num) {
    return (num > 0) - (num < 0);
}

void bound::dbg_draw_normals(sf::RenderWindow* window) {
    for (int i = 0; i < normal_count; i++) {
        sf::VertexArray lines(sf::LineStrip, 2);
        lines[0] = get_normal(i) + this->pos;
        lines[1] = lines[0].position + get_normal(i) * 10.0f;
        window->draw(lines);
    }

}
void bound::dbg_draw_normal(sf::RenderWindow* window, sf::Vector2f normal) {
    sf::VertexArray lines(sf::LineStrip, 2);
    lines[0] = normal + this->pos;
    lines[1] = lines[0].position + normal * 10.0f;
    window->draw(lines);
}
void bound::dbg_draw_collision_pos(sf::RenderWindow* window, sf::Vector2f collision_pos) {
    sf::CircleShape point(2.0f);
    point.setPosition(collision_pos - sf::Vector2f(1.0f, 1.0f));
    point.setFillColor(sf::Color(0, 255, 0));
    window->draw(point);
}
void bound::dbg_draw_bound(sf::RenderWindow* window) {
    sf::VertexArray lines(sf::LineStrip, verts_count);
    for (int i = 0; i < verts_count; ++i) {
        lines[i] = sf::Vector2f(rotate(verts[i], rot).x * scale.x + pos.x, rotate(verts[i], rot).y * scale.y + pos.y);
    }
    window->draw(lines);
}
