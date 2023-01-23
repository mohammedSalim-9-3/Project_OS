#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h> 
#include <ctype.h>
#include "myshell.h"
// delete all commands to don't have any problem
void deletCommandUser(char* command[]) {
    for (int i = 0; i < 10; i++) {
       command[i] = NULL;
    }
}
// When use getLine read sapac in last and the programme not run true
char *deleteEnterCharacter(char *string){
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
    return string;
}
// use getLine to read command from user enter...
char * getCommandFile(char* commandString) {
    size_t bufsize = 0;
    commandString = NULL;
    getline(&commandString,&bufsize,stdin);
    return commandString;
 
}
// fetch command String From User
char * getCommandUser(char* commandString) {
    size_t bufsize = 0;
    commandString = NULL;
    getline(&commandString,&bufsize,stdin);
    return commandString;
 
}

// divide command string to array in command
void splitString (char* command[] , char * commandString) {
       // Wow when you use function excevp you must last index array of str Null
       // command[0] = strtok(commandString , " ");
       // command[1] = strtok(NULL , " ");
     char* progName = strtok(commandString , " ");  
     int index = 0;
     while (progName != NULL) {
        command[index] = progName;
        progName = strtok(NULL , " ");      
        index++;

   }    
   
}
void excuteCommand (char* command[]) {

         execvp(command[0], command);
        

     }
 // cheak is path we send T or F  and change dir.....   
void cheakAndChangeDirectory(char* command[]){
        
   if (cd(command[1]) < 0 ) {
       perror(command[1]); // error message.
    }else {
      cd(command[1]);
    } 
}
// return Int to use in function cheakAndChangeDirectory....
int cd (char * path) {

  // int chdir(const char *path);
     return chdir(path);
}
// printCurrentDirectory is a function to print absolute and its colorful..... 
void printCurrentDirectory() {
  
   char currWorkDir[1000];
	getcwd(currWorkDir, sizeof(currWorkDir));  //return string containing an absolute pathname that is the current working directory of the calling process
	printf("\033[0;31m"); // bold red
	printf("~%s$ ", currWorkDir);
	printf("\033[0m"); // reset

}
// call function help 
void excute_help() {
      char ch;
      size_t bufsize = 0;
      FILE* ptr= fopen("readme" , "r");
      char*line = NULL;
       while (!feof(ptr)  && getline(&line,&bufsize,ptr)!= -1) {
   
        if (strstr(line , "#") != NULL) {
            printf("\033[0;33m");
            printf("If you want to stop enter char < F >: ");
            scanf("%c" , &ch); 
            if (ch == 'F'){
                break;
            }
      } 
	printf("\033[0m"); // reset      
    printf("%s" , line);
      }
      
   }

