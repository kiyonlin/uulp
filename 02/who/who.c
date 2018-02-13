#include <stdio.h>
#include <utmpx.h>
#include <time.h>

#define SHOWHOST

// 时间戳转换为人类可读时间
// %12.12s 表示12宽，限制12个字符
void show_time(long timeval)
{
    char *cp;
    cp = ctime(&timeval);

    printf("%12.12s", cp + 4);
}

void show_info(struct utmpx *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS) return;

    printf("%-8.8s", utbufp->ut_user);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    show_time(utbufp->ut_tv.tv_sec);
    
#ifdef SHOWHOST
    if (utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}

int main()
{
    struct utmpx *current_record;

    current_record = getutxent();
    while (current_record)
    {
        show_info(current_record);
        current_record = getutxent();
    }
    endutxent();
    return 0;
}