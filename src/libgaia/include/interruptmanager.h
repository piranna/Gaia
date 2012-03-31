/*
 * interruptmanager.h
 *
 *  Created on: 09/01/2012
 *      Author: piranna
 */

#ifndef INTERRUPTMANAGER_H_
#define INTERRUPTMANAGER_H_

typedef void (*t_em_send)(char*,int);

void set_eventmanager_send(t_em_send em_send);

void interruptmanager_init(void);

#endif /* INTERRUPTMANAGER_H_ */
