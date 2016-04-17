#ifndef MAIN_H
#define MAIN_H

# include <windows.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>

# define PATH_DLL   "../DLL/CCAPI.dll"
# define CCAPI_OK   0

typedef unsigned char           u8;
typedef unsigned int            u32;
typedef unsigned long long int  u64;

typedef struct ConsoleInfoList  ConsoleInfoList;
typedef struct ConsoleInfo      ConsoleInfo;

void    Menu(const HINSTANCE CCAPI, const u32 pid);

#endif
