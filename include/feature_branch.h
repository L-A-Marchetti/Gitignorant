#ifndef FEATURE_BRANCH_H
#define FEATURE_BRANCH_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "init.h"

char* format_branch_name(const char* input);
int is_on_main_branch();
int update_main_branch();
void feature_branch_process();
int switch_to_main_if_needed();
int create_and_checkout_branch(const char* branch_name);
int setup_branch_tracking(const char* branch_name);
char* get_current_branch();

#endif // FEATURE_BRANCH_H