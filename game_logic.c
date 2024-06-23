#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "game_logic.h"

#define MAX_ATTEMPTS 6
#define MAX_WORD_LENGTH 20

void display_hangman(int attempts) {
    const char *hangman[] = {
        "  +---+\n      |\n      |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n      |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n  |   |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n /|   |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n /    |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
    };
    printf("%s\n", hangman[attempts]);
}

int is_word_complete( char *word_progress) {
    return strchr(word_progress, '_') == NULL;
}

int start_game(const char *word) {
    int word_length = (int)strlen(word);
    char word_progress[MAX_WORD_LENGTH] = {0};

    // Initialize the word progress with underscores
    for (int i = 0; i < word_length; i++) {
        word_progress[i] = '_';
    }

    // Initialize attempts and guessed letters
    int attempts = 0;
    char guessed_letters[26] = {0};
    int guessed_count = 0;

    while (attempts < MAX_ATTEMPTS) {
        // Display current game state
        display_hangman(attempts);
        printf("Word: %s\n", word_progress);
        printf("Guessed Letters: ");
        for (int i = 0; i < guessed_count; i++) {
            printf("%c ", guessed_letters[i]);
        }
        printf("\n");

        // Get user input
        printf("Guess a letter: ");
        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("Invalid input. Please guess a letter.\n");
            continue;
        }

        // Check if the letter has already been guessed
        int already_guessed = 0;
        for (int i = 0; i < guessed_count; i++) {
            if (guessed_letters[i] == guess) {
                already_guessed = 1;
                break;
            }
        }

        if (already_guessed) {
            printf("You've already guessed that letter.\n");
            continue;
        }

        // Add to guessed letters
        guessed_letters[guessed_count++] = guess;

        // Check if the guess is correct
        int correct_guess = 0;
        for (int i = 0; i < word_length; i++) {
            if (word[i] == guess) {
                word_progress[i] = guess;
                correct_guess = 1;
            }
        }

        if (!correct_guess) {
            attempts++;
        }

        if (is_word_complete(word_progress)) {
            printf("Congratulations! You guessed the word: %s\n", word);
            return attempts; // The score is the number of attempts taken
        }
    }

    if (attempts == MAX_ATTEMPTS) {
        display_hangman(attempts);
        printf("Game over! The word was: %s\n", word);
    }

    return MAX_ATTEMPTS; // If they lose, maximum attempts is the score
}
