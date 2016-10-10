/*************************************************************************
	> File Name: simple_strtoul.c
	> Author: seven
	> Mail:  
	> Created Time: 2016年10月10日 星期一 14时20分00秒
    >Function:
        Judge which is the type for data
        understand the function "simple_strtoul()" in u-boot code

unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base)


1.第一个参数中的const。一般在函数的形参中，如果我们只是希望调用者使用该参数，而不会去改变该参数内容（一般是指针指向的内容），则可以声明为const

2.第二个参数。C语言中函数只能有一个返回值，但是有时候我们希望从函数中得到不止一个返回内容怎么办呢？只能通过参数了。一般的参数是用来向函数输入信息的，但是指针型参数可以间接用来从函数
输出信息。使用时用户只需传入一个相应的指针，函数中会把需要输出的信息地址传给这个指针，这样在函数调用完成后，用户即可到endp指针处去取函数传出的值了。这就是用参数实现返回值的方式。但是
要注意，在函数中千万不可把局部变量的地址传给输出型指针，因为局部变量存在栈里，函数调用结束后即释放了，传出的指针指向的内容是栈上已经被释放的部分，因此是无效的

3.第三个参数base。要注意这个base的机制，本函数中是按照这样的理念来设计的。即如果str中有0x开头且接下来是数字则忽略用户调用时输入的base，强制为16进制。如果str不是上面情况然后才看用户
输入的base。用户输入非0则使用用户指定的base，若用户输入0则自动判断是8进制还是10进制。需要强调的是：使用习惯决定理念，理念决定代码逻辑

4.注意 if(endp)这里，在输出型参数使用中，函数内首先判断endp是否为NULL，并以此来决定是否输出这个机制来自于一个理念：这个输出参数有可能是用户关注的，也有可能是用户不在意的。这样处理可以
 给用户自由，即用户如果在意就传一个有效指针过来接收；如果不在意调用时直接给个NULL就行。提供服务但不强迫，这样很好。在OS的API中很多时候都有类似的技巧，请注意体会

************************************************************************/

#include<stdio.h>

/**
 * Decode the integer value of an environment variable and return it.
 *
 * @param name		Name of environemnt variable
 * @param base		Number base to use (normally 10, or 16 for hex)
 * @param default_val	Default value to return if the variable is not
 *			found
 * @return the decoded value, or default_val if not found
 */

/*

unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base)
{
    unsigned long result = 0,value;
    // 对于base，首先如果*cp以0x开头且下来是数字，则一定为16进制。
    // 然后如果用户指定了一个非0的进制，则遵循用户输入的进制。如果用户输入了0进制，则根据是否0开头来
    // 确定是8进制还是10进制
    if (*cp == '0') {
        cp++;
        if ((*cp == 'x') && isxdigit(cp[1])) {
            base = 16;            // 如果cp是0x开头的，下面一个又是数字，那么base一定为16.此时即使
            cp++;                // 用户输入了一个base，也忽略这个base而强制其为16
        }
        if (!base) {
            base = 8;            // 如果用户输入base为0，cp是0开头，接下来不是x，
        }                        // 那么强制为8进制
    }
    if (!base) {
        base = 10;                // 如果用户输入base为0，cp是非0开头，则使用10进制。
    }
    // while循环里value<base是精髓所在。这个解析停止的条件不能是null，而应该是str中第一个不是
    // 数字的字母。这个字母的范围取决于base，譬如如果是16进制那么f也算是数字。而如果是8进制那么
    // 9都不算是数字了。因此解析结束的范围只能和base比较来限定。
    while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp-'0' : (islower(*cp)
        ? toupper(*cp) : *cp)-'A'+10) < base) {
        result = result*base + value;
        cp++;
    }
    if (endp)        // 此处if判断的作用是：用户在使用这个函数时，如果不关心endp则可以直接使用
        *endp = (char *)cp;        // null,而不必担心程序运行会出错。这种处理技巧很实用，用户可以
        return result;        // 自行决定是否使用这个函数提供的参数式返回值。
}


*/

#define _U	0x01	/* upper */
#define _L	0x02	/* lower */
#define _D	0x04	/* digit */
#define _C	0x08	/* cntrl */
#define _P	0x10	/* punct */
#define _S	0x20	/* white space (space/lf/tab) */
#define _X	0x40	/* hex digit */
#define _SP	0x80	/* hard space (0x20) */


