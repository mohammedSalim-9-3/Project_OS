#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdbool.h>
#include "myshell.h"
int main(int argc , char* argv []) {


  pid_t my_fork;
  char* command[10];
  char* commandString;
  size_t len = 0;
  FILE * fd = fopen(argv[1], "r");;
  int  output;
  int  inp;
  while(1) {
       deletCommandUser(command);
   
     if (argc == 2 && !feof(fd)) {
          if (fd == NULL) {
             break;
          } 
       // get commands String From File          
      getline(&commandString, &len, fd);

     // If the file finished fetching  string Commands and remain 2 argc....
     } else if (argc == 2) {
        break;
     }
     // If the user does not want to execute a specific file
    else {
          printCurrentDirectory();
          commandString = getCommandUser(commandString);
     }
    commandString = deleteEnterCharacter(commandString);
     splitString(command, commandString); 

      // stdin   >> 0
      // stdout  >> 1

       int lengthCommandSystem = sizeof(command)/sizeof(command[0]);
       int defInp = dup(STDIN_FILENO);
       int defOut = dup(STDOUT_FILENO);
       for (int i = 0; i < lengthCommandSystem; i++ ){
         if (command[i] == NULL) {
            continue;
         }
          if (strcmp(command[i] , ">") == 0) {
            output = open(command[i+1]  ,O_CREAT | O_WRONLY | O_TRUNC  , 0777);
           //  stdout  write 1
            dup2 (output, STDOUT_FILENO);
            close(output);
            command[i] = NULL;
            command[i + 1] = NULL; 
         }else if (strcmp(command[i] , "<") == 0 ) {
         
            inp = open(command[i+1]  ,O_CREAT | O_RDONLY , 0777);
               //stdin read 0
            dup2 (inp, STDIN_FILENO);
            command[i] = NULL;
            command[i + 1] = NULL; 

         } else if (strcmp(command[i] , ">>") == 0) {
            output = open(command[i + 1], O_CREAT | O_WRONLY | O_APPEND , 0777);
     
           // Write 1 stdout
            dup2(output, STDOUT_FILENO);
            close(output);
            command[i] = NULL;
            command[i + 1] = NULL;
         }
       }

   

      // When user clik enter without arqument
         if (command[0] == NULL){
        
            continue;
        }
        // this is a preparation to excute environc
        if(strcmp(command[0] , "environ") == 0 ){
            command[0] = "env" ; 
        }
        // this is to excute clr command.
        if(strcmp(command[0] , "clr") == 0 ){
            command[0] = "clear" ; 
        }
        // this is to excute pause command.
        if (strcmp(command[0], "pause") == 0)
        {
            printf("Paused\n");
                 printf("press <Enter> key to continue\n");
                 while(1){
               	  	char c;
	               	scanf("%c",&c);
            		    if(c=='\n'){
            	     	       break;
                     	} 
       }
        }
        if (strcmp(command[0] , "help") == 0) {
           excute_help();
        }
        // excute quit command and so on.
        else if (strcmp(command[0], "quit") == 0)
        {
            exit(1);
        }else if (strcmp(command[0], "cd") == 0) {
                if (command[1] == NULL) {
                  
                  printCurrentDirectory();
                  printf("\n\n"); 
                  continue;
                }
                 cheakAndChangeDirectory(command);
        }
         else {
            // here We excute command by child
             my_fork  = fork ();
             if ( my_fork == 0){
                excuteCommand(command);
                
             }
             
             else {
                wait(NULL);
                close(STDIN_FILENO);
                close(STDOUT_FILENO);
                dup2(defInp, STDIN_FILENO);
                dup2(defOut, STDOUT_FILENO);
            }
         }
       }
}

