#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define MAX_ATTEMPTS 6
#define MAX_WORD_LENGTH 20

int start_game();
void display_hangman(int attempts);
int is_word_complete(char *word_progress);

#endif // GAME_LOGIC_H
