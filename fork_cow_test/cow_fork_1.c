/*************************************************************************
	> File Name: cow_fork_1.c
	> Author: 
	> Mail: 
	> Created Time: 2016年11月16日 星期三 14时44分55秒
 ************************************************************************/

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h> // for system()
#include <time.h>
#include <unistd.h> // for execl(), fork()
#include <wait.h>       // for wait()

#define D(x) __FILE__":%d:%s: " x, __LINE__, __func__
#define PAGESIZE    4096U
#define NPAGES      100000U

/* auxiliary routines to do time accounting */
t_start(struct timespec *t)
{
    clock_gettime(CLOCK_REALTIME, t);
} /* t_start */

t_print(struct timespec *t)
{
    struct timespec now;

    clock_gettime(CLOCK_REALTIME, &now); /* stop */
    now.tv_nsec -= t->tv_nsec;
    now.tv_sec -= t->tv_sec;
    if (now.tv_nsec < 0) {
        now.tv_nsec += 1000000000L;
        now.tv_sec--;
    } /* if */
    printf(D("elapsed: %d.%09d\n"),
           now.tv_sec, now.tv_nsec);
} /* t_print */

void testv(
        struct timespec *t,
        char *b,
        size_t bs,
        const char *fmt,
        va_list p)
{
    int i;
    static char c = 0;
    vprintf(fmt, p);
    t_start(t);
    for (i = 0; i < bs; i += PAGESIZE)
        b[i] = c;
    c++;
    t_print(t);
} /* testv */

void test(struct timespec *t,
        char *b,
        size_t bs,
        const char *fmt,
        ...)
{
    va_list p;
    va_start(p, fmt);
    testv(t, b, bs, fmt, p);
    va_end(p);
} /* test */

int main(int argc, char *argv[])
{   
    static char buffer[NPAGES*PAGESIZE];
    struct timespec ts;
    int i, res;

    test(&ts, buffer, sizeof buffer,
            D("The first test (expect high time--page allocating)\n"));
    test(&ts, buffer, sizeof buffer,
            D("The second test (expect low time)\n"));

    switch(res = fork()) { 
    case -1:
        fprintf(stderr,
                D("Cannot fork: %s(errno=%d)\n"),
                strerror(errno), errno);
        exit(EXIT_FAILURE);
    case 0: /* child */
        test(&ts, buffer, sizeof buffer,
                D("child[%d]: third test (expect high time--copy on write)\n"),
                getpid());
        test(&ts, buffer, sizeof buffer,
                D("child[%d]: fourth test (expect low time)\n"),
                getpid());
        exit(EXIT_SUCCESS);
    default: /* parent */
        printf(D("parent[%d]: waiting for child[%d] to finish\n"),
                getpid(), res);
        wait(NULL); /* expect so the calls don't get intermixed */
        test(&ts, buffer, sizeof buffer,
                D("parent[%d]: third test (expect medium time--swapping)\n"),
                getpid());
        test(&ts, buffer, sizeof buffer,
                D("parent[%d]: third test (expect low time)\n"),
                getpid());
        exit(EXIT_SUCCESS);
    } /* if */
    /*NOTREACHED*/
} /* main */
