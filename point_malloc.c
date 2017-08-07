/*************************************************************************
	> File Name: host_link.c
	> Author: 
	> Mail: 
	> Created Time: Sun 06 Aug 2017 09:14:46 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned int  uint32_t;
typedef unsigned char uint8_t;

struct host_link_read_data {
        unsigned char tag;
        int data_size;
        unsigned char *data;
};

typedef struct
{
      uint8_t Data[8];   
}CanTxMsgTypeDef;

typedef struct
{
    CanTxMsgTypeDef* pRxMsg;     
}CAN_HandleTypeDef;

CAN_HandleTypeDef can1;

void test(struct host_link_read_data *read_data)
{
   can1.pRxMsg = malloc(read_data->data_size); //should be malloc. If not, will be error
   memcpy(can1.pRxMsg->Data, read_data->data, read_data->data_size);
    
    printf("pRxMsg = { ");
    for(int i = 0; i < read_data->data_size; i++ )
        printf("%d ", can1.pRxMsg->Data[i]);
    printf("}\n");

    free(can1.pRxMsg);

}

struct host_link_read_data *host_link_read()
{
        char str[] = {30,40};
        static struct host_link_read_data read_data;
        read_data.tag = 10;
        read_data.data_size = sizeof(str);
        read_data.data = str;
        return &read_data;
}


int main()
{
    struct host_link_read_data *read = host_link_read();
    test(read);
    
    return 0;

}
