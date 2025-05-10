#include "main.h"

int main(int argc, char *argv[]) {
    int option;
    if (argc == 2) {
        while ((option = getopt(argc, argv, ":hvo:i:c:")) != -1) {
            switch (option) {
            case 'h':
                print_help();
                exit(0);
            case 'v':
                print_version();
                exit(0);
            }
        }
    }



    initscr();
    noecho();
    curs_set(0);
    
    int terminal_height, terminal_width;
    int box_x{0};
    int box_y{0};
    
    getmaxyx(stdscr, terminal_height, terminal_width); // Terminali akna suuruste saamine
    
    WINDOW *whole_screen = newwin(terminal_height, terminal_width, box_y, box_x);
    
    if (terminal_height < 23 or terminal_width < 48) {
        mvwprintw(whole_screen, terminal_height / 2, terminal_width / 2 - 33 / 2, "Too small, make terminal bigger!" );
        sleep(5);
        return 1;
    }
    
    if (!has_colors() or !can_change_color()) {
        std::printf("Can't change color!");
        return 0;
    } else {
        start_color();
    }
    
    WINDOW *game_board;
    
    WINDOW *score_board;
    WINDOW *first_preview;
    WINDOW *second_preview;
    
    WINDOW *change_box;
    
    // Defiing window default sizes
    int double_size{};

    int game_board_height{ROWS};
    int game_board_width{COLUMNS * 2}; // Times two because one block consists of two spaces - Original Tetris grid is 10 x 20
    
    int score_board_height{3};
    int score_board_width{10};
    
    int preview_board_height{4};
    int preview_board_width{10};
    
    if (terminal_height > 43) {
        // Makes every window 2 times larger
        double_size++;
        
        game_board_height *= 2;
        game_board_width *= 2;

        score_board_height += 2;
        score_board_width *= 2;
        
        preview_board_height *= 2;
        preview_board_width *= 2;
        
    }
    
    nodelay(whole_screen, TRUE);
    
    
    game_board_height += 2;
    game_board_width += 2;
    
    score_board_height += 2;
    score_board_width += 2;
    
    preview_board_height += 2;
    preview_board_width += 2;
    
    game_board = newwin(
        game_board_height, 
        game_board_width,
        terminal_height / 2 - game_board_height / 2,
        terminal_width / 2 - game_board_width / 2);
        
    score_board = newwin(
        score_board_height, 
        score_board_width,
        terminal_height / 2 - game_board_height / 2,
        terminal_width / 2 + game_board_width / 2);
        
    first_preview = newwin(
            preview_board_height, 
        preview_board_width, 
        terminal_height / 2 - game_board_height / 2 + score_board_height,
        terminal_width / 2 + game_board_width / 2);
        
    second_preview = newwin(
            preview_board_height, 
            preview_board_width, 
            terminal_height / 2 - game_board_height / 2 + score_board_height + preview_board_height,
            terminal_width / 2 + game_board_width / 2);
        
    change_box = newwin(
            preview_board_height, 
            preview_board_width, 
            terminal_height / 2 - game_board_height / 2,
            terminal_width / 2 - game_board_width / 2 - preview_board_width);
            
    std::vector<WINDOW *> windows = {
        whole_screen,
        game_board,
        score_board,
        first_preview,
        second_preview,
        change_box
    };
    
    borders_all(windows, whole_screen);
    //wborder(game_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
    //    ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    mvwprintw(score_board, double_size ? 3 : 2, 1, double_size ? "Current:" : "C:");
    // mvwprintw(score_board, double_size ? 4 : 3, 1, double_size ? "High:" : "H:");
    
    
    wattron(score_board, A_STANDOUT);
    mvwprintw(score_board, 0, 1, " SCORE ");
    
    wattron(first_preview, A_STANDOUT);
    mvwprintw(first_preview, 0, 1, double_size ? " I PREVIEW " : " I ");

    wattron(second_preview, A_STANDOUT);
    mvwprintw(second_preview, 0, 1, double_size ? " II PREVIEW " : " II ");
    
    wattron(change_box, A_STANDOUT);
    mvwprintw(change_box, 0, 1, double_size ? " HOLD PIECE " : " HOLD ");

    refresh_all(windows);
    
    // use_default_colors();

    short r, g, b;
    color_content(COLOR_RED, &r, &g, &b);  

    r = std::clamp(r + 200, 0, 1000);
    g = std::clamp(g + 200, 0, 1000);
    b = std::clamp(b + 200, 0, 1000);

    init_color(COLOR_RED, r, g, b);

    init_pair(1, COLOR_RED, -1);
    
    dataStream ds;
    
    setUpGame(ds, blockList, TOTALBLOCKS);
    addFallingBlock(ds, getNext(ds, blockList, TOTALBLOCKS));
    
    
    using clock = std::chrono::steady_clock;
    auto last_drop = clock::now();
    int drop_interval_ms = 500;
    
    int character;

    int show_controls{1};

    while ((character = wgetch(whole_screen))) {
        drop_interval_ms = 500;
        switch (character) {
            case 'a':
            moveBlockLeft(ds);
            break;
            case 'd':
            moveBlockRight(ds);
            break;
            case 'w':
            rotateBlockRight(ds);
            break;
            case 'q':
            // delwin(whole_screen);??????????
            endwin();
            return 0;
            case 'p':
            show_controls++;
            break;
            case ' ':
            while(!fallFurtherDown(ds));
            lockFallingBlock(ds);
            clearFallingBlock(ds);
            addFallingBlock(ds, getNext(ds, blockList, TOTALBLOCKS));
            break;
            case 's':
            drop_interval_ms = 50;
            break;
            case 'e':
            changeHold(ds, blockList, TOTALBLOCKS);

        }

        // ---------------------------- CLOCK -------------------------------------
        
        auto now = clock::now();
        // int interval = get_interval(ds.level);
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_drop).count();
        checkAndClearLine(ds);
        if(isGameJoever(ds)){ endwin(); return 0; }
        if (elapsed >= drop_interval_ms) {
            if (fallFurtherDown(ds)) {
                lockFallingBlock(ds);
                clearFallingBlock(ds);
                addFallingBlock(ds, getNext(ds, blockList, TOTALBLOCKS));
            }
            last_drop = now;
        }

        // ---------------------------------------------------------------------------------------

        combineFrames(ds);

        // ---------------------------- UPDATES EVERYTHING ---------------------------------------

        draw_dots(game_board, game_board_height, game_board_width, double_size);
        draw_board(game_board, double_size, ds);
        draw_score(score_board, score_board_height, score_board_width, double_size, ds.score);
        
        draw_side_boxes(first_preview, second_preview, change_box, preview_board_height, preview_board_width, double_size, ds);

        refresh_all(windows);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

// -------------------------------------------------------------------------------------------------

void print_help(void) {
    std::cout 
        << "Controls:\n"
        << "q - closes tetris\n";
}

void print_version(void) {
    std::cout 
        << "Versions:\n"
        << "blablabla!\n";
}

void refresh_all(std::vector<WINDOW *> windows) {
    for (auto window : windows) {
        wrefresh(window);
    }
}

void borders_all(std::vector<WINDOW *> windows, WINDOW * ignore) {
    for (auto window : windows) {
        if (window == ignore) {
            continue;
        }
        
        wattron(window, A_BOLD);
        box(window, 0, 0);
        wattroff(window, A_BOLD);
    }
}

void draw_dots(WINDOW * w, int height, int width, int d) {
    wattroff(w, A_STANDOUT);
    for (int i{}; i < (d ? (height-2) / 2 : height-2); i++) {
        for (int j{}; j < (d ? (width-2) / 4 : (width-2) / 2); j++) {
            if (d) {
                mvwprintw(w, i * 2 + 1, j * 4 + 1, "    ");
                mvwprintw(w, i * 2 + 2, j * 4 + 1, ".   ");
            } else {
                mvwprintw(w, i +1, j * 2 + 1, ". ");
            }
        }   
    }
}

void draw_board(WINDOW * w, int d, dataStream ds) {
    for (int row{}; row < ROWS; row++) {
        for (int column{}; column < COLUMNS; column++) {
            int num = ds.entireGame[row][column];
            if (num) {
                draw_block(w, num, row, column, d);
            }
        }
    }
}

void draw_block(WINDOW* w, int n, int row, int column, int size) {
    wattron(w, A_STANDOUT);
    switch (n) {
        
    case 1:
        // mvwprintw(w, 1, 10, "%d", n);
        break;
        
        default:
        break;
    }
    if (size) {
        mvwprintw(w, row * 2 + 1, column * 4 + 1, "    ");
        mvwprintw(w, row * 2 + 2, column * 4 + 1, ".   ");
    } else {
        mvwprintw(w, row +1, column * 2 + 1, ". ");
    }
}

void draw_score(WINDOW* w, int height, int width, int d, unsigned long score) {
    
    wattroff(w, A_STANDOUT);
    mvwprintw(w, d ? 3 : 2, d ? 11 : 5, "%lu", score);
}


void draw_side_boxes(WINDOW *first, WINDOW *second, WINDOW *hold, int height, int width, int d, dataStream ds) {

    // ----------------------------------------- FIRST PREVIEW -------------------------------------------
    draw_dots(first, height, width, d);

    for (int row{}; row < height; row++) {
        for (int column{}; column < width; column++) {
            int num = ds.nextBlock.flat[row][column];
            if (num) {
                draw_block(first, num, ds.nextBlock.blockType == 2 ? row : row+1, column+1, d);
            }
        }
    }

    // ----------------------------------------- SECOND PREVIEW -------------------------------------------
    draw_dots(second, height, width, d);

    for (int row{}; row < height; row++) {
        for (int column{}; column < width; column++) {
            int num = ds.nextNextBlock.flat[row][column];
            if (num) {
                draw_block(second, num, ds.nextNextBlock.blockType == 2 ? row : row+1, column+1, d);
            }
        }
    }

    // ----------------------------------------- HOLD BOX -------------------------------------------
    draw_dots(hold, height, width, d);
    
    if (ds.holdsBlock) {

        for (int row{}; row < height; row++) {
            for (int column{}; column < width; column++) {
                int num = ds.holdingBlock.flat[row][column];
                if (num) {
                    draw_block(hold, num, ds.holdingBlock.blockType == 2 ? row : row+1, column+1, d);
                }
            }
        }
    }
    
}