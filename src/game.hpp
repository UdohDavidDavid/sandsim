#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "constants.hpp"
#include "block.hpp"
#include "mouse_box.hpp"
#include <string>

class Game {
public:
    Blocks blocks;
    MouseBox mouse_box;

    bool grid = true;

    Game() {
        // Tell the window to use vsync and work on high DPI displays
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

        SetTraceLogCallback(custom_log); // call this before InitWindow() 

        // Create the window and OpenGL context
        InitWindow(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT,
                constants::TITLE);
    }

    ~Game() {
        // destroy the window and cleanup the OpenGL context
        CloseWindow();
    }

    static void custom_log(int msgType, const char *text, va_list args) {
        return;
    }

    void run() {
        // game loop
        while (!WindowShouldClose()) {
            SetTargetFPS(constants::FPS);
            BeginDrawing();
            ClearBackground(BLACK);

            process_keys();
            draw_grid();
            blocks.draw();
            blocks.update(GetFrameTime());
            mouse_box.draw_rect_at_mouse_pos(blocks);
            mouse_box.scroll_radius();
            draw_fps();
            
            EndDrawing();
        }
    }

    void draw_grid() {
        if (IsKeyPressed(KEY_SPACE)) grid = !grid;
        if (grid) {
            for (int i = 1; i < constants::COL_NUM; ++i) {
                DrawLine(i * constants::cell_width, 0, i * constants::cell_width,
                    constants::WINDOW_HEIGHT, {67, 67, 67, 255});
                for (int j = 1; j < constants::ROW_NUM; ++j) {
                    DrawLine(0, j * constants::cell_height, constants::WINDOW_WIDTH,
                        j * constants::cell_height, {67, 67, 67, 255});
                }
            }
        }
    }

    void draw_fps() {
        DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 5, WHITE);
    }

    void process_keys() {
        if (IsKeyPressed(KEY_LEFT_SHIFT)) {
            mouse_box.isDrawing = !mouse_box.isDrawing;
        }
        if(IsKeyPressed(KEY_LEFT_CONTROL)) {
            mouse_box.isNigga = !mouse_box.isNigga;
        }
    }
};

#endif