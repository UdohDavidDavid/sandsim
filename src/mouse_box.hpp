#ifndef MOUSE_HOX_HPP
#define MOUSE_HOX_HPP

#include "raylib.h"
#include "constants.hpp"
#include "block.hpp"
#include <string>

class MouseBox {
public:
    bool isDrawing = false;
    bool isNigga = false;
    int radius = 1;
    float timer = 0.0f;
    float last_frame_time = 0.0f;
    float timeout = false;

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
        if (isNigga) {
            DrawText("-",
                    mouse_rect.x + ((constants::cell_width) * radius) + constants::cell_width,
                    mouse_rect.y - constants::cell_height, 5, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && yep) {
                    for (int i = 0; i < constants::COL_NUM; ++i) {
                        for (int j = 0; j < constants::ROW_NUM; ++j) {
                            if (CheckCollisionRecs(mouse_rect, blocks.blocks[i][j].rect)) {
                                blocks.spawn(i, j); 
                            }
                        }
                    }
            }
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && yep) {
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
            DrawText("C",
                    mouse_rect.x + ((constants::cell_width) * radius) + constants::cell_width,
                    mouse_rect.y - constants::cell_height, 5, WHITE);
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && yep) {
                timer += 1 * GetFrameTime();
                if (timer - last_frame_time > 0.06) {
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
            if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && yep) {
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

    void scroll_radius() {
        static int offset = 1;
        radius += static_cast<int>(GetMouseWheelMove()) * offset;
        if (!isDrawing) {
            if (radius >= 5) {
                offset = 2;
            }
            else {
                offset = 1;
            }
            if (radius <= 1) radius = 1;
        }
        else {
            if (radius >= 5) {
                offset = 2;
            }
            else {
                offset = 1;
            }
            if (radius <= 1) radius = 1;
        }
        Vector2 text = MeasureTextEx(GetFontDefault(), std::to_string(radius).c_str(), 5, 1);
        DrawText(std::to_string(radius).c_str(),
                (mouse_rect.x - constants::cell_width) - text.x,
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