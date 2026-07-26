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
    Rectangle rect = {67, 67, (float)constants::cell_width,
                      (float)constants::cell_height};
    bool blockstate = false;
    Color color;
};


class Blocks {
public:
    Block block;
    Block blocks[constants::COL_NUM][constants::ROW_NUM];
    Block new_blocks[constants::COL_NUM][constants::ROW_NUM];
    float fallspeed = 100.0f;
    // std::vector<Coord> coords;

    Blocks () {
        for (int i = 0; i < constants::COL_NUM; ++i) {
            for (int j = 0; j < constants::ROW_NUM; ++j) {
                block.rect.x = i * constants::cell_width;
                block.rect.y = j * constants::cell_height;
                block.color = sand_colors[pick_a_color(sand_colors)];
                blocks[i][j] = block;
            }
        }
        // coords.push_back({10, 1});
        // coords.push_back({10, 3});
        // coords.push_back({10, 5});
        // coords.push_back({10, 16});
        // coords.push_back({10, 18});
        // coords.push_back({10, 20});
        // coords.push_back({10, 12});
        // coords.push_back({10, 15});
        // coords.push_back({10, 22});
        // coords.push_back({1, 1});
        // coords.push_back({1, 3});
        // coords.push_back({1, 5});
        // coords.push_back({1, 16});
        // coords.push_back({1, 18});
        // coords.push_back({1, 20});
        // coords.push_back({1, 12});
        // coords.push_back({1, 15});
        // coords.push_back({1, 22});
        // blocks[2][3].blockstate = BlockState::FILLED;
        // blocks[10][15].blockstate = BlockState::FILLED;
    }


    void draw() {
        for (int i = 0; i < constants::COL_NUM; ++i) {
            for (int j = 0; j < constants::ROW_NUM; ++j) {
                if (blocks[i][j].blockstate) {
                    block_rect.x = blocks[i][j].rect.x;
                    block_rect.y = blocks[i][j].rect.y;
                    DrawRectangleRec(block_rect, blocks[i][j].color);
                }
            }
        }
    }

    void update(float deltatime) {
        for (int i = 0; i < constants::COL_NUM; ++i) {
            for (int j = 0; j < constants::ROW_NUM; ++j) {
                new_blocks[i][j] = blocks[i][j];
            }
        }
        for (int i = 0; i < constants::COL_NUM; ++i) {
            for (int j = 0; j < constants::ROW_NUM; ++j) {

                if (j >= constants::ROW_NUM - 1) {
                    continue;
                }
                if (blocks[i][j].blockstate) {

                    if (i > 0 && i < constants::COL_NUM - 1) {
                        if (blocks[i][j + 1].blockstate) {
                            if (blocks[i - 1][j + 1].blockstate && !blocks[i + 1][j + 1].blockstate) {
                                new_blocks[i][j].blockstate = false;
                                new_blocks[i + 1][j + 1].blockstate = true;
                            }
                            else if (blocks[i + 1][j + 1].blockstate && !blocks[i - 1][j + 1].blockstate) {
                                new_blocks[i][j].blockstate = false;
                                new_blocks[i - 1][j + 1].blockstate = true;
                            }
                            else if (!blocks[i - 1][j + 1].blockstate && !blocks[i + 1][j + 1].blockstate) {
                                int choice = choose_left_or_right(); // True is right, false is left btw
                                if (choice) {
                                    new_blocks[i][j].blockstate = false;
                                    new_blocks[i + 1][j + 1].blockstate = true;
                                }
                                else if (!choice) {
                                    new_blocks[i][j].blockstate = false;
                                    new_blocks[i - 1][j + 1].blockstate = true;
                                }
                            }
                            else if (blocks[i - 1][j + 1].blockstate && blocks[i + 1][j + 1].blockstate) {
                                continue;
                            }
                        }
                        else {
                            new_blocks[i][j].blockstate = false;
                            new_blocks[i][j + 1].blockstate = true;
                        }
                    }
                    else {
                        if (blocks[i][j + 1].blockstate) {
                            if (!blocks[i + 1][j + 1].blockstate && i < constants::COL_NUM - 1) {
                                new_blocks[i][j].blockstate = false;
                                new_blocks[i + 1][j + 1].blockstate = true;
                            }
                            else if (!blocks[i - 1][j + 1].blockstate && i > 0) {
                                new_blocks[i][j].blockstate = false;
                                new_blocks[i - 1][j + 1].blockstate = true;
                            }
                        }
                        else {
                            new_blocks[i][j].blockstate = false;
                            new_blocks[i][j + 1].blockstate = true;
                        }
                    }

                }
            }
        }
        for (int i = 0; i < constants::COL_NUM; ++i) {
            for (int j = 0; j < constants::ROW_NUM; ++j) {
                blocks[i][j] = new_blocks[i][j];
            }
        }
    }


    void spawn(int x, int y) {
        blocks[x][y].blockstate = true;
    }

    void erase(int x, int y) {
        // for (int i = 0; i < constants::COL_NUM; ++i) {
        //     for (int j = 0; j < constants::ROW_NUM; ++j) {
        //         if (i == x && j == y) {
        blocks[x][y].blockstate = false;
                    // coords.erase(coords.begin() + i);
                // }
        // }
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