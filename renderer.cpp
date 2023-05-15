#include "renderer.h"

renderer::renderer(int width, int height, int max_render_count) : window(sf::VideoMode(width, height), "!") {
    obj_index = 0;
    max_obj_count = max_render_count;
    gfx = new obj*[max_render_count];
}
renderer::~renderer() {
    delete[] gfx;
}

bool renderer::add_gfx(obj* shape) {
    if (obj_index < max_obj_count) {
        gfx[obj_index] = shape;
        ++obj_index;
        return true;
    }
    return false;
}

void renderer::begin_frame() {
    window.clear();
}

void renderer::render() {
    for (int i = 0; i < obj_index; ++i) {
        window.draw(gfx[i]->get_gfx());
    }
    window.display();
}

bool renderer::close_flag() {
    return !window.isOpen();
}

user_input_event renderer::poll_input_events() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    user_input_event in = (user_input_event){sf::Vector2f(-1.0f, -1.0f), ' '};
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    in.pos = sf::Vector2f(mouse_pos);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        in.key = '1';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        in.key = '2';
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        in.key = '`';
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        in.key = '~';
    }

    return in;
}

sf::RenderWindow* renderer::get_window() {
    return &window;
}
