/*************************************************************************
	> File Name: attribute_weak_alias.c
	> Author: 
	> Mail: 
	> Created Time: Fri 16 Dec 2016 10:29:16 AM CST
 ************************************************************************/
//strong.c
#include<stdio.h>
void symbol_1()
{
    printf("%s.%s\n", __FILE__, __func__);
}

//weak.c
#include<stdio.h>
void symbol_1() __attribute__ ((weak, alias("symbol_2")));
void symbol_2()
{
    printf("%s.%s\n", __FILE__, __func__);
}

int main()
{
    symbol_1();
    return 0;

}


/****************************compile 1******************************/
# gcc weak.c strong.c -o out
# ./out
# strong.c.symbol_1
/****************************compile 2******************************/
# gcc weak.c -o out
# ./out
# weak.c.symbol_2


/****************************summary******************************/
总结weak属性:
1. 给函数加上weak属性时，即使函数没定义，函数被调用也可以编译成功。
2. 当有两个函数同名时，则使用强符号（也叫全局符号即没有加weak的函数）
   来代替弱符号（加weak的函数)
3. 当函数没有定义，但如果是“某个函数”的别名时，如果该函数被调用，
   就间接调用“某个函数”
