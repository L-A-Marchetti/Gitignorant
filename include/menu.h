#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include "feature_branch.h"

#define MAJOR_VERSION 0
#define MINOR_VERSION 0
#define PATCH_VERSION 1
#define INPUT_BUFFER 2

void launch();
void print_menu();
int get_menu_input();
void clear_message(int n);

#endif // MENU_H