const unsigned char _ctype[] = {
_C,_C,_C,_C,_C,_C,_C,_C,			        /* 0-7 */
_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,		/* 8-15 */
_C,_C,_C,_C,_C,_C,_C,_C,			        /* 16-23 */
_C,_C,_C,_C,_C,_C,_C,_C,			        /* 24-31 */
_S|_SP,_P,_P,_P,_P,_P,_P,_P,			    /* 32-39 */
_P,_P,_P,_P,_P,_P,_P,_P,			        /* 40-47 */
_D,_D,_D,_D,_D,_D,_D,_D,			        /* 48-55 */
_D,_D,_P,_P,_P,_P,_P,_P,			        /* 56-63 */
_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,	/* 64-71 */
_U,_U,_U,_U,_U,_U,_U,_U,			        /* 72-79 */
_U,_U,_U,_U,_U,_U,_U,_U,			        /* 80-87 */
_U,_U,_U,_P,_P,_P,_P,_P,			        /* 88-95 */
_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,	/* 96-103 */
_L,_L,_L,_L,_L,_L,_L,_L,			        /* 104-111 */
_L,_L,_L,_L,_L,_L,_L,_L,			        /* 112-119 */
_L,_L,_L,_P,_P,_P,_P,_C,			        /* 120-127 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		    /* 128-143 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		    /* 144-159 */
_S|_SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,   /* 160-175 */
_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,       /* 176-191 */
_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,       /* 192-207 */
_U,_U,_U,_U,_U,_U,_U,_P,_U,_U,_U,_U,_U,_U,_U,_L,       /* 208-223 */
_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,       /* 224-239 */
_L,_L,_L,_L,_L,_L,_L,_P,_L,_L,_L,_L,_L,_L,_L,_L};      /* 240-255 */



#define __ismask(x) (_ctype[(int)(unsigned char)(x)])

#define isalnum(c)	((__ismask(c)&(_U|_L|_D)) != 0)         //检查c是否是字母或数字
#define isalpha(c)	((__ismask(c)&(_U|_L)) != 0)            //检查c是否是字母
#define iscntrl(c)	((__ismask(c)&(_C)) != 0)               //检查c是否控制字符(其ASCII码在0和0x1F之间,数值为 0-31)
#define isdigit(c)	((__ismask(c)&(_D)) != 0)               //检测是否是数字
#define isgraph(c)	((__ismask(c)&(_P|_U|_L|_D)) != 0)      //检查c是否可显示字符(其ASCII码在ox21到ox7E之间),不包括空格
#define islower(c)	((__ismask(c)&(_L)) != 0)               //检查小写字母
#define isprint(c)	((__ismask(c)&(_P|_U|_L|_D|_SP)) != 0)  //检查c是否是可打印字符(包括空格),其ASCII码在ox20到ox7E之间 
#define ispunct(c)	((__ismask(c)&(_P)) != 0)               //检查c是否是标点字符(不包括空格),即除字母,数字和空格以外的所有可打印字符 
#define isspace(c)	((__ismask(c)&(_S)) != 0)               //检查c是否是空格符和跳格符(控制字符)或换行符
#define isupper(c)	((__ismask(c)&(_U)) != 0)               //检查大写字母
#define isxdigit(c)	((__ismask(c)&(_D|_X)) != 0)            //检查c是否是一个16进制数学字符(即0-9,或A-F,或a-f)

#define isblank(c)	(c == ' ' || c == '\t')

#define isascii(c) (((unsigned char)(c))<=0x7f)
#define toascii(c) (((unsigned char)(c))&0x7f)

static inline unsigned char __tolower(unsigned char c)
{
	if (isupper(c))
		c -= 'A'-'a';
	return c;
}

static inline unsigned char __toupper(unsigned char c)
{
	if (islower(c))
		c -= 'a'-'A';
	return c;
}

#define tolower(c) __tolower(c)
#define toupper(c) __toupper(c)


unsigned long simple_strtoul(const char *cp, char **endp,
				unsigned int base)
{
	unsigned long result = 0;
	unsigned long value;

	if (*cp == '0') {
		cp++;
		if ((*cp == 'x') && isxdigit(cp[1])) {
			base = 16;
			cp++;
		}

		if (!base)
			base = 8;
	}

	if (!base)
		base = 10;

	while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp-'0' : (islower(*cp)
	    ? toupper(*cp) : *cp)-'A'+10) < base) {
		result = result*base + value;
		printf("base = %d\n", base);
        cp++;
	}

	if (endp)
		*endp = (char *)cp;

	return result;
}

int main()
{
    char *str = "0xA";
    printf("%s = %lu\n", str, simple_strtoul(str, NULL, 16));
    printf("\n");

    char ch = 'A';
    printf("the char %c :\n", ch);
    printf("isupper = %d\n", isupper(ch));
    printf("islower = %d\n", islower(ch));
    printf("isxdigit = %d\n", isxdigit(ch));
    printf("isdigit = %d\n", isdigit(ch));
    printf("isalnum = %d\n", isalnum(ch));
    printf("isascii = %d\n", isascii(ch));
    printf("toascii = %d\n", toascii(ch));
    printf("tolower = %c, the ASCII is %d\n", tolower(ch), tolower(ch));
    printf("toupper = %c, the ASCII is %d\n", toupper(ch), toupper(ch));
    return 0;

}

