
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

    WINDOW *game_board;

    WINDOW *score_board;
    WINDOW *first_preview;
    WINDOW *second_preview;
    WINDOW *third_preview;

    WINDOW *change_box;


    // Defiing window default sizes
    int does_size_matter{};

    int game_board_height{20};
    int game_board_width{10 * 2}; // Times two because one block consists of two spaces - Original Tetris grid is 10 x 20

    int score_board_height{3};
    int score_board_width{10};

    int preview_board_height{4};
    int preview_board_width{10};



    if (terminal_height < 23 or terminal_width < 48) {
        mvwprintw(whole_screen, terminal_height / 2, terminal_width / 2 - 33 / 2, "Too small, make terminal bigger!" );
        does_size_matter = 1;

    } else if (terminal_height > 43) {
        // Makes every window 2 times larger
        game_board_height *= 2;
        game_board_width *= 2;

        score_board_height += 2;
        score_board_width *= 2;

        preview_board_height *= 2;
        preview_board_width *= 2;
    }
    
    nodelay(whole_screen, TRUE);
    
    // box(whole_screen, 0, 0);

    
    if (!does_size_matter) {

        game_board_height += 2;
        game_board_width += 2;

        score_board_height += 2;
        score_board_width += 2;

        preview_board_height += 2;
        preview_board_width += 2;


        game_board  = newwin(
            game_board_height, 
            game_board_width, 
            terminal_height / 2 - game_board_height / 2, 
            terminal_width / 2 - game_board_width / 2);

        box(game_board,0 ,0);

        score_board = newwin(
            score_board_height, 
            score_board_width,
            terminal_height / 2 - game_board_height / 2,
            terminal_width / 2 + game_board_width / 2);

        box(score_board,0 ,0);

        first_preview = newwin(
            preview_board_height, 
            preview_board_width, 
            terminal_height / 2 - game_board_height / 2 + score_board_height,
            terminal_width / 2 + game_board_width / 2);

        box(first_preview, 0, 0);

        second_preview = newwin(
            preview_board_height, 
            preview_board_width, 
            terminal_height / 2 - game_board_height / 2 + score_board_height + preview_board_height,
            terminal_width / 2 + game_board_width / 2);

        box(second_preview, 0, 0);

        third_preview = newwin(
            preview_board_height, 
            preview_board_width, 
            terminal_height / 2 - game_board_height / 2 + score_board_height + preview_board_height * 2,
            terminal_width / 2 + game_board_width / 2);

        box(third_preview, 0, 0);

        change_box = newwin(
            preview_board_height, 
            preview_board_width, 
            terminal_height / 2 - game_board_height / 2,
            terminal_width / 2 - game_board_width / 2 - preview_board_width);

        box(change_box, 0, 0);

    }

    wrefresh(whole_screen);
    if (!does_size_matter) {
        wrefresh(game_board);
        wrefresh(score_board);
        wrefresh(first_preview);
        wrefresh(second_preview);
        wrefresh(third_preview);
        wrefresh(change_box);
    }

    int character;

    while ((character = wgetch(whole_screen))) {
        switch (character) {
          case '\t':
            break;
          case 'l':
            break;
          case 'k':
            break;
          case '\n':
            break;
          case 'q':
            // delwin(whole_screen);??????????
            endwin();
            exit(0);
        }
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