#ifndef __stdint_h__
#define __stdint_h__

typedef char           int8_t;
typedef short          int16_t;
typedef int            int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

/* Types for `void *' pointers.  */
#if __WORDSIZE == 64
	#ifndef __intptr_t_defined
		typedef long int intptr_t;
		#define __intptr_t_defined
	#endif

	typedef unsigned long int uintptr_t;
#else
	#ifndef __intptr_t_defined
		typedef int intptr_t;
		#define __intptr_t_defined
	#endif

	typedef unsigned int uintptr_t;
#endif

#endif /* __stdint_h__ */
