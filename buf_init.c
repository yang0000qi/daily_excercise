/*************************************************************************
	> File Name: buf_init.c
	> Author: 
	> Mail: 
	> Created Time: Sat 14 Oct 2017 04:00:56 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

struct STREAM_BUF {
    unsigned buf_size_shift;
    unsigned data_start;
    unsigned data_end;
    unsigned char *buf;
};


static int buf_init(struct STREAM_BUF *stream_buf, void *buf, unsigned size)
{
    
}

int main(int argc, char *argv[])
{

    printf("sizeof(unsigned) = %d\n", sizeof(unsigned));

    return 0;
    
}
