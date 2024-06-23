#include <stdio.h>
#include <string.h>
#include "leaderboard.h"

// Reads all users from the leaderboard file
int read_users(User *users, int max_users) {
    FILE *file = fopen(LEADERBOARD_FILE, "r");
    if (!file) {
        return 0; // No existing file
    }

    int count = 0;
    while (fscanf(file, "%s %d", users[count].name, &users[count].high_score) == 2 && count < max_users) {
        count++;
    }

    fclose(file);
    return count;
}

// Writes all users to the leaderboard file
void write_users(User *users, int user_count) {
    FILE *file = fopen(LEADERBOARD_FILE, "w");
    if (!file) {
        printf("Error: Could not write to leaderboard file.\n");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s %d\n", users[i].name, users[i].high_score);
    }

    fclose(file);
}

// Find user by name
int find_user(const char *name, User *users, int user_count) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

