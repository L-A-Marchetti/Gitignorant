#ifndef INIT_H
#define INIT_H

#include <stdio.h>

FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);
void init_process();
int version_check();

#endif // INIT_H