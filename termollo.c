
#include "piccolo/include.h"
#include "ncurses.h"
#include <stdio.h>

#define FN_SIGNATURE(name) piccolo_Value name (struct piccolo_Engine* engine, int argc, piccolo_Value* argv, piccolo_Value self)

int colorPairs[8][8];
int currPair;
FN_SIGNATURE(refresh_) {
    refresh();
    currPair = 1;
    for(int fg = 0; fg < 8; fg++)
        for(int bg = 0; bg < 8; bg++)
            colorPairs[fg][bg] = -1;
    return PICCOLO_NIL_VAL();
}

FN_SIGNATURE(init) {
    initscr();
    refresh();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    curs_set(0);
    refresh_(engine, 0, NULL, PICCOLO_NIL_VAL());
    return PICCOLO_NIL_VAL();
}

FN_SIGNATURE(stop) {
    endwin();
    return PICCOLO_NIL_VAL();
}

FN_SIGNATURE(print) {
    int y = PICCOLO_AS_NUM(argv[0]);
    int x = PICCOLO_AS_NUM(argv[1]);
    struct piccolo_ObjString* str = PICCOLO_AS_OBJ(argv[2]);
    mvprintw(y, x, str->string);
    return PICCOLO_NIL_VAL();
}

FN_SIGNATURE(input) {
    int in = getch();
    return PICCOLO_NUM_VAL(in);
}

FN_SIGNATURE(setColor) {
    int fg = PICCOLO_AS_NUM(argv[0]);
    int bg = PICCOLO_AS_NUM(argv[1]);
    if(colorPairs[fg][bg] == -1) {
        init_pair(currPair, fg, bg);
        colorPairs[fg][bg] = currPair;
        if(currPair < 8)
            currPair++;
    }
    attrset(COLOR_PAIR(colorPairs[fg][bg]));
    return PICCOLO_NIL_VAL();
}