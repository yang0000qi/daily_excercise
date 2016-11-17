/*************************************************************************
	> File Name: fork_1.c
	> Author: 
	> Mail: 
	> Created Time: 2016年11月16日 星期三 15时06分12秒
 ************************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int var_glb; /* A global variable*/

int main(void)
{
    pid_t childPID;
    int var_lcl = 0;

    childPID = fork();

    if(childPID >= 0) // fork was successful
    {
        if(childPID == 0) // child process
        {
            var_lcl++;
            var_glb++;
            printf("\n Child var_lcl address= %p,var_glb address = %p\n", &var_lcl, &var_glb);
            printf("\n Child Process :: var_lcl = [%d], var_glb[%d]\n", var_lcl, var_glb);
        }
        else //Parent process
        {
            var_lcl = 10;
            var_glb = 20;
            printf("\n Parent  var_lcl address= %p,var_glb address = %p\n", &var_lcl, &var_glb);
            printf("\n Parent process :: var_lcl = [%d], var_glb[%d]\n", var_lcl, var_glb);
        }
    }
    else // fork failed
    {
        printf("\n Fork failed, quitting!!!!!!\n");
        return 1;
    }

    return 0;
}
