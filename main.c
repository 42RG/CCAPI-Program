# include "includes/main.h"
# include "includes/ccapi.h"

int     main(void)
{
    const HINSTANCE CCAPI = LoadLibrary(PATH_DLL);
    assert(CCAPI && "Move CCAPI.dll in executable path");

    const int ret_cc = ConnectConsole(CCAPI);
    assert(ret_cc == CCAPI_OK && "Can't connect to PS3");

    u32 pid;
    const bool ret_ap = AttachProcess(CCAPI, &pid);
    assert(ret_ap != CCAPI_OK && "Can't attach default process game");

    Menu(CCAPI, pid);

    FreeLibrary(CCAPI);
    return (0);
}
