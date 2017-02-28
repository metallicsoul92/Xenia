#include "../include/Xenia/xsh.h"
#include <stdio.h>
void shellmain()
{
  char **args;
  dir = "/";
  int status;
  do{
    printf("%s>>", dir);
    curr_line =shell_readLine();
    args = shell_split_line(curr_line);
    status = shell_execute(args);

    free(line);
    free(args);
  }while(status);
}
char *shell_readLine();
char **shell_split_line(char *line);
int shell_launch(char **args);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_execute(char **args);
