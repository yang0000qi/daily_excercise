/*************************************************************************
	> File Name: strmZ
	> Mail: 
	> Created Time: 2016年10月10日 星期一 11时23分52秒
 ************************************************************************/

#include<stdio.h>

 struct struct_test {
     int a;
     char b;
     float d;
};

int main(int argc, char *argv[])
{
    struct struct_test test_1;
    printf("sizeof = %lu\n", sizeof(test_1));

    return 0;
}
