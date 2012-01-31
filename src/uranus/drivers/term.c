/*
 * term.c
 *
 *  Created on: 28/12/2011
 *      Author: piranna
 */

#include "eventmanager.h"

#include "keyboard_layouts.h"


extern keyboard_layout kbdus;

// Use normal keyboard by default
static unsigned char* kbd = kbdus[KB_NORMAL];


static void term_handler_press(unsigned char scancode)
{
	/* Just to show you how this works, we simply translate
	*  the keyboard scancode into an ASCII value, and then
	*  display it to the screen. You can get creative and
	*  use some flags to see if a shift is pressed and use a
	*  different layout, or you can add another 128 entries
	*  to the above layout to correspond to 'shift' being
	*  held. If shift is held using the larger lookup table,
	*  you would add 128 to the scancode when you look for it */

	switch(scancode)
	{
		case 42:    // LShift
		case 54:    // RShift
			kbd = kbdus[KB_SHIFT];
			return;

		case 29:    // CTRL
			return;

		case 56:    // Alt
			return;
	}

	char c = kbd[scancode];

	eventmanager_send("term/press/character", c);

    eventmanager_send("VGA/text/putchar", c);
}

static void term_handler_release(unsigned char scancode)
{
	/* You can use this one to see if the user released the
	*  shift, alt, or control keys... */

	switch(scancode)
	{
		case 42:    // LShift
		case 54:    // RShift
			kbd = kbdus[KB_NORMAL];
			return;

		case 29:    // CTRL
			return;

		case 56:    // Alt
			return;
	}

	eventmanager_send("term/release/character", kbd[scancode]);
}


void term_init(void)
{
	eventmanager_attach("keyboard/press/character",   &term_handler_press);
	eventmanager_attach("keyboard/release/character", &term_handler_release);
}
