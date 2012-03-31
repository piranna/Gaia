#include <video.h>


/* Some screen stuff. */
#define COLUMNS   80		/* The number of columns. */
#define LINES     25		/* The number of lines. */
#define ATTRIBUTE 7			/* The attribute of an character. */
#define VIDEO     0xB8000	/* The video memory address. */

/* Variables. */
//static int xpos;	/* Save the X position. */
//static int ypos;	/* Save the Y position. */
int xpos;	/* Save the X position. */
int ypos;	/* Save the Y position. */

/* Point to the video memory. */
static volatile unsigned char* video = (unsigned char*)VIDEO;


void linefeed(void)
{
	int i = 0;

	// Copy all video buffer one line up
	for(; i < COLUMNS * (LINES-1) * 2; i++)
		*(video + i) = *(video + i + COLUMNS * 2);

	// Empty last line
	for(; i < COLUMNS * LINES * 2; i++)
		*(video + i) = 0;
}
