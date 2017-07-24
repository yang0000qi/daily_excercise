/*************************************************************************
	> File Name: time.c
	> Author: 
	> Mail: 
	> Created Time: Mon 24 Jul 2017 10:22:45 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>

int main()
{
   struct  timeval start;
   struct  timeval end;
   unsigned  long diff;
   gettimeofday(&start,NULL);
   
   while(1)
    {
        gettimeofday(&end,NULL);
        if(1 == (end.tv_sec-start.tv_sec)+ (end.tv_usec-start.tv_usec) / 1000000)
        {
            printf("the interval is 1s\n");
            gettimeofday(&start,NULL);
        
        }
    }
   return 0;


}
