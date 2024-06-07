#ifndef MY_DEFS_H_
#define MY_DEFS_H_

extern const char* loglevel2str[];
extern const char* myDefsModule2str[];

#define LOG_OUT_SYSLOG 0
#define LOG_OUT_STDOUT 1
#define LOG_OUT_FILE   2

#define	MYLOG_CRIT	0	/* critical conditions */
#define	MYLOG_ERR		1	/* error conditions */
#define	MYLOG_WARNING	2	/* warning conditions */
#define	MYLOG_INFO	3	/* informational */
#define	MYLOG_DEBUG	4	/* debug-level messages */
#define	MYLOG_NONE	5	/* none */

#define MY_LOGMANAGER_MQ_NAME "/mylogqueue"

enum myDef_module_ids
{
	MYDEF_MODULE_IDS_LOG_MANAGER = 0
};

typedef struct
{
	char file[64];
	char func[64];
	int line_number;
	int error_type;
} s_error;

#endif