/*************************************************************************
	> File Name: cow_fork.c
	> Author: 
	> Mail: 
	> Created Time: 2016年11月16日 星期三 14时39分20秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h> // for system()
#include <unistd.h> // for execl(), fork()
#include <wait.h>       // for wait()
int main(int argc, char *argv[]) {   
    int pid, i;               /* fork another process */ 
    char *ptr = "world";
    char *b = ptr;
    char *c = NULL;
    printf("%s , %p, %p\n " , b, b, &b); 
    int k = 1;
    printf("start...\n");
    for(k;k<1000;k++)
    {
    pid = fork();

    if(pid < 0) {             /* error occurred */    
            fprintf(stderr,"Fork Failed");    
            exit(-1);   
    }   
    else if (pid== 0) {           /* child process */
            //printf("it should be same with parent : %s , %p, %p\n " , b, b, &b); 
            //b = k + "0";
            b = "hello";
            c=b;
            // printf("it might be differ : %s , %p, %p\n " , b, b, &b); 
    }   
    else {    
            wait(NULL);    
            //printf("parent : %s , %p, %p\n " , b, b, &b); 
            exit(0);   
    }   

    }    
    printf("c : %s , %p, %p\n " , c, c, &c); 
    printf("end...\n");
}
