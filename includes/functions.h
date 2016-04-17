#ifndef FUNCTIONS_H
#define FUNCTIONS_H

# include "main.h"
# include "ccapi.h"

# define B_SPACE        8
# define DEFAULT_NAME   "born2code42"
# define LOBBY_NAME     "^1Lobby ^21 ^5sp"

void    Menu(const HINSTANCE CCAPI, const u32 pid);
bool    ChangeName(const HINSTANCE CCAPI, const u32 pid);
bool    ChangePrestige(const HINSTANCE CCAPI, const u32 pid);
u32     GetPrestige(void);
char    *GetRealName(const char *str);
char    *GetName(void);
char    *strjoin(const char *s1, const char *s2);
char    *Replace(const char *s1, const char *search, const int r);
u8      GetByte(const u8 *str);
char    *StringToHex(const char *str);
u8      *StringToByteArray(const char *str);

/* -- BO2 Offsets -- */

# define BO2_PRESTIGE_OFFSET    (u32) 0x26FD014
# define BO2_NAME_OFFSET        (u32) 0x026C0658

/* --             -- */

#endif
