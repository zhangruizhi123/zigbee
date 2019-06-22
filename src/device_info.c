#include "device_info.h"


int device_login(char*appKey,char*mac,struct device_info*devInfo)
{
    char url[100];
    char result[300];
    sprintf(url,"%s/appDevice/deviceLogin.do?productKey=%s&mac=%s",HOST_BASE,appKey,mac);
    printf("%s\n",url);
    post(url,result);
    printf("result:%s\n",result);
    return 0;
}


