#include "sm_http.h"
#include "string.h"

static char buff[SM_HTTP_SIZE]={0};
static int ft_curl_post_parse(void* buffer, size_t size, size_t nmemb, char * useless)  
{
    strncpy(buff,buffer,nmemb);
    return nmemb;
}

int post(char*url,char*result)
{
    
    CURLcode res;
    int code =0;
    CURL *curl;
    char*data="";
    int iRet = 0;
    memset(buff,0,SM_HTTP_SIZE);
    curl = curl_easy_init(); 
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data); //post参数  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ft_curl_post_parse); //对返回的数据进行操作的函数地址  
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL); //这是write_data的第四个参数值  
    curl_easy_setopt(curl, CURLOPT_POST, 1); //设置问非0表示本次操作为post
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    res = curl_easy_perform(curl);
    if(res==CURLE_OK)
    {
        strcpy(result,buff);
        code=1;
    }
    else
    {
       code=0;
    }
    curl_easy_cleanup(curl);
    return code;
}