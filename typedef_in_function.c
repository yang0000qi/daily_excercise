/*************************************************************************
	> File Name: typedef_in_function.c
	> Author:yangqi 
	> Mail: yang0000qi@126.com
	> Created Time: 2016年10月09日 星期日 17时00分58秒
    > The code is to understand "typedef" in function, it has been met in u-boot/arch/arm/lib/board.c
    > typedef int (init_fnc_t) (void)
 ************************************************************************/

#include<stdio.h>

int for_printf(void)
{
    return 10;
}

int main(int argc, char *argv[])
{
    typedef int (int_func_t) (void);
    int_func_t *funcp = for_printf;
    printf("%d\n", funcp());//use funcp() is correct, funcp will be error
}

