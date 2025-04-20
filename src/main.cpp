
#include <curses.h>
#include <iostream>


int main(int argc, char *argv[]) {
    initscr();
    noecho();
    curs_set(0);

    int box_height, box_width;
    int terminal_height, terminal_width;
    int box_x{2};
    int box_y{1};
    
    getmaxyx(stdscr, terminal_height, terminal_width);
    
    box_height = terminal_height - 2;
    box_width = terminal_width - 4;

    WINDOW *window = newwin(box_height, box_width, box_y, box_x);
    
    nodelay(window, TRUE);
    
    box(window, 0, 0);
    wrefresh(window);

    getch();

    delwin(window);
    endwin();
    
    return 0;
}
