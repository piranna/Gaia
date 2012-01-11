/*
 * term.c
 *
 *  Created on: 28/12/2011
 *      Author: piranna
 */

#include "eventmanager.h"

#define KB_NORMAL 0
#define KB_SHIFT  1
#define KB_CTRL   2
#define KB_ALT    4


/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
static unsigned char kbdus[1 + KB_SHIFT][128] =
{
	{
		0,	// Error code

		27/*ESC*/,    '1','2','3','4','5','6','7','8','9','0',    '-', '=','\b',
		'\t',          'q','w','e','r','t','y','u','i','o','p',   '[', ']','\n',
		0/*LCtrl*/,     'a','s','d','f','g','h','j','k','l',      ';','\'', '`',
		0/*LShift*/,'\\','z','x','c','v','b','n','m',   ',','.','/',0/*RShift*/,
		'*',
		0/*LAlt*/,             ' '/*    SpaceBar    */,           0/*CapsLock*/,

		/* 59-68 - F1-F10 */
		0,0,0,0,0,0,0,0,0,0,

		0,	/* 69 - NumLock*/
		0,	/* ScrollLock */

		0/*Home */,    0/* ArrowUp   */,0/* PageUp     */,'-',
		0/*ArrowLeft*/,0               ,0/* ArrowRight */,'+',
		0/*79 - End*/, 0/* ArrowDown */,0/* PageDown   */,
		0/*            Ins           */,0/* Del        */,

		0,0,0,

		0/* F11 */,0/* F12 */,

		0,	/* All other keys are undefined */
	},
	{
		0,	// Error code

		0/*ESC*/,     '!','@','#','$','%','^','&','*','(',')',     '_','+','\b',
		0,             'Q','W','E','R','T','Y','U','I','O','P',    '{','}','\n',
		0/*LCtrl*/,     'A','S','D','F','G','H','J','K','L',       ':','"', '~',
		0/*LShift*/, '|','Z','X','C','V','B','N','M',   '<','>','?',0/*RShift*/,
		0,
		0/*LAlt*/,              0/*     SpaceBar     */,          0/*CapsLock*/,

		/* 59-68 - F1-F10 */
		0,0,0,0,0,0,0,0,0,0,

		0,	/* 69 - NumLock*/
		0,	/* ScrollLock */

		0/*Home */,    0/* ArrowUp   */,0/* PageUp     */,'-',
		0/*ArrowLeft*/,0               ,0/* ArrowRight */,'+',
		0/*79 - End*/, 0/* ArrowDown */,0/* PageDown   */,
		0/*            Ins           */,0/* Del        */,

		0,0,0,

		0/* F11 */,0/* F12 */,

		0,	/* All other keys are undefined */
	},
};

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
