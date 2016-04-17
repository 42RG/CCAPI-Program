#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "main.h"
# include "ccapi.h"

typedef struct ConsoleInfoList  ConsoleInfoList;
typedef struct ConsoleInfo      ConsoleInfo;

struct ConsoleInfoList {
  size_t count;
  ConsoleInfo *head;
  ConsoleInfo *tail;
};

struct ConsoleInfo {
  char *name;
  char *ip;
  ConsoleInfo *next;
  ConsoleInfo *prev;
};

ConsoleInfoList *CIL_new(void);
ConsoleInfoList *CIL_set_tail(ConsoleInfoList *list, ConsoleInfo *list_tail);
ConsoleInfoList *CIL_append(ConsoleInfoList *list, const char *name, const char *ip);
bool            CIL_is_empty(const ConsoleInfoList *list);
void            CIL_del(ConsoleInfoList **list);

ConsoleInfo     *CI_new(const char *name, const char *ip, ConsoleInfo *prev, ConsoleInfo *next);
ConsoleInfo     *CIL_get_tail(const ConsoleInfoList *list);
ConsoleInfo     *CIL_get_head(const ConsoleInfoList *list);
ConsoleInfo     *CI_get_next(const ConsoleInfo *list);
ConsoleInfo     *CI_set_next(ConsoleInfo *list, ConsoleInfo *list_next);
void            CI_print(const ConsoleInfo *list);

#endif
