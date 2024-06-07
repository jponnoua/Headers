

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <mqueue.h>

#include "myLog.h"

s_error my_log(int error_type, const char *file, const char* func, int line_number, const char *format, ...) {
    s_error ret;
	memset(&ret, 0, sizeof(ret));
	ret.line_number = line_number;
	ret.error_type = error_type;
	if(file != NULL)
	{
		strncpy(ret.file, file, sizeof(ret.file) - 1);
		ret.file[sizeof(ret.file) - 1] = '\0';
	}

	if(func != NULL)
	{
		strncpy(ret.func, func, sizeof(ret.func) - 1);
		ret.func[sizeof(ret.func) - 1] = '\0';
	}

	if (error_type <= g_log_display_level)
	{
		struct myMsg_msg_queue err_msg;
		memset(&err_msg, 0, sizeof(err_msg));
		err_msg.msg.contents.contents_log.error_type = error_type;
		if(file != NULL)
		{
			strncpy(err_msg.msg.contents.contents_log.file, file, sizeof(err_msg.msg.contents.contents_log.file) - 1);
			err_msg.msg.contents.contents_log.file[sizeof(err_msg.msg.contents.contents_log.file) - 1] = '\0';
		}

		if(func != NULL)
		{
			strncpy(err_msg.msg.contents.contents_log.func, func, sizeof(err_msg.msg.contents.contents_log.func) - 1);
			err_msg.msg.contents.contents_log.func[sizeof(err_msg.msg.contents.contents_log.func) - 1] = '\0';
		}

		err_msg.msg.contents.contents_log.line_number = line_number;
		strncpy(err_msg.msg.contents.contents_log.error_file_output, g_log_filename, sizeof(err_msg.msg.contents.contents_log.error_file_output));
		err_msg.msg.contents.contents_log.error_output = g_log_output;
		err_msg.msg.contents.contents_log.error_msg[0] = 0;
		va_list args;
		va_start(args, format);
		vsnprintf(err_msg.msg.contents.contents_log.error_msg, sizeof(err_msg.msg.contents.contents_log.error_msg), format, args);
		va_end(args);

        mqd_t mq_fd = mq_open(MY_LOGMANAGER_MQ_NAME, O_WRONLY);
        if(mq_fd != -1)
        {
            if (mq_send(mq_fd, (const char *)&err_msg, sizeof(err_msg), 0) == -1) {
                perror("mq_send");
            }
            
            mq_close(mq_fd);
        }
        else {
            perror("mq_open");
        }
	}

	return ret;
}