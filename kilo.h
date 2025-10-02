#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** defines ***/

#define CTRL_KEY(k) ((k) & 0x1f)

/*** prototypes ***/

void enableRawMode(void);
void disableRawMode(void);
void die(const char *s);
char editorReadKey(void);
void editorProcessKeypress(void);
