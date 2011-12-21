/*
 * fixedDict.h
 *
 * Implements a fixed-size dictionary sorted alphabetically
 *
 *  Created on: 21/12/2011
 *      Author: piranna
 */

#ifndef FIXEDDICT_H_
#define FIXEDDICT_H_

typedef struct
{
	char key[32];
	void* value;
} pairKeyValue;

typedef struct
{
	pairKeyValue* pairs;
	unsigned int length;
} fixedDict;

void  fixedDict_del(fixedDict dict, char* key);
void* fixedDict_get(fixedDict dict, char* key);
void  fixedDict_set(fixedDict dict, char* key, void* value);

#endif /* FIXEDDICT_H_ */
