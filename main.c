#include <stdio.h>
#include "sm_uart.h"
#include "sm_crc.h"
#include "mqtt.h"

void u_call(char*data,int len)
{
    if(len>=4)
    {
        unsigned char length=data[0];
        char cc=data[1];
        unsigned short cmd=(data[2]&0xff)|((data[3]&0xff)<<8);
        if(length+4==len&&sm_crc(data+4,length)==cc)
        {
            if(cmd==0)
            {
                printf("log:%s\n",data+4);
            }
            else if(cmd==1)
            {
                unsigned char*datas=data+4;
                printf("mac:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",datas[0],datas[1],datas[2],
                datas[3],datas[4],datas[5],datas[6],datas[7]);
                unsigned short idadd=(short)(datas[8]&0xFF)|((datas[9]&0xFF)<<8);
                printf("short addr:%04x %u\n",idadd,idadd);
                
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
    /*
    if(sm_uart_init("/dev/ttyUSB0")==1){
        sm_uart_callback(u_call);
         char*str="gggggg";
        while(1)
        {
            //sm_uart_write(str,strlen(str));
            sleep(2);
        }
    }else{
        printf("Open UART failed!\n");
    }
    */
   if(mqtt_init()==1)
   {
       char*str="hello mqtt!\n";
       while(1)
       {
           mqtt_publish("test:",str,strlen(str));
           sleep(2);
       }
   }
   printf("program exit...\n");
    return 0;
}

