#include  <stdio.h>
#include  <sys/types.h>
#include  <stdlib.h>
#include  <string.h>
#include  <sys/wait.h>
#include  <unistd.h>

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

void  execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) 
     {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) 
     {          /* for the child process:         */
          if(*argv[0] != '!')
            {
              if (execvp(*argv, argv) < 0)       /* execute the command  */
              {   
                  printf("*** ERROR: exec failed\n");
                  exit(1);
                }       
            }
           else
           {   
               
            system("tac history.txt > filerev.txt");
            int s=atoi(argv[1]);
            //printf("%d",s);
            //printf("in #");
            char stmt[60];
            sprintf(stmt,"sed -n 1,%dp filerev.txt",s);
            system(stmt);
              }
     }
     else
     {                                  /* for the parent:      */
          while (wait(&status) != pid);
     }
}

 

int  main()
{
     char  line[1024];             /* the input line                 */
     char  *argv[64];              /* the command line argument      */
     char c;
    int i;
    FILE *fp;
    FILE *fp1;
    int ln;
    fp1=fopen("filerev.txt","w");
    fclose(fp1);
    fp=fopen("history.txt","w");   
    fclose(fp);
     while (1)
    {                   /* repeat until done ....         */
          fp=fopen("history.txt","a+");
          printf("Shell -> ");     /*   display a prompt             */
          gets(line);              /*   read in the command line     */
            //ln=len(line);
            //puts(line);
          c=line[0];
            i=0;
          while((c=line[i])!=0)
          {
              fprintf(fp,"%c",c);
              i=i+1;
          }
          fprintf(fp,"\n");
            fclose(fp);
         //fileinsert(argv);
          printf("\n");
          
          if(strcmp(line,"history")==0)
            {
                fp=fopen("history.txt","r+");
                fseek(fp,0,SEEK_SET);
                while(fgets(line,sizeof(line),fp)!=NULL)
                {
                    printf("%s",line);   
                }
                fclose(fp);       
            }
        else
        {
          parse(line, argv);       /*   parse the line               */
          if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
               exit(0);            /*   exit if it is                */
          execute(argv);           /* otherwise, execute the command */
        }
           
     }
    return 0;
}
