#ifndef INIT_H
#define INIT_H

#include <stdio.h>

char* get_input();
void init_process();
int version_check();
int create_readme(char* pn, char* pd);
int initialize_git_repo();
int stage_changes();
int commit(const char *message);
int add_remote(char* remote);
int push();

#endif // INIT_H