#include "main.h"

int main(int argc, char* argv[]) {
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


        
    //------------------------------------- GETTING READY FOR GAME ----------------------------------------------



    initscr();
    noecho();
    curs_set(0);

    int terminal_height, terminal_width;
    int box_x{ 0 };
    int box_y{ 0 };

    getmaxyx(stdscr, terminal_height, terminal_width); // Terminali akna suuruste saamine

    WINDOW* whole_screen = newwin(terminal_height, terminal_width, box_y, box_x);

    nodelay(whole_screen, TRUE);
    if (terminal_height < 23 or terminal_width < 59) {
        // wattron(whole_screen, A_STANDOUT);

        mvwprintw(whole_screen, terminal_height / 2, terminal_width / 2 - (21 / 2), "Make terminal bigger!");
        wrefresh(whole_screen);
        sleep(2);
        endwin();
        return 0;
        }

    if (has_colors()) {
        start_color();
        if (can_change_color()) {
            use_default_colors();
            enable_soft_tetris_palette();  // Custom function you'll define
            set_background(whole_screen, terminal_height, terminal_width);
            } else {
            enable_basic_palette();        // Fallback to 8 standard colors
            }
        }

    WINDOW* game_board;
    WINDOW* score_board;
    WINDOW* first_preview;
    WINDOW* second_preview;
    WINDOW* change_box;

    // Defiing window default sizes
    int double_size{};

    int game_board_height{ ROWS };
    int game_board_width{ COLUMNS * 2 }; // Times two because one block consists of two spaces - Original Tetris grid is 10 x 20

    int score_board_height{ 3 };
    int score_board_width{ 10 };

    int preview_board_height{ 4 };
    int preview_board_width{ 10 };

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

    std::vector<WINDOW*> windows = {
        whole_screen,
        game_board,
        score_board,
        first_preview,
        second_preview,
        change_box
        };

    set_background(score_board, score_board_height, score_board_width);

    borders_all(windows, whole_screen);

    mvwprintw(score_board, double_size ? 3 : 2, 1, double_size ? "Current:" : "C:");
    // mvwprintw(score_board, double_size ? 4 : 3, 1, double_size ? "High:" : "H:");

    wattron(score_board, A_STANDOUT);
    mvwprintw(score_board, 0, 1, " SCORE ");

    wattron(first_preview, A_STANDOUT);
    mvwprintw(first_preview, 0, 1, " I ");

    wattron(second_preview, A_STANDOUT);
    mvwprintw(second_preview, 0, 1, " II ");

    wattron(change_box, A_STANDOUT);
    mvwprintw(change_box, 0, 1, " HOLD ");

    refresh_all(windows);

    dataStream ds;

    setUpGame(ds, blockList, TOTALBLOCKS);
    addFallingBlock(ds, getNext(ds, blockList, TOTALBLOCKS));


    using clock = std::chrono::steady_clock;
    auto last_drop = clock::now();
    int drop_interval_ms = 500;

    int character;

    int show_controls{};



    // ----------------------------------------------------- LOOP TIME ---------------------------------------------- 



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
                endwin();
                return 0;
            case 'h':
                show_controls < 1 ? show_controls++ : show_controls--;
                break;
            case ' ':
                while (!fallFurtherDown(ds));
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
        if (isGameJoever(ds)) { endwin(); return 0; }
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

        draw_help_text(whole_screen, terminal_height, terminal_width, show_controls);

        // ---------------------------------------------------------------------------------------

        refresh_all(windows);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    return 0;
    }



// -------------------------------------------- FUNCTION DEFINITIONS -------------------------------------------



void print_help(void) {
    std::cout
        << "Controls:\n"
        << "q - closes tetris\n"
        << "Ingame controls:\n"
        << "e - holds the current block\n"
        << "w - rotates the current block\n"
        << "s - speed up button\n"
        << "a/d - move left/right\n"
        << "space - teleport down\n"
        << "alt+f4 - weak mans tool\n";

    }

