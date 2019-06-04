#include "sm_crc.h"

char sm_crc(char*data,char len)
{
    char result=0;
    char i=0;
    for(i=0;i<len;i++)
    {
        result+=data[i];
    }
    return result;
}