#ifndef _DEV_INFO_H_
#define _DEV_INFO_H_ 1
#include "sm_http.h"
#define TOPIC_SIZE 40
#define HOST_BASE  "http://192.168.86.1:8080/smart-home" 

struct device_info
{
    char sub[TOPIC_SIZE];
    char pub[TOPIC_SIZE];
};


int device_login(char*appKey,char*mac,struct device_info*devInfo);

#endif
