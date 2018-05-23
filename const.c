/*************************************************************************
	> File Name: const.c
	> Author: 
	> Mail: 
	> Created Time: Fri 20 Apr 2018 02:16:54 PM CST
 ************************************************************************/

#include<stdio.h>


int main()
{
    const int val  = 8;
    //const = 9; //error
    printf("const int val = %d\n", val);

    int * const p = NULL ;

    *p = 9;

    printf("const int *p = %d\n", *p);
    

    return 0;

}
