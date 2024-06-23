#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game_logic.h"
#include "leaderboard.h"

void main_menu() {
    // Load user data from leaderboard file
    User users[MAX_USERS]; // Maximum 100 users
    int user_count = read_users(users, MAX_USERS);

    // Ask for username and check if it's a new or existing user
    printf("Enter your username: ");
    char username[MAX_USER_NAME_LENGTH];
    scanf("%s", username);

    int user_index = find_user(username, users, user_count);

    if (user_index == -1) {
        // New user
        user_index = user_count++;
        strncpy(users[user_index].name, username, MAX_USER_NAME_LENGTH);
        users[user_index].high_score = MAX_ATTEMPTS; // Default high score
        printf("New user added: %s\n", username);
    } else {
        // Existing user
        printf("Welcome back, %s! Your high score: %d\n", users[user_index].name, users[user_index].high_score);
    }

    // Main menu loop
    while (1) {
        printf("\nMain Menu:\n");
        printf("1. Start New Game\n");
        printf("2. View Leaderboard\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Ask for category and start the game
                printf("\nSelect a category:\n");
                printf("1. Books\n");
                printf("2. Persons\n");
                printf("3. Things\n");
                printf("4. Animals\n");
                printf("5. Fruits\n");
                printf("Enter your choice: ");

                int category_choice;
                scanf("%d", &category_choice);

                if (category_choice < 1 || category_choice > 5) {
                    printf("Invalid category choice.\n");
                    break;
                }

                // Load words from the selected category file
                char filename[20];
                switch (category_choice) {
                    case 1:
                        strcpy(filename, "words/book.txt");
                        break;
                    case 2:
                        strcpy(filename, "words/persons.txt");
                        break;
                    case 3:
                        strcpy(filename, "words/things.txt");
                        break;
                    case 4:
                        strcpy(filename, "words/animal.txt");
                        break;
                    case 5:
                        strcpy(filename, "words/fruits.txt");
                        break;
                }

                FILE *file = fopen(filename, "r");
                if (!file) {
                    printf("Error: Could not open file.\n");
                    break;
                }

                // Count the number of words in the file
                int word_count = 0;
                char word[MAX_WORD_LENGTH];
                while (fgets(word, MAX_WORD_LENGTH, file) != NULL) {
                    word_count++;
                }
                rewind(file);

                // Select a random word
                srand((unsigned int)time(NULL));
                int selected_index = rand() % word_count;

                // Skip to the selected word
                for (int i = 0; i < selected_index; i++) {
                    fgets(word, MAX_WORD_LENGTH, file);
                }
                fclose(file);

                // Remove newline character from the word
                word[strcspn(word, "\n")] = '\0';

                // Start the game with the selected word
                int score = start_game(word);
                if (score < users[user_index].high_score) {
                    users[user_index].high_score = score; // Update high score
                    printf("New high score for %s: %d\n", username, score);
                }
                break;
            }
            case 2: {
                // Display the leaderboard
                printf("\nLeaderboard:\n");
                for (int i = 0; i < user_count; i++) {
                    printf("%d. %s - High Score: %d\n", i + 1, users[i].name, users[i].high_score);
                }
                break;
            }
            case 3:
                // Save the updated leaderboard before exiting
                write_users(users, user_count);
                return; // Exit the program
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}

int main() {
    main_menu();
    return 0;
}
