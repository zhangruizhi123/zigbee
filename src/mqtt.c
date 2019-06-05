#include "mqtt.h"


#define HOST "localhost"
#define PORT  1883
#define KEEP_ALIVE 60

static bool session = true;

static struct mosquitto *mosq = NULL;

static pthread_t  tid1;

static void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    if(message->payloadlen){
        printf("%s %s", message->topic, message->payload);
    }else{
        printf("%s (null)\n", message->topic);
    }
    fflush(stdout);
}

static void my_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    int i;
    if(!result){
        /* Subscribe to broker information topics on successful connect. */
        mosquitto_subscribe(mosq, NULL, "test:", 2);
    }else{
        fprintf(stderr, "Connect failed\n");
    }
}

static void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
    int i;
    printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
    for(i=1; i<qos_count; i++){
        printf(", %d", granted_qos[i]);
    }
    printf("\n");
}

static void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
    /* Pring all log messages regardless of level. */
    printf("%s\n", str);
}

static void mqtt_loop(void*p)
{
    mosquitto_loop_forever(mosq, -1, 1);
}
int mqtt_init()
{
     //libmosquitto 库初始化
    mosquitto_lib_init();
    //创建mosquitto客户端
    mosq = mosquitto_new(NULL,session,NULL);
    if(!mosq){
        printf("create client failed..\n");
        mosquitto_lib_cleanup();
        return 1;
    }
    //设置回调函数，需要时可使用
    //mosquitto_log_callback_set(mosq, my_log_callback);
    mosquitto_connect_callback_set(mosq, my_connect_callback);
    mosquitto_message_callback_set(mosq, my_message_callback);
    //mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
    //客户端连接服务器
    if(mosquitto_connect(mosq, HOST, PORT, KEEP_ALIVE)){
        fprintf(stderr, "Unable to connect.\n");
        return -1;
    }
    int err = pthread_create(&tid1, NULL, (void*)mqtt_loop, NULL);
    if(err!=0)
    {
         printf("can't create thread 1\n");
         return -2;
    }

    return 1;
}

int mqtt_destory()
{
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

int mqtt_publish(char*topic,char*data,int len)
{
    return mosquitto_publish(mosq,NULL,topic,len,data,0,0);
}

