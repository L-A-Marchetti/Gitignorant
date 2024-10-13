#include "../include/init.h"
#include "../include/menu.h"

int version_check() {
    FILE *fp;
    char buffer[128];
    fp = popen("git --version", "r");
    if (fp == NULL) {
        printf("Error while executing the command git --version\n");
        return 1;
    }
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("☑ Git is installed: %s", buffer);
    } else {
        clear_message(1);
        printf("☒ Git is not installed: You can install it by using the command: sudo apt install git\n");
        pclose(fp);
        return 1;
    }
    pclose(fp);
    return 0;
}

char* get_input() {
    char* input = NULL;
    size_t size = 0;
    if (getline(&input, &size, stdin) == -1) {
        perror("get input:");
        return NULL;
    }
    return input;
}

void init_process() {
    printf("Project name: ");
    char* project_name = get_input();
    printf("Short description: ");
    char* project_description = get_input();
    printf("Remote URL (example: https://github.com/L-A-Marchetti/Gitignorant.git): ");
    char* project_remote = get_input();
    clear_message(3);
    if (version_check() != 0) {
        return;
    }
    create_readme(project_name, project_description);
    printf("%s", project_remote);
}

void create_readme(char *pn, char *pd) {
    FILE *file = fopen("README.md", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "# %s\n\n", pn);
    fprintf(file, "## Description\n\n%s\n", pd);
    fprintf(file, "Repository initialized using Gitignorant | Support: https://github.com/L-A-Marchetti/Gitignorant\n");
    fclose(file);
    printf("☑ README.md created successfully!\n");
}