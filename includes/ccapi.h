#ifndef CCAPI_H
# define CCAPI_H

# include "main.h"
# include "consoleinfo.h"

typedef enum NotifyIcon
{
    NotifyInfo,
    NotifyCaution,
    NotifyFriend,
    NotifySlider,
    NotifyWrongWay,
    NotifyDialog,
    NotifyDalogShadow,
    NotifyText,
    NotifyPointer,
    NotifyGrab,
    NotifyHand,
    NotifyPen,
    NotifyFinger,
    NotifyArrow,
    NotifyArrowRight,
    NotifyProgress,
    NotifyTrophy1,
    NotifyTrophy2,
    NotifyTrophy3,
    NotifyTrophy4
} NotifyIcon;

typedef struct ConsoleName
{
   char value[256];
} ConsoleName;

typedef struct ConsoleIp
{
   char value[256];
} ConsoleIp;

typedef struct ProcessName
{
    char value[512];
} ProcessName;

typedef int(*CCAPI_ConnectConsole)(const char *);
typedef int(*CCAPI_GetConsoleInfo)(int index, ConsoleName *, ConsoleIp *);
typedef int(*CCAPI_GetNumberOfConsoles)(void);
typedef int(*CCAPI_GetConnectionStatus)(int *);
typedef int(*CCAPI_VshNotify)(NotifyIcon, const char *);
typedef int(*CCAPI_GetProcessList)(u32 *, u32 *);
typedef int(*CCAPI_GetProcessName)(u32, ProcessName *);
typedef int(*CCAPI_SetMemory)(u32, u64, u32, const void *);

ConsoleInfoList *ShowIPList(const HINSTANCE CCAPI);
ConsoleInfo     *GetIPCIL(const ConsoleInfoList *cil, const size_t c);
char            *GetIPConnect(const ConsoleInfoList *cil);
char            *GetProcessName(const HINSTANCE CCAPI, u32 pid);
char	        *strdup(const char *s1);
bool            AttachProcess(const HINSTANCE CCAPI, u32 *pid);
bool            GetProcessList(const HINSTANCE CCAPI, u32 **pids, u32 *npid);
int             ConnectConsole(const HINSTANCE CCAPI);
int             SetMemory(const HINSTANCE CCAPI, u32 pid, u64 offset, u32 size, const void *data);
void	        memdel(void **ap);
void            clean_stdin(void);
#endif
