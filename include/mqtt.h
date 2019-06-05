#ifndef _MQTT_H_
#define _MQTT_H_
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <string.h>
#include <pthread.h>
//初始化
int mqtt_init();
//发生数据
int mqtt_publish(char*data,int len);
//销毁函数
int mqtt_destory();

#endif
