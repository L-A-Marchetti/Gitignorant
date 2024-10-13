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
    char menu[2][32] = {
    "1- Initialize a Git repository.",
    "2- Quit."
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
                printf("\033[A\033[K");
                is_first++;
            } else {
                printf("\033[A\033[K");
                printf("\033[A\033[K");
            }
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice < 1 || choice > menu_length);
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