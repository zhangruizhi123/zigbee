#ifndef _SM_UART_H_
#define _SM_UART_H_

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>
#include<termios.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#include<errno.h>
#include <pthread.h>

typedef void (*uart_callback)(char*data,int len);

//初始化函数
int sm_uart_init(char*name);
//销毁函数
int sm_uart_destory();
//写函数
int sm_uart_write(char*data,int len);
//会掉函数
int sm_uart_callback(uart_callback call);

#endif
