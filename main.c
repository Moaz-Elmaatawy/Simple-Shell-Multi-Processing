#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include<string.h>
#include<signal.h>
#include<time.h>


#define max_args 250 //the maximum number of arguments for a single command
#define max_line 250 //the maximum command lenght

FILE* log; //the logging file

// this function reads a single line and split and create the arguments array
int read_line(char line[], char *arg[]){
    printf("Moaz:~$ ");
    fgets(line,max_args,stdin); // read a line
    // removing the end line from the end of the command
    int i=0;
    while(line[i]!='\n')++i;
    line[i]='\0';
    i=0;
    // split the command into an array where each index is a word
    char * token = strtok(line," ");
    arg[i]=token;
    while( token != NULL ) {
        ++i;
        token = strtok(NULL," ");
        arg[i]=token;
    }
    return i;
}


// Writting to the log file
void log_to_file(){
    //open the log file and append to it
    log=fopen("log.txt","a");
    //get the current time
    time_t curr_time;
    time(&curr_time);
    //write that a child has been terminated and the termination time
    fprintf(log,"%s Child Terminated\n",ctime(&curr_time));
    // close the file
    fclose(log);
//    printf("logged\n");
}

int main()
{
    //create a new file for logging
    log=fopen("log.txt","w");
    fclose(log);

    //create a signal for child termination and execute the log_to_file method
    signal(SIGCHLD,log_to_file);

    //loop until exit command
    while(1){
        // get the command ready
        char line[max_line];
        char *args[max_args];
        int n_args=read_line(line,args);

        //empty command
        if(n_args==0){
            continue;
        }

        //check whether it is an exite command or not
        if(!strcmp(args[0],"exit")){
            printf("terminated..");
            exit(0);
        }

        //check whether it is a background process
        int background_process=0;
        if(!strcmp(args[n_args-1],"&")){
            args[n_args-1]="\0";
            background_process=1;
            //printf("background process\n");
        }

        //create a child process
        int child_pid=fork();

        if(child_pid <0 ){
            // an error has been occured while forking
            printf("Error Forking chid\n");
            exit(1);
        }
        // if it is the child process
        if(child_pid==0){
            //check if it is a correct command or not
            if(execvp(args[0],args)<0 ){
                printf("Wrong Command !!\n");
                exit(1);
            }
        }
        // if it is a normal process
        else if(!background_process){
            // wait untill the child process terminate
            waitpid(child_pid,NULL,0);
        }

    }

    return 0;
}
