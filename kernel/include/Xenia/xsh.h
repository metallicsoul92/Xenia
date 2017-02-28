#ifndef XSH_H
#define XSH_H

//shell variables
char *curr_line;
char **lineList;
char *dir;
//shell functions
void shellmain();
char *shell_readLine();
char **shell_split_line(char *line);
int shell_launch(char **args);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_execute(char **args);


#endif // XSH.h
