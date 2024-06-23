#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define MAX_USERS 100
#define MAX_USER_NAME_LENGTH 50
#define LEADERBOARD_FILE "users.txt"

// User structure with name and high score
typedef struct {
    char name[MAX_USER_NAME_LENGTH];
    int high_score;
} User;

int read_users(User *users, int max_users);
void write_users(User *users, int user_count);
int find_user(const char *name, User *users, int user_count);

#endif // LEADERBOARD_H
