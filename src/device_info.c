#include "device_info.h"
#include <string.h>
#include "cJSON.h"

int device_login(char*appKey,char*mac,struct device_info*devInfo)
{
    char url[100];
    char result[300];
    int res=0;
    sprintf(url,"%s/appDevice/deviceLogin.do?productKey=%s&mac=%s",HOST_BASE,appKey,mac);
    //printf("%s\n",url);
    res=post(url,result);
    if(res==1&&devInfo!=NULL)
    {
        cJSON *json=cJSON_Parse(result);
        if(json!=NULL)
        {
            cJSON*code=cJSON_GetObjectItem(json,"code");
            if(code!=NULL&&code->valueint==0)
            {
                cJSON*data=cJSON_GetObjectItem(json,"data");
                if(data!=NULL)
                {
                    cJSON*pub=cJSON_GetObjectItem(data,"pub");
                    if(pub!=NULL)
                    {
                        strcpy(devInfo->pub,pub->valuestring);
                    }
                    cJSON*sub=cJSON_GetObjectItem(data,"sub");
                    if(sub!=NULL)
                    {
                        strcpy(devInfo->sub,sub->valuestring);
                    }
                    res=1;
                }
            }
        }

        cJSON_Delete(json);
    }

    return res;
}


