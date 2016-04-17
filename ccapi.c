#include "includes/ccapi.h"

void                memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}

char                *strdup(const char *s1)
{
    const size_t len    = strlen(s1) + 1;
    char        *p      = malloc(len);

    return (p ? memcpy(p, s1, len) : NULL);
}

int                 SetMemory(const HINSTANCE CCAPI, u32 pid, u64 offset, u32 size, const void *data)
{
    CCAPI_SetMemory SetMemory = (CCAPI_SetMemory)GetProcAddress(CCAPI, "CCAPISetMemory");
    assert(SetMemory && "Can't load SetMemory function from CCAPI.dll");

    return (SetMemory(pid, offset, size, data));
}

char                *GetProcessName(const HINSTANCE CCAPI, u32 pid)
{
    CCAPI_GetProcessName GetProcessName = (CCAPI_GetProcessName)GetProcAddress(CCAPI, "CCAPIGetProcessName");
    assert(GetProcessName && "Can't load GetProcessName function from CCAPI.dll");

    ProcessName name;
    if (GetProcessName(pid, &name) == CCAPI_OK)
        return (strdup(name.value));
    return (NULL);
}

bool                GetProcessList(const HINSTANCE CCAPI, u32 **pids, u32 *npid)
{
    CCAPI_GetProcessList GetProcessList = (CCAPI_GetProcessList)GetProcAddress(CCAPI, "CCAPIGetProcessList");
    assert(GetProcessList && "Can't load GetProcessList function from CCAPI.dll");

    GetProcessList(npid, 0);

    *pids = (u32 *)malloc(*npid * sizeof(u32));
    if (*pids)
    {
        if (GetProcessList(npid, *pids) == CCAPI_OK)
            return (true);
    }
    return (false);
}

bool                AttachProcess(const HINSTANCE CCAPI, u32 *pid)
{
    size_t  count;
    u32     *pids;
    char    *pname;

    bool result = GetProcessList(CCAPI, &pids, &count);
    if (!result)
        return (result);
    for (unsigned int i = 0; i < count; ++i)
    {
        if ((pname = GetProcessName(CCAPI, pids[i])))
        {
            if (!strstr(pname, "flash"))
            {
                *pid = pids[i];
                break;
            }
            else
                result = false;
        }
    }
    memdel((void **)&pids);
    return (result);
}

ConsoleInfo         *GetIPCIL(const ConsoleInfoList *cil, const size_t c)
{
    ConsoleInfoList *tmp = (ConsoleInfoList *)cil;
    if (c == 1)
        return (tmp->head);
    if (c == tmp->count)
        return (tmp->tail);
    if (c > (tmp->count / 2) + 1)
    {
        for (unsigned int i = 0; i < (tmp->count - c); ++i)
            tmp->tail = tmp->tail->prev;
        return (tmp->tail);
    }
    for (unsigned int i = 1; i < c; ++i)
        tmp->head = tmp->head->next;
    return (tmp->head);
}

void                clean_stdin(void)
{
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

char                *GetIPConnect(const ConsoleInfoList *cil)
{
    ConsoleInfoList *tmp = (ConsoleInfoList *)cil;
    size_t c;
    while (!((c = getchar()) > '0' && c - '0' <= tmp->count))
        ;
    c -= '0';
    tmp->head = GetIPCIL(tmp, c);
    printf("Console selected: %zu [%s - %s]\n", c, tmp->head->name, tmp->head->ip);

    clean_stdin();
    return (tmp->head->ip);
}

ConsoleInfoList     *ShowIPList(const HINSTANCE CCAPI)
{
    CCAPI_GetConsoleInfo GetConsoleInfo = (CCAPI_GetConsoleInfo)GetProcAddress(CCAPI, "CCAPIGetConsoleInfo");
    assert(GetConsoleInfo && "Can't load GetConsoleInfo function from CCAPI.dll");

    CCAPI_GetNumberOfConsoles GetNumberOfConsoles = (CCAPI_GetNumberOfConsoles)GetProcAddress(CCAPI, "CCAPIGetNumberOfConsoles");
    assert(GetNumberOfConsoles && "Can't load GetNumberOfConsoles function from CCAPI.dll");

    ConsoleInfoList *cil = CIL_new();
    if (!cil)
        return (NULL);

    ConsoleName name;
    ConsoleIp   ip;
    for (int i = 0; i < GetNumberOfConsoles(); ++i)
    {
        GetConsoleInfo(i, &name, &ip);
        cil = CIL_append(cil, name.value, ip.value);
    }

    for (ConsoleInfo *ci = CIL_get_head(cil); ci; ci = CI_get_next(ci))
        CI_print(ci);

    printf("Select an IP Adress (1 .. %zu)\n", cil->count);
    return (cil);
}

int                 ConnectConsole(const HINSTANCE CCAPI)
{
    ConsoleInfoList *cil    = ShowIPList(CCAPI);
    const char      *ip     = GetIPConnect(cil);

    CIL_del(&cil);
    CCAPI_ConnectConsole ConnectConsole = (CCAPI_ConnectConsole)GetProcAddress(CCAPI, "CCAPIConnectConsole");
    assert(ConnectConsole && "Can't load ConnectConsole function from CCAPI.dll");

    CCAPI_VshNotify Notify = (CCAPI_VshNotify)GetProcAddress(CCAPI, "CCAPIVshNotify");
    assert(Notify && "Can't load Notify function from CCAPI.dll");

    CCAPI_GetConnectionStatus GetConnectionStatus = (CCAPI_GetConnectionStatus)GetProcAddress(CCAPI, "CCAPIGetConnectionStatus");
    assert(GetConnectionStatus && "Can't load GetConnectionStatus function from CCAPI.dll");

    if (ConnectConsole(ip) == CCAPI_OK)
        Notify(NotifyCaution, "Connected!");
    int status;
    GetConnectionStatus(&status);
    printf("Status connection: %s\n", status ? "Connected" : "Not connected");
    return (!status);
}
