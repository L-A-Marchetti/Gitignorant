#ifndef FEATURE_PUSH_H
#define FEATURE_PUSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_modified_files();
void stage_files();
int push();
int show_current_branch(char* branch_name);
int verify_staging();
void push_feature_branch();

#endif // FEATURE_PUSH_H