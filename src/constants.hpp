#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace constants {
    inline const int WINDOW_WIDTH = 800;
    inline const int WINDOW_HEIGHT = 600;
    inline const int ASPECT_RATIO = WINDOW_WIDTH / WINDOW_HEIGHT;
    inline const char *TITLE = "Snake sim";


    inline const int cell_width = 5;
    inline const int cell_height = 5;

    inline const int COL_NUM = WINDOW_WIDTH / cell_width;
    inline const int ROW_NUM = WINDOW_HEIGHT / cell_height;

    inline const int FPS = 45;
}

#endif