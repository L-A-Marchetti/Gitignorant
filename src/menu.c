#include "../include/menu.h"

int get_menu_input() {
    char input[INPUT_BUFFER];
    int err = scanf("%1s", input);
    if (err != 1) {
        perror("input error");
    }
    while (getchar() != '\n');
    return atoi(input);
}

void print_menu() {
    int is_first = 0;
    char menu[3][32] = {
    "1- Initialize a Git repository.",
    "2- Create a feature branch.",
    "3- Quit."
    };
    int menu_length = sizeof(menu) / sizeof(menu[0]);
    for (int i = 0; i < menu_length; i++) {
        printf("%s\n", menu[i]);
    }
    printf("\n");
    int choice = 0;
    do {
        choice = get_menu_input();
        if (choice < 1 || choice > menu_length) {
            if (is_first == 0) {
                clear_message(1);
                is_first++;
            } else {
                clear_message(2);
            }
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice < 1 || choice > menu_length);
    switch (choice) {
        case 1:
            if (is_first == 0) {
                clear_message(1);
                is_first++;
            } else {
                clear_message(2);
            }
            init_process();
            return;
        case 2:
            if (is_first == 0) {
                clear_message(1);
                is_first++;
            } else {
                clear_message(2);
            }
            feature_branch_process();
            return;
        case 3:
            if (is_first == 0) {
                clear_message(1);
                is_first++;
            } else {
                clear_message(2);
            }
            return;
    }
}

void clear_message(int n) {
    for (int i = 0; i < n; i++) {
        printf("\033[A\033[K");
    }
}

void launch() {
    printf("   ______ _  __   _                                           __ \n");
    printf("  / ____/(_)/ /_ (_)____ _ ____   ____   _____ ____ _ ____   / /_\n");
    printf(" / / __ / // __// // __ `// __ \\ / __ \\ / ___// __ `// __ \\ / __/\n");
    printf("/ /_/ // // /_ / // /_/ // / / // /_/ // /   / /_/ // / / // /_  \n");
    printf("\\____//_/ \\__//_/ \\__, //_/ /_/ \\____//_/    \\__,_//_/ /_/ \\__/  \n");
    printf("                 /____/                                     \n");
    printf("\nVersion %d.%d.%d | Support: https://github.com/L-A-Marchetti/Gitignorant\n\n", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
    print_menu();
}