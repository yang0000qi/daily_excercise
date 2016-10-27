/*************************************************************************
	> File Name: asmlinkage.c
	> Author: 
	> Mail: 
	> Created Time: 2016年10月13日 星期四 15时54分11秒
 
    asmlinkage void __init start_kernel(void)

 ************************************************************************/

#include<stdio.h>

asmlinkage void __init start_kernel(void);

//arm platform

#ifdef __cplusplus
#define CPP_ASMLINKAGE extern "C"
#else
#define CPP_ASMLINKAGE
#endif

#ifndef asmlinkage
#define asmlinkage CPP_ASMLINKAGE
#endif

/*
 extern "C" 包含双重含义，从字面上即可得到：首先，被它修饰的目标是“extern”的；其次，被它修饰的目标是“C”的。
　　（1） 被extern "C"限定的函数或变量是extern类型的extern是C/C++语言中表明函数和全局变量作用范围（可见性）的关键字，该关键字告诉编译器，其声明的函数和变量可以在本模块或其它模块中使用。与extern对应的关键字是static，被它修饰的全局变量和函数只能在本模块中使用。因此，一个函数或变量只可能被本模块使用时，其不可能被extern “C”修饰。
　　（2） 被extern "C"修饰的变量和函数是按照C语言方式编译和连接的。
*/

//x86 platform
#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))
#define FASTCALL(x) x __attribute__((regparm(3)))
#define fastcall __attribute__((regparm(3)))

/*
　函数定义前加宏asmlinkage，表示这些函数通过堆栈而不是通过寄存器传递参数。gcc编译器在汇编过程中调用c语言函数时传递参数有两种方法：一种是通过堆栈，另一种是通过寄存器。缺省时采用寄存器，假如你要在你的汇编过程中调用c语言函数，并且想通过堆栈传递参数，你定义的c函数时要在函数前加上宏asmlinkage。
　　其中 __attribute__是关键字，是gcc的c语言扩展。__attribute__机制是GNU C的一大特色，它可以设置函数属性、变量属性和类型属性等。可以通过它们向编译器提供更多数据，帮助编译器执行优化等。
　　__attribute__((regparm(0)))：告诉gcc编译器该函数不需要通过任何寄存器来传递参数，参数只是通过堆栈来传递。
　　__attribute__((regparm(3)))：告诉gcc编译器这个函数可以通过寄存器传递多达3个的参数，这3个寄存器依次为EAX、EDX 和 ECX。更多的参数才通过堆栈传递。这样可以减少一些入栈出栈操作，因此调用比较快。
　　asmlinkage大都用在系统调用中。有一些情况下是需要明确的告诉编译器，我们是使用stack来传递参数的，比如x86中的系统调用，是先将参数压入stack以后调用sys_*函数的，所以所有的sys_*函数都有asmlinkage来告诉编译器不要使用寄存器来编译。
*/
