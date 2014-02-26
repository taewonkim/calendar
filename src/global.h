#ifndef __H_GLOBAL__
#define __H_GLOBAL__

#define INVALID_VALUE           255

#define MAX_MONTH_COUNT          12
#define WEEK_OF_SIZE              3
#define DAYS_NORM_MONTH_TWO      28
#define DAYS_LEAP_MONTH_TWO      29

// redefine   signed type.
typedef signed   char  s8;
typedef signed   short s16;
typedef signed   int   s32;

// redefine unsigned type.
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// I defined BOOL type, 
// Because C Language is not supported Boolean type.
enum BOOL {
	false = 0, true
};

typedef enum BOOL bool;

#endif
