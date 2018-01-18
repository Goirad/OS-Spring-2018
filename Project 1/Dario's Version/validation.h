#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define INT_SIZE 11  //1 (+/-) + 10 (number of digits in MAX_INT)
#define NO_ERR       0
#define ERR_TOO_LONG 1
#define ERR_NON_DIG  2

struct ValidatedInt {
  int value;
  char error;
};

struct ValidatedInt parseInt(char * str);
