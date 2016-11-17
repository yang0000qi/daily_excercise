/*************************************************************************
	> File Name: fork_2.c
	> Author: 
	> Mail: 
	> Created Time: 2016年11月16日 星期三 15时23分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>



int g_var[102400] = {0};
int main()
{
        int l_var[102400] = {0};
        fprintf(stderr,"g_var 's address is %lx\n",(unsigned long)g_var);

        fprintf(stderr,"l_var 's address is %lx\n",(unsigned long)l_var);

        memset(g_var,0,sizeof(g_var));
        memset(l_var,0,sizeof(l_var));

        sleep(15);

        int ret = fork();
        if(ret < 0 )
        {
                fprintf(stderr,"fork failed ,nothing to do now!\n");
                return -1;
        }

        if(ret == 0)
        {
                sleep(10);
                fprintf(stderr, "I begin to write now\n");

                fprintf(stderr,"address at %-10lx value(%-6d) will cause page falut\n",
                               (unsigned long)(g_var+2048),g_var[2048]);
                g_var[2048] = 4;

                sleep(6);
                fprintf(stderr,"address at %-10lx value(%-6d) will cause page fault\n",
                                (unsigned long)(g_var+10240),g_var[10240]);
                g_var[10240] = 8;


                sleep(4);
                fprintf(stderr,"address at %-10lx value(%-6d) will cause page falut\n",
                                (unsigned long)(l_var+2048),l_var[2048]);
                l_var[2048] = 8;

                sleep(4);
                fprintf(stderr,"address at %-10lx value(%-6d) will cause page falut\n",
                                 (unsigned long)(l_var+10240),l_var[10240]);
                l_var[10240] = 8;
              
        }
        if(ret >0)
        {
                waitpid(-1,NULL,0);
                fprintf(stderr,"child process exit, now check the value\n");
                fprintf(stderr,"g_var[%-6d] = %-4d\ng_var[%-6d] = %-4d\n",
                                2048,g_var[2048],10240,g_var[10240]);
                fprintf(stderr,"l_var[%-6d] = %-4d\nl_var[%-6d] = %-4d\n",
                                2048,l_var[2048],10240,l_var[10240]);

                return 0;
        }

}
