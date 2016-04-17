# include "includes/functions.h"

u32     GetPrestige(void)
{
    int prst;
    do
    {
        scanf("%d[^\n]", &prst);
    } while (prst < 0);
    return (prst);
}

char    *strjoin(const char *s1, const char *s2)
{
	const size_t    size_s1     = strlen(s1);
	const size_t	size_s2     = strlen(s2);
	char            *strjoin    = malloc(size_s1 + size_s2 + 1);

	if (!strjoin)
		return (NULL);
	strcpy(strjoin, s1);
	strcpy(&strjoin[size_s1], s2);
	strjoin[size_s1 + size_s2 + 1] = '\0';
	return (strjoin);
}

char    *Replace(const char *str, const char *search, const int r)
{
    char *replace   = (char *)str;
    unsigned int i  = 0;
    unsigned int j;

    while (str[i])
    {
        j = 0;
        while (search[j])
        {
            if (str[i] == search[j] &&
                str[i + 1] != '\0' && isdigit((int)str[i + 1]))
                    replace[i] = r;
            j++;
        }
        i++;
    }
    return (replace);
}

char    *GetRealName(const char *str)
{
    char *ptr = (char *)str;

    if (ptr[0] == B_SPACE)
        return (strdup(0));

    if (strchr(ptr, '-'))
    {
        if (!strcmp(ptr, "-def"))
            return (DEFAULT_NAME);
        if (!strcmp(ptr, "-lobby"))
            return (LOBBY_NAME);
        if (ptr[0] == '-' && isdigit((int)ptr[1])
            && !strcmp(&ptr[2], "def"))
        {
            ptr[2] = 0;
            return (strjoin(ptr, DEFAULT_NAME));
        }
    }
    ptr[strlen(ptr)] = 0;
    return (strdup(ptr));
}

char    *GetName(void)
{
    const size_t size = 20;

    char p[size];
    scanf("%[^\n]", p);

    return (GetRealName(p));
}

bool    ChangePrestige(const HINSTANCE CCAPI, const u32 pid)
{
    printf("Set a prestige: ");

    const int prestige  = GetPrestige();
    const int ret       = SetMemory(CCAPI, pid, BO2_PRESTIGE_OFFSET, 1, &prestige);
    if (ret != CCAPI_OK)
    {
        printf("Can't set memory\n");
        return (false);
    }

    printf("Prestige set: %d(0x%02X) [adress: 0x%02X]\n", prestige, prestige, BO2_PRESTIGE_OFFSET);
    return (true);
}

u8      GetByte(const u8 *str)
{
    unsigned char byte = 0;
    for (unsigned int i = 0; i < 2; ++i, ++str)
    {
        unsigned int n = 0;
        if (*str >= '0' && *str <= '9')
            n = *str - '0';
        if (*str >= 'a' && *str <= 'f')
            n = 10 + *str - 'a';
        if (*str >= 'A' && *str <= 'F')
            n = 10 + *str - 'A';
        byte = n + byte * 16;
    }
    return (byte);
}

char    *StringToHex(const char *str)
{
    size_t  len     = strlen(str);
    char    *strhex = malloc(2 * len + 1);
    char    *pos    = strhex;

    for (unsigned int i = 0; i < len; ++i, pos += 2)
        sprintf(pos, "%x", str[i]);
    strhex[2 * len + 1] = '\0';
    return (strhex);
}

u8      *StringToByteArray(const char *str)
{
    char            *s1     = StringToHex(str);
    const u8        *ptr    = (u8 *)s1;
    const size_t    len     = strlen(s1);
    u8              *bytes  = malloc((len / 2) + 1);
    unsigned int    i       = 0;
    unsigned int    j       = 0;

    for (; j < len; ++i, j += 2)
        bytes[i] = GetByte(&ptr[j]);

    bytes[i] = '\0';
    free(s1);
    return (bytes);
}

bool    ChangeName(const HINSTANCE CCAPI, const u32 pid)
{
    printf("Set a new name: ");

    char            *name   = GetName();
    if (!name)
        return (false);
    u8              *ptr    = (u8 *)Replace(name, "$-*", '^');
    const size_t    len     = strlen(name);

    int ret = SetMemory(CCAPI, pid, BO2_NAME_OFFSET, len + 1, ptr);
    if (ret != CCAPI_OK)
    {
        printf("Can't set memory\n");
        return (false);
    }

    printf("New name set: %s [adress: 0x%02X]\n", *name ? name : "empty name", BO2_NAME_OFFSET);
    free(name);
    return (true);
}

void    Menu(const HINSTANCE CCAPI, const u32 pid)
{
    u32 choice;
    do
    {
        printf( "0) Quit\n"
                "1) Change prestige\n"
                "2) Change name\n> ");
        while (!((choice = getchar()) >= '0' && choice <= '2'))
            ;
        clean_stdin();
        if (choice == '1')
            choice = !ChangePrestige(CCAPI, pid) ? '0' : choice;
        if (choice == '2')
            choice = !ChangeName(CCAPI, pid) ? '0' : choice;
    } while (choice != '0');
}
