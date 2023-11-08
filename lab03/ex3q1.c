/* Purpose: Simplified version of the dice game Zanzibar. Two players that have three lives 
 * roll three dice three times, and the loser loses a life. 
 * Author: Christopher Vander Veen
 * Date: Sept 27 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void roll(int result[3]) { // I realized after this submission that this was unnecessary and I could put this in main to only execute once.``
  static int seeded = 0;
  if (!seeded) {
    srand(time(NULL));
    seeded = 1;
  }

  for (int i = 0; i < 3; i++) {
    result[i] = rand() % 6 + 1;
  }
}

int calculateScore(int roll[3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++)
      if (roll[j] < roll[i]) {
        int temp = roll[j];
        roll[j] = roll[i];
        roll[i] = temp;
      }
  }

  if (roll[0] == roll[1] && roll[1] == roll[2]) { // Calculates specieal rolls ie. 1,1,1 2,2,2 etc
    switch (roll[0]) {
      case 1: return 999;
      case 2: return 998;
      case 3: return 997;
      case 4: return 996;
      case 5: return 995;
      case 6: return 994;
    }
  }
  if (roll[0] == 1 && roll[1] == 2 && roll[2] == 3) { // Calculates score if not a special roll
    return 993;
  }
  return 100 * roll[2] + 10 * roll[1] + roll[0];
}

void gameLoop(int *p1score, int *p2score) { // pass in pointers so we can change the variables by reference instead of by value.
  int dice[3];
  int turn = 1, player = 1;
  char choice;

  while (player <= 2) {
    turn = 1;
    while (turn <= 3) {
      printf("Turn %d player %d: ", turn, player);
      scanf(" %c", &choice);
      if (choice == 's') {
        break;
      }
      roll(dice);
      int score = calculateScore(dice);
      printf("You rolled: %d %d %d = %d points\n", dice[0], dice[1], dice[2], score);
      if (player == 1) {
        *p1score = score; // dereference to change the actual value at memory location.
      } else if (player == 2) {
        *p2score = score;
      }
      turn++;
    }
    player++;
  }
}

int main(void) {
  int p1lives = 3, p2lives = 3, p1score, p2score;

  while (p1lives > 0 && p2lives > 0) {
    p1score = 0;
    p2score = 0;
    gameLoop(&p1score, &p2score);
    if (p1score > p2score) {
      p2lives--;
      printf("Player 1 wins this round with %d points\n", p1score);
    } else if (p1score < p2score) {
      p1lives--;
      printf("Player 2 wins this round with %d points\n", p2score);
    } else {
      printf("Both players tied this round with %d points\n", p1score);
    }
    printf("Player 1 lives = %d\n", p1lives);
    printf("Player 2 lives = %d\n\n", p2lives);
  }

  if (p2lives == 0) {
    printf("Player 1 wins!\n");
  } else if (p1lives == 0) {
    printf("Player 2 wins!\n");
  }
  return 0;
}
