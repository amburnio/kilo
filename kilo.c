#include "kilo.h"

struct termios orig_termios;

int main(void) {
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        }
        else {
            printf("%d ('%c')\r\n", c, c);
        }
    }
    return 0;
}

void enableRawMode(void) {
    atexit(disableRawMode);

    // Get current terminal attributes
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;

    // Turn off various flags in order to enter raw mode
    raw.c_iflag &= ~(ICRNL | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    // Set terminal attributes
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode(void) {
    // Set terminal attributes to original state
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
