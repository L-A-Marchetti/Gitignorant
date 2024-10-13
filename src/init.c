#include "../include/init.h"
#include "../include/menu.h"

int version_check() {
    FILE *fp;
    char buffer[128];
    fp = popen("git --version", "r");
    if (fp == NULL) {
        printf("Error while executing the command git --version\n");
        return 1; // Error in executing command
    }
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("☑ Git is installed: %s", buffer);
    } else {
        clear_message(1);
        printf("☒ Git is not installed: You can install it by using the command: sudo apt install git\n");
    }
    pclose(fp);
    return 0;
}

void init_process() {
    version_check();
}