/*
 * date.c
 *
 *  Created on: 02/04/2012
 *      Author: piranna
 */

// Command that print the current date requesting it throught events system


#include <stdio.h>


static void date_callback(int ticks)
{
	printf("%d ticks since power-on\n", ticks);
}

void date_run(char* line)
{
	eventmanager_send("date", date_callback);
}