void print_version(void) {
    std::random_device rng;
    std::cout
        << "Versions:\n"
        << "1.0\n";
    if (rng() % 10 < 2) {
        std::cout << R"(
  |\__/,|   (`\
  |_ _  |.--.) )
  ( T   )     /
 (((^_(((/(((_>
)";
        } else if (rng() % 10 < 3) {
            std::cout << R"(
             *     ,MMM8&&&.            *
                  MMMM88&&&&&    .
                 MMMM88&&&&&&&
     *           MMM88&&&&&&&&
                 MMM88&&&&&&&&
                 'MMM88&&&&&&'
                   'MMM8&&&'      *    
          |\___/|     /\___/\
          )     (     )    ~( .              '
         =\     /=   =\~    /=
           )===(       ) ~ (
          /     \     /     \
          |     |     ) ~   (
         /       \   /     ~ \
         \       /   \~     ~/
  jgs_/\_/\__  _/_/\_/\__~__/_/\_/\_/\_/\_/\_
  |  |  |  |( (  |  |  | ))  |  |  |  |  |  |
  |  |  |  | ) ) |  |  |//|  |  |  |  |  |  |
  |  |  |  |(_(  |  |  (( |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |\)|  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
)";
            }
    }

void refresh_all(std::vector<WINDOW*> windows) {
    for (auto window : windows) {
        wrefresh(window);
        }
    }

void borders_all(std::vector<WINDOW*> windows, WINDOW* ignore) {
    for (auto window : windows) {
        if (window == ignore) {
            continue;
            }

        wattron(window, A_BOLD);
        wattron(window, COLOR_PAIR(8));

        wattron(window, A_STANDOUT);
        box(window, 0, 0);
        wattroff(window, A_BOLD);
        }
    }

void draw_dots(WINDOW* w, int height, int width, int d) {

    wattron(w, COLOR_PAIR(8));
    wattron(w, A_STANDOUT);

    for (int i{}; i < (d ? (height - 2) / 2 : height - 2); i++) {
        for (int j{}; j < (d ? (width - 2) / 4 : (width - 2) / 2); j++) {

            if (d) {
                mvwprintw(w, i * 2 + 1, j * 4 + 1, "    ");
                mvwprintw(w, i * 2 + 2, j * 4 + 1, ".   ");
                } else {
                mvwprintw(w, i + 1, j * 2 + 1, ". ");
                }
            }
        }
    }

void draw_board(WINDOW* w, int d, dataStream ds) {
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
    wattron(w, COLOR_PAIR(n));
    if (size) {
        mvwprintw(w, row * 2 + 1, column * 4 + 1, "    ");
        mvwprintw(w, row * 2 + 2, column * 4 + 1, ".   ");
        } else {
        mvwprintw(w, row + 1, column * 2 + 1, ". ");
        }
    wattroff(w, COLOR_PAIR(n));
    }

void draw_score(WINDOW* w, int height, int width, int d, unsigned long score) {
    // wattroff(w, A_STANDOUT);
    mvwprintw(w, d ? 3 : 2, d ? 11 : 5, "%lu", score);
    }


void draw_side_boxes(WINDOW* first, WINDOW* second, WINDOW* hold, int height, int width, int d, dataStream ds) {

    // ----------------------------------------- FIRST PREVIEW -------------------------------------------
    draw_dots(first, height, width, d);

    for (int row{}; row < height; row++) {
        for (int column{}; column < width; column++) {
            int num = ds.nextBlock.flat[row][column];
            if (num) {
                draw_block(first, num, ds.nextBlock.blockType == 2 ? row : row + 1, column + 1, d);
                }
            }
        }

    // ----------------------------------------- SECOND PREVIEW -------------------------------------------
    draw_dots(second, height, width, d);

    for (int row{}; row < height; row++) {
        for (int column{}; column < width; column++) {
            int num = ds.nextNextBlock.flat[row][column];
            if (num) {
                draw_block(second, num, ds.nextNextBlock.blockType == 2 ? row : row + 1, column + 1, d);
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
                    draw_block(hold, num, ds.holdingBlock.blockType == 2 ? row : row + 1, column + 1, d);
                    }
                }
            }
        }

    }

void enable_soft_tetris_palette() {

    init_color(12, 0xf5 * 4, 0x7d * 4, 0x26 * 4);
    init_color(13, 0xf8 * 4, 0x55 * 4, 0x52 * 4);
    init_color(14, 0xdf * 4, 0xa0 * 4, 0x00 * 4);
    init_color(15, 0x8d * 4, 0xa1 * 4, 0x01 * 4);
    init_color(16, 0x3a * 4, 0x94 * 4, 0xc5 * 4);
    init_color(17, 0x35 * 4, 0xa7 * 4, 0x7c * 4);
    init_color(18, 0xdf * 4, 0x69 * 4, 0xba * 4);

    init_color(19, 0xf2 * 4, 0xef * 4, 0xdf * 4); //BG

    init_pair(1, 12, -1);
    init_pair(2, 13, -1);
    init_pair(3, 14, -1);
    init_pair(4, 15, -1);
    init_pair(5, 16, -1);
    init_pair(6, 17, -1);
    init_pair(7, 18, -1);

    init_pair(8, 19, -1); //BG
    }

void enable_basic_palette() {
    init_pair(1, COLOR_CYAN, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, COLOR_MAGENTA, -1);
    init_pair(4, COLOR_GREEN, -1);
    init_pair(5, COLOR_RED, -1);
    init_pair(6, COLOR_BLUE, -1);
    init_pair(7, COLOR_WHITE, -1);  // As orange fallback
    }

void set_background(WINDOW* w, int height, int width) {
    wattron(w, COLOR_PAIR(8));
    wattron(w, A_STANDOUT);

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            mvwprintw(w, i, j, " ");
            }
        }
    clear();
    refresh();
    }

void draw_help_text(WINDOW* w, int height, int width, int status) {
    if (status) {
        mvwprintw(w, height - 9, 2, "A: left");
        mvwprintw(w, height - 8, 2, "D: right");
        mvwprintw(w, height - 7, 2, "W: rotate");
        mvwprintw(w, height - 6, 2, "E: hold");
        mvwprintw(w, height - 5, 2, "Space: down");
        mvwprintw(w, height - 4, 2, "S: faster");
        mvwprintw(w, height - 3, 2, "Q: quit");
        mvwprintw(w, height - 2, 2, "H: close help    ");
        } else {
        for (size_t i = 0; i < 7; i++) {
            mvwprintw(w, height - 3 - i, 2, "           ");
            }
        mvwprintw(w, height - 2, 2, "Press H for help!");
        }
    }