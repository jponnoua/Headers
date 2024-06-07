#ifndef MY_LOG_H_
#define MY_LOG_H_

#include "myMsg.h"

extern int g_log_display_level;
extern int g_log_output;
extern char g_log_filename[64];

s_error my_log(int error_type, const char *file, const char* func, int line_number, const char *format, ...);

#endif