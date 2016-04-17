# include "includes/consoleinfo.h"

ConsoleInfo         *CI_new(const char *name, const char *ip, ConsoleInfo *prev, ConsoleInfo *next)
{
    ConsoleInfo *list;
    if ((list = malloc(sizeof(ConsoleInfo))))
    {
        list->name  = strdup(name);
        list->ip    = strdup(ip);
        list->prev  = !prev ? NULL : prev;
        list->next  = !next ? NULL : next;
    }
	return (list);
}

ConsoleInfo         *CI_get_next(const ConsoleInfo *list)
{
    return (list->next);
}

ConsoleInfo         *CI_set_next(ConsoleInfo *list, ConsoleInfo *list_next)
{
    list->next = list_next;
    return (list);
}

void                CI_print(const ConsoleInfo *list)
{
    printf("Nom: %s\tIP: %s\n", list->name, list->ip);
}

void                CIL_del(ConsoleInfoList **list)
{
    ConsoleInfo *tmp_list = (*list)->tail;

    while (tmp_list)
    {
        ConsoleInfo *tmp_del = tmp_list;
        tmp_list = tmp_list->prev;
        free(tmp_del);
    }
    memdel((void **)list);
}

ConsoleInfo         *CIL_get_tail(const ConsoleInfoList *list)
{
    return (list->tail);
}

ConsoleInfoList     *CIL_set_tail(ConsoleInfoList *list, ConsoleInfo *list_tail)
{
    list->tail = list_tail;
    return (list);
}

ConsoleInfo         *CIL_get_head(const ConsoleInfoList *list)
{
    return (list->head);
}

bool                CIL_is_empty(const ConsoleInfoList *list)
{
    return (list->count == 0);
}

ConsoleInfoList     *CIL_append(ConsoleInfoList *list, const char *name, const char *ip)
{
    if (CIL_is_empty(list))
    {
        list->head = list->tail = CI_new(name, ip, NULL, NULL);
    }
    else
    {
        ConsoleInfo *new = CI_new(name, ip, list->tail, NULL);
        CI_set_next(CIL_get_tail(list), new);
        CIL_set_tail(list, new);
    }
    list->count++;
    return (list);
}

ConsoleInfoList     *CIL_new(void)
{
	ConsoleInfoList	*list;

	if ((list = malloc(sizeof(ConsoleInfoList))))
    	{
        	list->count = 0;
        	list->head = NULL;
        	list->tail = NULL;
    	}
	return (list);
}
