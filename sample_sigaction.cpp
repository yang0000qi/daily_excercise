/*************************************************************************
	> File Name: sample_sigaction.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年11月02日 星期一 17时29分59秒
 ************************************************************************/

#include<iostream>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <sys/syscall.h>

using namespace std;

#define SIG_MONITOR_SIZE    8
#define MAX_TRACES          100
#define STACK_BODY_SIZE     (64*1024)

#define TRACE_DUMP_DIR "/mnt"

#define SEVEN_PRINT(fmt, args...) do { \
    printf(fmt, ##args); \
} while (0)


#define gettid() syscall(SYS_gettid)

int dump(char *fileName)
{
    int j, nptrs;
    int rc = 0;
    void *buffer[MAX_TRACES];
    char **strings;

    nptrs = backtrace(buffer, MAX_TRACES);

    SEVEN_PRINT("backtrace() returned %d addresses \n", nptrs);

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++) {
        SEVEN_PRINT("[%02d] %s \n", j, strings[j]);
        if (fileName) {
            char buff[256] = {0x00};
            snprintf(buff, sizeof(buff), "echo \"%s\" >> %s", strings[j], fileName);
            rc = system((const char*) buff);
        }
    }

    free(strings);

    return 0;
}


void signal_handler(int signo)
{
    /// Use static flag to avoid being called repeatedly.
    int rc = 0;
    static volatile bool isHandling[SIGALRM + 1] = {false};
    if (true == isHandling[signo]) {
        return;
    }
    SEVEN_PRINT("=========>>>catch signal %d <<< from tid:%d====== \n", signo, (int)gettid());

    isHandling[signo] = true;

    if (SIGINT == signo) {
        exit(0);
    }

    char fileName[128] = {0x00};
    char buff[256] = {0x00};

    /// Dump trace and r-xp maps
    snprintf(fileName, sizeof(fileName), "%s/trace_%d[%d].txt", TRACE_DUMP_DIR, getpid(), signo);

    snprintf(buff, sizeof(buff), "cat /proc/%d/maps | grep '/usr' | grep 'r-xp' | tee %s", getpid(), fileName);
    SEVEN_PRINT("Run cmd: %s \n", buff);
    rc = system((const char*) buff);

    SEVEN_PRINT("Dump stack start... \n");
    dump(fileName);
    SEVEN_PRINT("Dump stack end... \n");

    /// Dump fd
    snprintf(fileName, sizeof(fileName), "%s/fd_%d[%d].txt", TRACE_DUMP_DIR, getpid(), signo);
    snprintf(buff, sizeof(buff), "ls -l /proc/%d/fd > %s", getpid(), fileName);
    SEVEN_PRINT("Run cmd: %s \n", buff);
    rc = system((const char*) buff);

    /// Dump whole maps
    snprintf(fileName, sizeof(fileName), "%s/maps_%d[%d].txt", TRACE_DUMP_DIR, getpid(), signo);
    snprintf(buff, sizeof(buff), "cat /proc/%d/maps > %s", getpid(), fileName);
    SEVEN_PRINT("Run cmd: %s \n", buff);
    rc = system((const char*) buff);

    /// Dump meminfo
    snprintf(fileName, sizeof(fileName), "%s/meminfo_%d[%d].txt", TRACE_DUMP_DIR, getpid(), signo);
    snprintf(buff, sizeof(buff), "cat /proc/meminfo > %s", fileName);
    SEVEN_PRINT("Run cmd: %s \n", buff);
    rc = system((const char*) buff);

    /// Dump ps
    snprintf(fileName, sizeof(fileName), "%s/ps_%d[%d].txt", TRACE_DUMP_DIR, getpid(), signo);
    snprintf(buff, sizeof(buff), "ps -T > %s", fileName);
    SEVEN_PRINT("Run cmd: %s \n", buff);
    rc = system((const char*) buff);

    /// Dump top
    snprintf(fileName, sizeof(fileName), "%s/top_%d[%d].txt", TRACE_DUMP_DIR, getpid(), signo);
    snprintf(buff, sizeof(buff), "top -b -n 1 > %s", fileName);
    SEVEN_PRINT("Run cmd: %s \n", buff);
    rc = system((const char*) buff);

    exit(0);
}



void registerSigMonitor()
{
    int sigArray[SIG_MONITOR_SIZE] =
    {
        SIGINT,     // 2
        SIGILL,     // 4
        SIGABRT,    // 6
        SIGBUS,     // 7
        SIGFPE,     // 8
        SIGSEGV,    // 11
        SIGPIPE,    // 13
        SIGALRM,    // 14
    };

    /// Sig stack configure
    static stack_t    sigseg_stack;
    static char       stack_body[STACK_BODY_SIZE];
    sigseg_stack.ss_sp      = stack_body;
    sigseg_stack.ss_flags = SS_ONSTACK;
    sigseg_stack.ss_size  = sizeof(stack_body);
    assert(!sigaltstack(&sigseg_stack, NULL));

    /// Regiser handler of sigaction
    static struct  sigaction sig;
    sig.sa_handler   = signal_handler;
    sig.sa_flags     = SA_ONSTACK;

    /// Add blocking signals
    /// TODO: still can not block signal SIGSEGV ?
    sigemptyset(&sig.sa_mask);
    for (int i = 0; i < SIG_MONITOR_SIZE; i++) {
        sigaddset(&sig.sa_mask, sigArray[i]);
    }

    /// Register handler for signals
    for (int i = 0; i < SIG_MONITOR_SIZE; i++) {
        if(0 != sigaction(sigArray[i], &sig, NULL)) {
            SEVEN_PRINT("monitor signal %d failed \n", sigArray[i]);
        }
    }

    SEVEN_PRINT("Monitoring... \n");

    return;
}


int main()
{
    registerSigMonitor();

    SEVEN_PRINT("Running... \n");

    int *ptr = NULL;
    *ptr = 1;

    return 0;
}
