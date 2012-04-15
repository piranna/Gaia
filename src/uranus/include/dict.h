/*
 * dict.h
 *
 * Implements a key-value dictionary sorted alphabetically
 *
 *  Created on: 30/12/2011
 *      Author: piranna
 */

#ifndef DICT_H_
#define DICT_H_

typedef struct
{
	char* key;
	void* value;
} pairKeyValue;

typedef struct
{
	pairKeyValue pair;
	dict* next;
} dict;

void dict_init(dict* dict);

void  dict_del(dict* dict, char* key);
void* dict_get(dict* dict, char* key);
void  dict_set(dict* dict, char* key, void* value);

#endif /* DICT_H_ */
