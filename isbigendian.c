/*************************************************************************
	> File Name: isbigendian.c
	> Author: 
	> Mail: 
	> Created Time: 2016年10月27日 星期四 14时38分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
bool isbigendian()
{
    union NUM{
        int a;
        char b;
    }num;
    num.a = 0x12345678;
    printf("num.a = %x, num.b = %x\n", num.a, num.b);
    if(num.b == 0x12){
        printf("this is big endian\n");  
        return true;
    }
    printf("this is little endian\n");
    return false;
}

int main()
{
    isbigendian();
    int var; // Integer values
    char *ptr; // Pointer
    // Assign 'var' and output it in byte order and as a value
    var = 0x12345678;
    ptr = (char *) &var;
    printf("ptr[0] = %02X \n", ptr[0]); // Prints 78
    printf("ptr[1] = %02X \n", ptr[1]); // Prints 56
    printf("ptr[2] = %02X \n", ptr[2]); // Prints 34
    printf("ptr[3] = %02X \n", ptr[3]); // Prints 12
    printf("var = %08X \n", var); // Prints 12345678 
    
    return 0;
}

/*
    1)联合体是一个结构；

    2)它的所有成员相对于基地址的偏移量都为0；

    3)此结构空间要大到足够容纳最"宽"的成员；

    4)其对齐方式要适合其中所有的成员；
 */
