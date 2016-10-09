/*************************************************************************
	> File Name: data_type_c_language.c
	> Author: 
	> Mail: 
	> Created Time: 2016年10月09日 星期日 19时44分49秒

C Data Types
In general, you'd commonly use:

int 
	for most variables and "countable" things (for loop counts, variables, events)
char 
	for characters and strings
float 
	for general measurable things (seconds, distance, temperature)
uint32_t 
	for bit manipulations, especially on 32-bit registers


Integer Data Types
C Type		    	stdint.h type	Bits	Sign		Range
char			    uint8_t		    8	    Unsigned	0 .. 255
signed char		    int8_t		    8	    Signed		-128 .. 127
unsigned short		uint16_t	    16	    Unsigned	0 .. 65,535
short			    int16_t		    16	    Signed		-32,768 .. 32,767
unsigned int		uint32_t	    32	    Unsigned	0 .. 4,294,967,295
int			        int32_t		    32	    Signed		-2,147,483,648 .. 2,147,483,647
unsigned long long	uint64_t	    64	    Unsigned	0 .. 18,446,744,073,709,551,615
long long		    int64_t		    64	    Signed		-9,223,372,036,854,775,808 .. 9,223,372,036,854,775,807


Floating Point Data Types
C type			IEE754 Name		    Bits	Range
float			Single Precision	32		-3.4E38 .. 3.4E38
double			Double Precision	64		-1.7E308 .. 1.7E308


Pointers
The ARMv7-M architecture used in mbed microcontrollers is a 32-bit architecture, so standard C pointers are 32-bits.

Pointers to void
A pointer of type void * represents the address of an object, but not its type. For example, a memory allocation function void *malloc( size_t size ); returns a pointer to void which can be casted to any data type.

Notes:
1.Whilst most types are signed by default (short, int, long long), char is unsigned by default.
2.Because the natural data-size for an ARM processor is 32-bits, it is much more preferable to use int as a variable than short; the processor may actually have to use more instructions to do a calculation on a short than an int!


************************************************************************/


#include<stdio.h>
#include <limits.h>

int main()
{

   printf("Storage size for int : %d \n", sizeof(int));
   printf("Storage size for short : %d \n", sizeof(short));
   printf("Storage size for long : %d \n", sizeof(long));
   printf("Storage size for long long : %d \n", sizeof(long long));
   printf("Storage size for float : %d \n", sizeof(float));
   printf("Storage size for double : %d \n", sizeof(double));
   printf("Storage size for long double : %d \n", sizeof(long double));

   return 0;
}
