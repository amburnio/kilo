#include "kilo.h"

/*** data ***/

struct termios orig_termios;

/*** init ***/

int main(void) {
    enableRawMode();

    while (1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}

/*** terminal ***/

void enableRawMode(void) {
    atexit(disableRawMode);

    // Get current terminal attributes
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    struct termios raw = orig_termios;

    // Turn off various flags in order to enter raw mode
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    // Set terminal attributes
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void disableRawMode(void) {
    // Set terminal attributes to original state
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void die(const char *s) {
    perror(s);
    exit(1);
}

char editorReadKey(void) {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}

/*** output ***/

void editorRefreshScreen(void) {
    // Clear entire screen
    write(STDOUT_FILENO, "\x1b[2J", 4);

    // Reposition the cursor at the first row and column
    write(STDOUT_FILENO, "\x1b[H", 3);
}

/*** input ***/

void editorProcessKeypress(void) {
    char c = editorReadKey();

    switch (c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}
