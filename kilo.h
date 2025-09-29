#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** prototypes ***/

void enableRawMode(void);
void disableRawMode(void);
void die(const char *s);
