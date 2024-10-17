#include "../include/feature_push.h"
#include "../include/init.h"
#include "../include/feature_branch.h"
#include "../include/menu.h"
#include <readline/readline.h>
#include <readline/history.h>

void push_feature_branch() {
    // Get the current branch name
    char* branch_name = get_current_branch();
    if (branch_name == NULL) {
        printf("☒ Unable to determine the current branch.\n");
        return;
    }
    if (show_current_branch(branch_name) != 0) {
        clear_message(2);
        return;
    }
    clear_message(2);
    // Show modified files
    show_modified_files();
    // Ask user if they want to stage all files or choose
    if (verify_staging() != 0) {
        free(branch_name);
        return;
    }
    // Ask for the commit message
    printf("Enter the commit message: ");
    char* commit_message = get_input();
    if (commit_message == NULL) {
        return;
    }
    if (commit(commit_message) != 0) {
        return;
    }
    // Commit and push
    if (push() != 0) {
        return;
    }
    free(commit_message);
    free(branch_name); // Free allocated memory for branch name
}


void show_modified_files() {
    printf("Unstaged/Untracked files:\n");
    system("git status -s");
}

void stage_files() {
    using_history();
    char *file;

    while (1) {
        file = readline("Enter the name of the file to stage (or 'done' to finish): ");
        if (file == NULL) {
            printf("☒ Error reading input.\n");
            break;
        }
        if (strcmp(file, "done") == 0) {
            free(file);
            break;
        }
        char command[300];
        snprintf(command, sizeof(command), "git add %s", file);
        if (system(command) != 0) {
            printf("☒ Failed to add file %s.\n", file);
        } else {
            printf("☑ File %s added successfully.\n", file);
        }
        free(file); // Libérer la mémoire allouée par readline
    }
}

int push() {
    int result = system("git push > /dev/null 2>&1");
    if (result == 0) {
        printf("☑ Changes pushed successfully.\n");
    } else {
        printf("☒ Failed to push changes. Exit status: %d\n", WEXITSTATUS(result));
        return 1;
    }
    return 0;
}

int show_current_branch(char* branch_name) {
    // Show the current branch to the user
    printf("Current branch: %s\n", branch_name);
    printf("Do you want to push this branch? (y/n): ");
    char confirmation;
    scanf(" %c", &confirmation);
    if (confirmation != 'y' && confirmation != 'Y') {
        printf("Operation cancelled.\n");
        free(branch_name);
        return 1;
    }
    return 0;
}

int verify_staging() {
    printf("Do you want to stage all files (a) or choose specific files (c)? ");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'a' || choice == 'A') {
        system("git add -A");
    } else if (choice == 'c' || choice == 'C') {
        stage_files();
    } else {
        printf("Invalid choice. Operation cancelled.\n");
        return 1;
    }
    while (getchar() != '\n');
    return 0;
}