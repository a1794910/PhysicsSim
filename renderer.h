#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "obj.h"

struct user_input_event {
    sf::Vector2f pos;
    char key;
};

class renderer {
public:
    renderer(int width, int height, int max_render_count);
    ~renderer();

    bool add_gfx(obj* shape);

    void begin_frame();

    void render();

    bool close_flag();

    user_input_event poll_input_events();

    sf::RenderWindow* get_window();
private:
    sf::RenderWindow window;
    obj** gfx;
    int obj_index;
    int max_obj_count;
};

#endif
