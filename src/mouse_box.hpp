#ifndef MOUSE_HOX_HPP
#define MOUSE_HOX_HPP

#include "raylib.h"
#include "constants.hpp"
#include "block.hpp"

class MouseBox {
public:
    bool isDrawing = false;
    bool isNigga = false;
    int radius = 1;

    void draw_rect_at_mouse_pos(Blocks &blocks) {
        mouse = GetMousePosition();
        origin = {0, 0};
        offset_x = (float)radius * constants::cell_width / 2;
        offset_y = (float)radius * constants::cell_width / 2;
        mouse_rect = {
            static_cast<float>(static_cast<int>(mouse.x / constants::cell_width) *
                constants::cell_width),
            static_cast<float>(static_cast<int>(mouse.y / constants::cell_height) *
                constants::cell_height),
            radius * (float)constants::cell_width,
            radius * (float)constants::cell_height};

        DrawRectangleLines(
            static_cast<int>(mouse.x / constants::cell_width) * constants::cell_width,
            static_cast<int>(mouse.y / constants::cell_height) * constants::cell_height,
            radius * (float)constants::cell_width,
            radius * (float)constants::cell_height, {255, 255, 255, 255});
        bool yep = false;
        if (mouse.x > 0 && mouse.x < constants::WINDOW_WIDTH && mouse.y > 0 && mouse.y < constants::WINDOW_HEIGHT)
            yep = true;
        static float timer = 0.0f;
        static float last_frame_time = 0.0f;
        static float timeout = false;
        if (!isDrawing) {
            if (isNigga) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && yep) {
                        for (int i = 0; i < constants::COL_NUM; ++i) {
                            for (int j = 0; j < constants::ROW_NUM; ++j) {
                                if (CheckCollisionRecs(mouse_rect, blocks.blocks[i][j].rect)) {
                                    blocks.spawn(i, j); 
                                }
                            }
                        }
                }
            }
            else {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && yep) {
                    timer += 1 * GetFrameTime();
                    if (timer - last_frame_time > 0.08) {
                        timeout = true;
                        for (int i = 0; i < constants::COL_NUM; ++i) {
                            for (int j = 0; j < constants::ROW_NUM; ++j) {
                                if (CheckCollisionRecs(mouse_rect, blocks.blocks[i][j].rect)) {
                                    blocks.spawn(i, j); 
                                }
                            }
                        }
                        timer = 0;
                    }
                }
            }
        }
        else {
            if (isNigga) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && yep) {
                    for (int i = 0; i < constants::COL_NUM; ++i) {
                        for (int j = 0; j < constants::ROW_NUM; ++j) {
                            if (CheckCollisionRecs(mouse_rect, blocks.blocks[i][j].rect)) {
                                blocks.erase(i, j);
                            }
                        }
                    }
                }
            }
            else {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && yep) {
                    for (int i = 0; i < constants::COL_NUM; ++i) {
                        for (int j = 0; j < constants::ROW_NUM; ++j) {
                            if (CheckCollisionRecs(mouse_rect, blocks.blocks[i][j].rect)) {
                                blocks.erase(i, j);
                            }
                        }
                    }
                }
            }
        }
    }

    void scroll_radius() {
        radius += static_cast<int>(GetMouseWheelMove());
        if (!isDrawing) {
            if (radius >= 30) radius = 30;
            if (radius <= 1) radius = 1;
        }
        else {
            if (radius >= 30) radius = 30;
            if (radius <= 1) radius = 1;
        }
        DrawText(std::to_string(radius).c_str(),
                mouse_rect.x - constants::cell_width,
                mouse_rect.y - constants::cell_height, 5, WHITE);
    }

private:
    Vector2 mouse = GetMousePosition();
    Rectangle mouse_rect;
    Vector2 origin = {0, 0};
    float offset_x = (float)radius * constants::cell_width / 2;
    float offset_y = (float)radius * constants::cell_width / 2;
};

#endif