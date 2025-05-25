#pragma once

#include <curses.h>
#include <unistd.h>
#include <locale.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>

#include "blocks.h"

void print_help(void);

void print_version(void);

void refresh_all(std::vector<WINDOW*>);

void borders_all(std::vector<WINDOW *>, WINDOW * = nullptr); 

void draw_dots(WINDOW *, int, int, int);

void draw_board(WINDOW *, int, dataStream);

void draw_block(WINDOW *, int, int, int, int);

void moving_down(dataStream &);

void draw_score(WINDOW*, int, int, int, unsigned long);

void draw_side_boxes(WINDOW *, WINDOW *, WINDOW *, int, int, int, dataStream);

void enable_soft_tetris_palette();

void enable_basic_palette();

void set_background(WINDOW *, int, int);

void draw_help_text(WINDOW *, int, int, int);