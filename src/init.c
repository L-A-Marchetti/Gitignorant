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
        printf("\033[0m☑ Git is installed: %s\033[90m", buffer);
    } else {
        clear_message(1);
        printf("\033[0m☒ Git is not installed: You can install it by using the command: sudo apt install git\033[90m\n");
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
    if (create_readme(project_name, project_description) != 0) {
        return;
    }
    if (initialize_git_repo() != 0) {
        return;
    }
    if (name_m_branch() != 0) {
        return;
    }
    if (stage_changes() != 0) {
        return;
    }
    if (commit("first commit") != 0) {
        return;
    }
    if (add_remote(project_remote) != 0) {
        return;
    }
    if (push_upstream() != 0) {
        return;
    }
    printf("\033[0m☑ Repository initialized successfully.\033[90m\n");
    free(project_name);
    free(project_description);
    free(project_remote);
}

int commit(const char *message) {
    char command[256];
    snprintf(command, sizeof(command), "git commit -m \"%s\"", message);
    int result = system(command);
    if (result == 0) {
        printf("\033[0m☑ Changes committed successfully.\033[90m\n");
    } else {
        printf("\033[0m☒ Failed to commit changes. Exit status: %d\n\033[90m", WEXITSTATUS(result));
        return 1;
    }
    return 0;
}

int add_remote(char *remote) {
    char command[256];
    snprintf(command, sizeof(command), "git remote add origin %s", remote);
    int result = system(command);
    if (result == 0) {
        printf("\033[0m☑ Remote added successfully.\033[90m\n");
    } else {
        printf("\033[0m☒ Failed to add the remote. Exit status: %d\n\033[90m", WEXITSTATUS(result));
        return 1;
    }
    return 0;
}

int initialize_git_repo() {
    int result = system("git init");
    if (result == 0) {
        printf("\033[0m☑ Git repository initialized successfully.\033[90m\n");
    } else {
        printf("\033[0m☒ Failed to initialize Git repository. Exit status: %d\033[90m\n", WEXITSTATUS(result));
        return 1;
    }
    return 0;
}

int stage_changes() {
    int result = system("git add -A");
    if (result == 0) {
        printf("\033[0m☑ Files staged successfully.\n\033[90m");
    } else {
        printf("\033[0m☒ Failed to stage files. Exit status: %d\033[90m\n", WEXITSTATUS(result));
        return 1;
    }
    return 0;
}

int push_upstream() {
    int result = system("git push -u origin main");
    if (result == 0) {
        printf("\033[0m☑ Changes pushed successfully.\033[90m\n");
    } else {
        printf("\033[0m☒ Failed to push changes. Exit status: %d\033[90m\n", WEXITSTATUS(result));
        return 1;
    }
    return 0;
}

int name_m_branch() {
    int result = system("git branch -m main");
    if (result == 0) {
        printf("\033[0m☑ Main branch named \"main\" successfully.\033[90m\n");
    } else {
        printf("\033[0m☒ Failed to rename the main branch. Exit status: %d\033[90m\n", WEXITSTATUS(result));
        return 1;
    }
    return 0;
}

int create_readme(char *pn, char *pd) {
    FILE *file = fopen("README.md", "w");
    if (file == NULL) {
        perror("☒ Error opening file");
        return 1;
    }
    fprintf(file, "# %s\n\n", pn);
    fprintf(file, "## Description\n\n%s\n", pd);
    fprintf(file, "Repository initialized using Gitignorant | Support: https://github.com/L-A-Marchetti/Gitignorant\n");
    fclose(file);
    printf("\033[0m☑ README.md created successfully!\033[90m\n");
    return 0;
}