/*
 * us.c
 *
 *  Created on: 11/01/2012
 *      Author: piranna
 */

#include "keyboard_layouts.h"


/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
keyboard_layout kbdus =
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
