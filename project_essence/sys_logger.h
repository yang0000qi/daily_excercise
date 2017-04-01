#ifndef LW_CLOGGER_H_
#define LW_CLOGGER_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef  NATIVE_LOG_FILE_DEBUG

#define MODULE_MW "MW"

#define CLOG_MAX_MSG_LEN (1024)

#define LOG_LEVEL_CRITICAL      (0)
#define LOG_LEVEL_ERROR         (1)
#define LOG_LEVEL_WARNING       (2)
#define LOG_LEVEL_MESSAGE       (3)
#define LOG_LEVEL_VERBOSE       (4)

static char *module = MODULE_MW;
static int fd = -1;
static int log_level = LOG_LEVEL_VERBOSE;

const char * const CLOG_LEVEL_CHARS[] = {
		"CRIT",
		"ERR",
		"WARNING",
		"MESSAGE",
		"VERBOSE"
};

void log_write(const char *tag, int level, char *msg)
{
	time_t now = 0;
	int res = -1;
	char buf[64] = {0};
	char log[CLOG_MAX_MSG_LEN + 128] = {0};

    const char * path = "/data/save.log";
    fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
    if (-1 == fd) {
        printf("Unable to open %s: %s\n", path, strerror(errno));
        return 0;
    }

	if (level > log_level) {
		return;
	}

    char *date_format = (char *)"%Y-%m-%d %H:%M:%S";
    now = time(NULL);

	strftime(buf, sizeof(buf), date_format, localtime(&now));

	snprintf(log, sizeof(log), "%s %s %s/%s %s\n", buf, module, CLOG_LEVEL_CHARS[level], tag, msg);

	res = write(fd, log, strlen(log));
	if (-1 == res) {
	    printf("Unable to write to log file: %s\n", strerror(errno));
	}
    else {
        fsync(fd);
    }
    fclose(fd);

	return;
}

void my_log(const char *tag, int level, const char *fmt, ...)
{
	va_list ap;
	char msg[CLOG_MAX_MSG_LEN] = {0};

	va_start(ap, fmt);
	vsnprintf(msg, sizeof(msg), fmt, ap);
	log_write(tag, level, msg);

	va_end(ap);

	return;
}

#define LOGV(tag, fmt, ...) my_log(tag, LOG_LEVEL_VERBOSE, fmt, ##__VA_ARGS__)
#define LOGM(tag, fmt, ...) my_log(tag, LOG_LEVEL_MESSAGE, fmt, ##__VA_ARGS__)
#define LOGW(tag, fmt, ...) my_log(tag, LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#define LOGE(tag, fmt, ...) my_log(tag, LOG_LEVEL_ERROR,   fmt, ##__VA_ARGS__)
#define LOGC(tag, fmt, ...) my_log(tag, LOG_LEVEL_CRITICAL,fmt, ##__VA_ARGS__)

#else

#include <cutils/log.h>

#define LOGV(tag, fmt, ...) __android_log_print(ANDROID_LOG_VERBOSE, tag, fmt, ##__VA_ARGS__)
#define LOGM(tag, fmt, ...) __android_log_print(ANDROID_LOG_INFO,    tag, fmt, ##__VA_ARGS__)
#define LOGW(tag, fmt, ...) __android_log_print(ANDROID_LOG_WARN,    tag, fmt, ##__VA_ARGS__)
#define LOGE(tag, fmt, ...) __android_log_print(ANDROID_LOG_ERROR,   tag, fmt, ##__VA_ARGS__)
#define LOGC(tag, fmt, ...) __android_log_print(ANDROID_LOG_FATAL,   tag, fmt, ##__VA_ARGS__)

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // LW_CLOGGER_H_
