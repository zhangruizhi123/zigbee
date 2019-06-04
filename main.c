#include <stdio.h>
#include "sm_uart.h"

void u_call(char*data,int len)
{
    printf("data:%s %d\n",data,len);
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

