/*
Contoh masukan dan keluaran
---------------------------
    $ date
    Tue Dec  9 13:34:17 WIB 2014
    $ whoami
    auriza
    $ exit
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
void split_words(char *string, char **words) {
  int i;
  words[0] = strtok(string, " \n");

  for (i = 0; words[i]; i++) 
    words[i + 1] = strtok(NULL, " \n");
}

int main () {
  char cmd[80];         // String perintah
  char *args[20];       // argumen string
  char *user = getenv("USER");
  char hostname[90]; 
  gethostname(hostname, 90);

  while(1) {
    pid_t pid;
    char curcwd[90];
    getcwd(curcwd, 90);
    
    printf("%s $ %s [%s] ", user, hostname, curcwd);
    fgets(cmd, sizeof(cmd), stdin);
    // printf("%s", cmd);
    split_words(cmd, args);

    // for(int i = 0; args[i] != NULL; i++) 
    //  printf("%s, ", args[i]);
    // printf("\n");
    
    if(args[0] == NULL)
      continue;
    
    if(strcmp(args[0], "exit") == 0) 
      break;

    else if (strcmp(args[0], "cd") == 0) {
      // char oldcwd[90];
      // getcwd(oldcwd, sizeof(oldcwd));
      char *targetDir = args[1];
      if(targetDir == NULL || !strcmp(targetDir, "~")) {
        targetDir = getenv("HOME");
        
      }

      if (chdir(targetDir) != 0) {
        perror("cd");
      }

      continue;
    } else {
      pid = fork();

      if (pid == 0) {
        int exec_val = execvp(args[0], args); 
        if(exec_val == -1) {
          perror(args[0]);
          return -1;
      } 
      } else if (pid > 0){
        wait(NULL);
      } else {
        perror("fork");
      }

 
    }
    

 }                       

  return 0;
}
