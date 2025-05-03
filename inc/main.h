#pragma once

#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

#include "blocks.h"

void print_help(void);
void print_version(void);

void refresh_all(std::vector<WINDOW*>);
void borders_all(std::vector<WINDOW *>, WINDOW * = nullptr); 

void draw_dots(WINDOW *, int, int, int);

void draw_board(WINDOW *, int, dataStream);

void draw_block(WINDOW *, int, int, int);

void moving_down(dataStream &);

