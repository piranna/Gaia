/* bkerndev - Bran's Kernel Development Tutorial
 * By:   Brandon F. (friesenb@gmail.com)
 * Desc: Keyboard driver
 *
 * Notes: No warranty expressed or implied. Use at own risk.
 */

#include "eventmanager.h"
#include "syscall.h"


/* Handles the keyboard interrupt */
static void keyboard_handler(int dumb)
{
    /* Read from the keyboard's data buffer */
    unsigned char scancode = syscall_inb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if(scancode & 0x80)
    {
        scancode -= 0x80;   // Get key from scancode

    	eventmanager_send("keyboard/release/scancode",scancode);
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

    	eventmanager_send("keyboard/press/scancode",scancode);
    }
}

/* Installs the keyboard handler into IRQ1 */
void keyboard_init(void)
{
//	eventmanager_attach("IRQ/1", &keyboard_handler);
	eventmanager_attach("irq/1", keyboard_handler);
}
