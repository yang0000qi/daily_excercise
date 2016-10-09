/*************************************************************************
	> File Name: typedef_in_function.c
	> Author:yangqi 
	> Mail: yang0000qi@126.com
	> Created Time: 2016年10月09日 星期日 17时00分58秒
    > The code is to understand "typedef" in function, it has been met in u-boot/arch/arm/lib/board.c
    > typedef int (init_fnc_t) (void)

    >函数别名
        typedef int (init_fnc_t) (void)
        相当于为参数是void类型，返回值是int类型的函数类型取了个别名
        表示对一个int (void)函数类型取别名init_fnc_t,可以用这个别名init_fnc_t进行创建这个类型的函数对象
    >通常用法：
        init_fnc_t *myfunction就是一个函数的指针，如果某个函数的类型是init_fnc_t类型，那么函数指针myfunction就可以指向这个函数

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

