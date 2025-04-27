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
    }
    
    WINDOW *game_board;
    
    WINDOW *score_board;
    WINDOW *first_preview;
    WINDOW *second_preview;
    WINDOW *third_preview;
    
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
            
    third_preview = newwin(
        preview_board_height, 
        preview_board_width, 
        terminal_height / 2 - game_board_height / 2 + score_board_height + preview_board_height * 2,
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
        third_preview,
        change_box
    };
    
    borders_all(windows, whole_screen);
    
    mvwprintw(score_board, double_size ? 2 : 1, 1, double_size ? "Current:" : "C:");
    mvwprintw(score_board, double_size ? 4 : 3, 1, double_size ? "High:" : "H:");
    
    
    wattron(score_board, A_STANDOUT);
    mvwprintw(score_board, 0, 1, " SCORE ");
    
    wattron(first_preview, A_STANDOUT);
    mvwprintw(first_preview, 0, 1, double_size ? " I PREVIEW " : " I ");

    wattron(second_preview, A_STANDOUT);
    mvwprintw(second_preview, 0, 1, double_size ? " II PREVIEW " : " II ");
    
    wattron(third_preview, A_STANDOUT);
    mvwprintw(third_preview, 0, 1, double_size ? " III PREVIEW " : " III ");
    
    wattron(change_box, A_STANDOUT);
    mvwprintw(change_box, 0, 1, double_size ? " NEXT PIECE " : " NEXT ");

    refresh_all(windows);
    
    
    


    start_color();
    // use_default_colors();

    short r, g, b;
    color_content(COLOR_RED, &r, &g, &b);  

    r = std::clamp(r + 200, 0, 1000);
    g = std::clamp(g + 200, 0, 1000);
    b = std::clamp(b + 200, 0, 1000);

    init_color(COLOR_RED, r, g, b);

    init_pair(1, COLOR_RED, -1);
    
    dataStream ds;
    
    addFallingBlock(ds, TSquare);
    
    int character;
    
    using clock = std::chrono::steady_clock;
    auto last_drop = clock::now();
    const int drop_interval_ms = 500;


    // auto get_interval = [&](int level){
    //     int iv = base_interval_ms - level * level_speed_decrement;
    //     return std::max(50, iv);                  // never faster than 50ms
    // };

    // int i{};

    while ((character = wgetch(whole_screen))) {
        switch (character) {
            case 'a':
            moveBlockLeft(ds);
            break;
            case 'd':
            moveBlockRight(ds);
            break;
            case ' ':
            rotateBlockRight(ds);
            break;
            case '\n':
            lockFallingBlock(ds);
            break;
            case 'q':
            // delwin(whole_screen);??????????
            endwin();
            return 0;
        }
        
        // mvwprintw(game_board, 0, 0, "%d", i++);
        
        
        
        
        
        // while (!hasHitRockBottom(ds)) {
        //     fallFurtherDown(ds);
        // }
        
        // lockFallingBlock(ds);
        // clearFallingBlock(ds);
        // addFallingBlock(ds, Line);
        
        auto now = clock::now();
        // int interval = get_interval(ds.level);
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_drop).count();

        if (elapsed >= drop_interval_ms) {

            if (fallFurtherDown(ds)) {
                lockFallingBlock(ds);
                clearFallingBlock(ds);
                addFallingBlock(ds, Line);
            }
            last_drop = now;
        }
        
        
        combineFrames(ds);
        draw_dots(game_board, game_board_height, game_board_width, double_size);
        draw_board(game_board, double_size, ds);
        wrefresh(game_board);
        
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

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
            mvwprintw(w, d ? i * 2 + 2: i +1, d ? j * 4 + 1: j * 2 + 1, ". ");
        }   
    }
}

void draw_board(WINDOW * w, int d, dataStream ds) {
    for (int row{}; row < ROWS; row++) {
        for (int column{}; column < COLUMNS; column++) {
            int num = ds.entireGame[row][column];
            if (num) {
                // mvwprintw(w, 0, 10, "Going to!");
                draw_block(w, num, row, column);
            }
        }
    }
}

void draw_block(WINDOW* w, int n, int row, int column) {
    wattron(w, A_STANDOUT);
    switch (n) {
        
    case 1:
        // mvwprintw(w, 1, 10, "%d", n);
        break;
        
        default:
        break;
    }
    mvwprintw(w, row + 1, column * 2 + 1, ". ");
}