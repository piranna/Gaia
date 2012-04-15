/*
 * keyboard_layouts.h
 *
 *  Created on: 11/01/2012
 *      Author: piranna
 */

#ifndef KEYBOARD_LAYOUTS_H_
#define KEYBOARD_LAYOUTS_H_

#define KB_NORMAL 0
#define KB_SHIFT  1
#define KB_CTRL   2
#define KB_ALT    4

// Typedef to define available keyboard layouts (currently only up to KB_SHIFT)
typedef char keyboard_layout[1 + KB_SHIFT][128];

#endif /* KEYBOARD_LAYOUTS_H_ */
