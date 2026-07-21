#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "constants.hpp"
#include "colors.hpp"
#include "raylib.h"
#include <random>
#include <vector>

enum class BlockState {
    EMPTY,
    FILLED,
};

struct Block {
    float pos_x = 30 * constants::cell_width;
    float pos_y = 30 * constants::cell_height;
    Rectangle rect = {pos_x, pos_y, (float)constants::cell_width,
                      (float)constants::cell_height};
    BlockState blockstate = BlockState::EMPTY;
    Color color;
};

struct Coord {
    int i;
    int j;
};

class Blocks {
public:
    Block block;
    Block blocks[constants::COL_NUM][constants::ROW_NUM];
    float fallspeed = 100.0f;
    std::vector<Coord> coords;

    Blocks () {
        for (int i = 0; i < constants::COL_NUM; ++i) {
            for (int j = 0; j < constants::ROW_NUM; ++j) {
                block.pos_x = i * constants::cell_width;
                block.pos_y = j * constants::cell_height;
                block.rect.x = block.pos_x;
                block.rect.y = block.pos_y;
                block.color = sand_colors[pick_a_color(sand_colors)];
                blocks[i][j] = block;
            }
        }
        coords.push_back({10, 1});
        coords.push_back({10, 3});
        coords.push_back({10, 5});
        coords.push_back({10, 16});
        coords.push_back({10, 18});
        coords.push_back({10, 20});
        coords.push_back({10, 12});
        coords.push_back({10, 15});
        coords.push_back({10, 22});
        coords.push_back({1, 1});
        coords.push_back({1, 3});
        coords.push_back({1, 5});
        coords.push_back({1, 16});
        coords.push_back({1, 18});
        coords.push_back({1, 20});
        coords.push_back({1, 12});
        coords.push_back({1, 15});
        coords.push_back({1, 22});
    }


    void draw() {
        for (int i = 0; i < constants::COL_NUM; ++i) {
            for (int j = 0; j < constants::ROW_NUM; ++j) {
                if (blocks[i][j].blockstate == BlockState::FILLED) {
                    block_rect.x = blocks[i][j].pos_x;
                    block_rect.y = blocks[i][j].pos_y;
                    DrawRectangleRec(block_rect, blocks[i][j].color);
                }
            }
        }
    }

    void update(float deltatime) {
        for (int i = 0; i < coords.size(); ++i) {
            if (coords[i].j >= constants::ROW_NUM - 1) {
                continue;
            }

            if (coords[i].i > 0 & coords[i].i < constants::COL_NUM - 1) {
                if (blocks[coords[i].i][coords[i].j + 1].blockstate == BlockState::FILLED) {
                    if (blocks[coords[i].i - 1][coords[i].j + 1].blockstate == BlockState::FILLED && blocks[coords[i].i + 1][coords[i].j + 1].blockstate != BlockState::FILLED) {
                        blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                        coords[i].i += 1;
                        coords[i].j += 1;
                    }
                    else if (blocks[coords[i].i + 1][coords[i].j + 1].blockstate == BlockState::FILLED && blocks[coords[i].i - 1][coords[i].j + 1].blockstate != BlockState::FILLED) {
                        blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                        coords[i].i -= 1;
                        coords[i].j += 1;
                    }
                    else if (blocks[coords[i].i - 1][coords[i].j + 1].blockstate != BlockState::FILLED && blocks[coords[i].i + 1][coords[i].j + 1].blockstate != BlockState::FILLED) {
                        int choice = choose_left_or_right(); // True is right, false is left btw
                        if (choice) {
                            blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                            coords[i].i += 1;
                            coords[i].j += 1;
                        }
                        else if (!choice) {
                            blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                            coords[i].i -= 1;
                            coords[i].j += 1;
                        }
                    }
                    else if (blocks[coords[i].i - 1][coords[i].j + 1].blockstate == BlockState::FILLED && blocks[coords[i].i + 1][coords[i].j + 1].blockstate == BlockState::FILLED) {
                        continue;
                    }
                }
                else {
                    blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                    coords[i].j += 1;
                }
            }
            else {
                if (blocks[coords[i].i][coords[i].j + 1].blockstate == BlockState::FILLED) {
                    if (blocks[coords[i].i + 1][coords[i].j + 1].blockstate != BlockState::FILLED && coords[i].i < constants::COL_NUM - 1) {
                        blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                        coords[i].i += 1;
                    }
                    else if (blocks[coords[i].i - 1][coords[i].j + 1].blockstate != BlockState::FILLED && coords[i].i > 0) {
                        blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                        coords[i].i -= 1;
                    }
                }
                else {
                    blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                    coords[i].j += 1;
                }
            }
            fill_coords();
        }
    }

    void fill_coords() {
        for (int i = 0; i < coords.size(); ++i) {
            blocks[coords[i].i][coords[i].j].blockstate = BlockState::FILLED;
        }
    }

    void spawn(int x, int y) {
        coords.push_back({x, y});
    }

    void erase(int x, int y) {
        for (int i = 0; i < coords.size(); ++i) {
            if (coords[i].i == x && coords[i].j == y) {
                blocks[coords[i].i][coords[i].j].blockstate = BlockState::EMPTY;
                coords.erase(coords.begin() + i);
            }
        }
    }

    int choose_left_or_right() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1);
        return dist6(rng);
    }

private:
    Rectangle block_rect = {0, 0,  // currently drawn rect
                        (float)constants::cell_width,
                        (float)constants::cell_height};
    
};

#endif