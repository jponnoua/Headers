#ifndef MY_MSG_H_
#define MY_MSG_H_

#include "myDefs.h"

enum myMsg_cmd
{
	MYMSG_CMD_LOG = 0,
};

struct myMsg_contents_log
{
	char file[64];
	char func[64];
	int line_number;
	int error_type;
	char error_file_output[64];
	int error_output;
	char error_msg[256];
};

union myMsg_contents
{
	struct myMsg_contents_log contents_log;
	char contents_align[1024];
};

struct myMsg_header
{
	enum myDef_module_ids sender;
	enum myDef_module_ids receiver;
	enum myMsg_cmd cmd;
};

struct myMsg_msg
{
	struct myMsg_header header;
	union myMsg_contents contents;
	void *param;						// This field will be resent in the answer as well
};

struct myMsg_msg_queue
{
	struct myMsg_msg msg;
};

#endif