#include <stdio.h>
#include "sm_uart.h"
#include "sm_crc.h"

void u_call(char*data,int len)
{
    if(len>=4)
    {
        char length=data[0];
        char cc=data[1];
        short cmd=(data[2]&0xff)|((data[3]&0xff)<<8);
        if(length+4==len&&sm_crc(data+4,length)==cc)
        {
            if(cmd==0)
            {
                printf("log:%s\n",data+4);
            }
        }
        else
        {
            printf("err data\n");
        }
        
    }
    else
    {
        printf("err data\n");
    }
    
}

int main()
{
    printf("hello world \n");
    if(sm_uart_init("/dev/ttyUSB0")==1){
        sm_uart_callback(u_call);
         char*str="gggggg";
        while(1)
        {
            sm_uart_write(str,strlen(str));
            sleep(2);
        }
    }else{
        printf("Open UART failed!\n");
    }
   
    return 0;
}

