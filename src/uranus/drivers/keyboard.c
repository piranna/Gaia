/* bkerndev - Bran's Kernel Development Tutorial
 * By:   Brandon F. (friesenb@gmail.com)
 * Desc: Keyboard driver
 *
 * Notes: No warranty expressed or implied. Use at own risk.
 */

#include "syscall_userspace.h"


/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[128] =
{
	0,	// Error code

	27/*ESC*/,     '1','2','3','4','5','6','7','8','9','0',       '-', '=','\b',
	'\t',           'q','w','e','r','t','y','u','i','o','p',      '[', ']','\n',
	0/*LCtrl*/,      'a','s','d','f','g','h','j','k','l',         ';','\'', '`',
	0/*LShift*/,'\\', 'z','x','c','v','b','n','m',      ',','.','/',0/*RShift*/,
	'*',
	0/*LAlt*/,              ' '/*    SpaceBar    */,              0/*CapsLock*/,

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
};

/* Handles the keyboard interrupt */
static void keyboard_handler(registers_t* r)
{
    /* Read from the keyboard's data buffer */
    unsigned char scancode = syscall_inb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if(scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
    	eventmanager_send("putchar",kbdus[scancode]);
    }
}

/* Installs the keyboard handler into IRQ1 */
void keyboard_init(void)
{
	syscall_irq_register_handler(IRQ1, &keyboard_handler);
}
