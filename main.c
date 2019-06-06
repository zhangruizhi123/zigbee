#include <stdio.h>
#include <signal.h>
#include "sm_uart.h"
#include "sm_crc.h"
#include "mqtt.h"
#include "cJSON.h"
unsigned short idadd=0;
//添加一行注释 11111
void u_call(unsigned char*data,int len)
{
    if(len>=6&&data[0]==0x55&&data[1]==0xAA)
    {
        unsigned char length=data[2];
        unsigned short cmd=(data[4]&0xff)|((data[5]&0xff)<<8);
        if(length+6==len)
        {
            if(cmd==0)
            {
                printf("log:%s\n",data+6);
            }
            else if(cmd==1)
            {
                unsigned char*datas=data+6;
                printf("mac:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",datas[0],datas[1],datas[2],
                datas[3],datas[4],datas[5],datas[6],datas[7]);
                idadd=(short)(datas[8]&0xFF)|((datas[9]&0xFF)<<8);
                printf("short addr:%04x %u\n",idadd,idadd);
                
            }
        }
        else
        {
            printf("err data1\n");
            int i=0;
            for(i=0;i<len;i++){
                printf("%02X ",data[i]);
            }
            printf("\n");
            
        }
        
    }
    else
    {
        printf("err data2\n");
    }
    
}
//程序退出时候会调动到这里
void service_destory(int signum)
{
    //当按下ctrl + C时候
    if(signum==2)
    {
        sm_uart_destory();
        mqtt_destory();
        printf("exit......\n");
        exit(0);
    }
    
}
int main()
{
    printf("hello world \n");
    signal(SIGINT, service_destory);
    if(sm_uart_init("/dev/ttyUSB0")==1){
       
       char bb[]={0xE1,0xC5,'h','e','l','l','o',0};
       char data[12]={0};
        sm_uart_callback(u_call);
         char*str="gggggg";
        while(1)
        {
            
            bb[0]=(idadd&0xFF);
            bb[1]=((idadd>>8)&0xFF);
            char crc=sm_crc(bb,8);
            
            data[0]=0x08;
            data[1]=crc;
            data[2]=02;
            data[3]=00;
            memcpy(data+4,bb,8);
            //sm_uart_write(str,strlen(str));
            sm_uart_write(data,12);
            
            sleep(1);
            //printf("send\n");
        }
    }else{
        printf("Open UART failed!\n");
    }

   /*
   if(mqtt_init()==1)
   {
       //char*str="hello mqtt!\n";
       cJSON*dev=cJSON_CreateObject();
       cJSON_AddStringToObject(dev,"version","1.0.0");
       cJSON_AddStringToObject(dev,"name","light");
       cJSON_AddStringToObject(dev,"mac","11:22:33:44:55:66");
       cJSON_AddNumberToObject(dev,"code",22);

       cJSON*switchs=cJSON_CreateObject();
       cJSON_AddBoolToObject(switchs,"switch",true);

       cJSON_AddItemToObject(dev,"payload",switchs);
       char*str=cJSON_Print(dev);
       printf("json:%s\n",str);
       while(1)
       {
           
           mqtt_publish(str,strlen(str));
           sleep(2);
       }

       cJSON_Delete(dev);
   }
   printf("program exit...\n");
   */
    return 0;
}

