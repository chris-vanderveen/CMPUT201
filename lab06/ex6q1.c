#include "ex6q1.h"
#include <stdint.h>

#define LEN 200000000
uint32_t MEMO[LEN];

// This function should be pure recursion - no dynamic programming allowed
uint32_t exp_mod_1(uint32_t base, uint32_t exp, uint32_t modulo) {
  EXP_MOD_1_CALL_COUNT ++;
  uint32_t left, right;

  if (exp == 1) {
    return base % modulo;
  }
  
  left = exp_mod_1(base, exp / 2, modulo);
  right = exp_mod_1(base, exp - exp /2, modulo);

  return (left * right) % modulo;
}

// This function should store the values of previous calls to exp_mod_2 in an
// array and use them for later calculations.
uint32_t exp_mod_2(uint32_t base, uint32_t exp, uint32_t modulo) {
  uint32_t half, result, temp1, temp2;
  EXP_MOD_2_CALL_COUNT++;

  if (exp == 1) {
    return base % modulo;
  }

  if (MEMO[exp] != 0) {
    return MEMO[exp];
  }
  
  half = exp / 2;
  temp1 = exp_mod_2(base, half, modulo);

  if (exp % 2 == 0) {
    result = (temp1 * temp1) % modulo;
  } else {
    temp2 = exp_mod_2(base, exp - half, modulo);
    result = (temp1 * temp2) % modulo;
  }

  MEMO[exp] = result;
  return result;
}

int main(void) {
    uint32_t base, exp, modulo;

    if (scanf("%d %d %d", &base, &exp, &modulo) != 3) {
        return 1;
    }

    uint32_t mod_1 = exp_mod_1(base, exp, modulo);
    uint32_t mod_2 = exp_mod_2(base, exp, modulo);

    fprintf(stdout, "exp_mod_1 calls: %d\n", EXP_MOD_1_CALL_COUNT);
    fprintf(stdout, "exp_mod_2 calls: %d\n", EXP_MOD_2_CALL_COUNT);
    fprintf(stdout, "%d == %d\n", mod_1, mod_2);
	return 0;
}
