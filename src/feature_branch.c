#include "../include/feature_branch.h"
#include "../include/menu.h"

char* format_branch_name(const char* input) {
    char* formatted = strdup(input);
    char* p = formatted;
    while (*p) {
        if (isspace(*p)) {
            *p = '-';
        } else {
            *p = (char)tolower((unsigned char)*p);
        }
        p++;
    }
    return formatted;
}


int is_on_main_branch() {
    FILE *fp;
    char buffer[128];
    fp = popen("git rev-parse --abbrev-ref HEAD", "r");
    if (fp == NULL) {
        printf("Error while checking current branch\n");
        return 0;
    }
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        pclose(fp);
        return (strcmp(buffer, "main\n") == 0);
    }
    pclose(fp);
    return 0;
}

int update_main_branch() {
    int result = system("git pull origin main > /dev/null 2>&1");
    if (result == 0) {
        printf("☑ Main branch updated successfully.\n");
        return 0;
    } else {
        printf("☒ Failed to update main branch. Exit status: %d\n", WEXITSTATUS(result));
        return 1;
    }
}

int switch_to_main_if_needed() {
    if (!is_on_main_branch()) {
        printf("You are not on the main branch. Update main to start new branch from latest? (y/n): ");
        char response;
        scanf(" %c", &response);
        if (response == 'y' || response == 'Y') {
            clear_message(1);
            if (system("git checkout main > /dev/null 2>&1") != 0) {
                printf("☒ Failed to switch to main branch.\n");
                return 1;
            }
            printf("☑ Successfully switched to main branch.\n");
        } else {
            printf("Operation cancelled.\n");
            return 1;
        }
    }
    return 0;
}

int create_and_checkout_branch(const char* branch_name) {
    char command[256];
    snprintf(command, sizeof(command), "git checkout -b %s > /dev/null 2>&1", branch_name);
    if (system(command) == 0) {
        printf("☑ Feature branch '%s' created and checked out successfully.\n", branch_name);
        return 0;
    } else {
        printf("☒ Failed to create and checkout feature branch.\n");
        return 1;
    }
}

int setup_branch_tracking(const char* branch_name) {
    char command[256];
    snprintf(command, sizeof(command), "git push -u origin %s > /dev/null 2>&1", branch_name);
    if (system(command) == 0) {
        printf("☑ Branch tracking set up successfully.\n");
        return 0;
    } else {
        printf("☒ Failed to set up branch tracking.\n");
        return 1;
    }
}

char* get_current_branch() {
    FILE *fp;
    char *branch = malloc(256);
    if (branch == NULL) {
        return NULL;
    }
    fp = popen("git rev-parse --abbrev-ref HEAD", "r");
    if (fp == NULL) {
        free(branch);
        return NULL;
    }
    if (fgets(branch, 256, fp) == NULL) {
        pclose(fp);
        free(branch);
        return NULL;
    }
    pclose(fp);
    branch[strcspn(branch, "\n")] = 0; 
    return branch;
}

void feature_branch_process() {
    printf("Enter the name of the new feature branch: ");
    char* branch_name = get_input();
    if (branch_name == NULL) {
        return;
    }
    branch_name[strcspn(branch_name, "\n")] = 0;
    clear_message(1);
    char* formatted_branch_name = format_branch_name(branch_name);
    free(branch_name);
    if (switch_to_main_if_needed() != 0 || update_main_branch() != 0) {
        free(formatted_branch_name);
        return;
    }
    if (create_and_checkout_branch(formatted_branch_name) == 0) {
        setup_branch_tracking(formatted_branch_name);
    }
    char* current_branch = get_current_branch();
    if (current_branch != NULL) {
        printf("☑ Current branch: %s\n", current_branch);
        free(current_branch);
    } else {
        printf("☒ Unable to determine current branch.\n");
    }
    free(formatted_branch_name);
}

