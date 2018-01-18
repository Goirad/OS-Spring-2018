#include "validation.h"

/*
  Overkill for validation, but I intend to build on this anytime a project
  requires validation.

*/

//assume \0 terminated string
struct ValidatedInt parseInt(char * str) {
  if (strlen(str) > INT_SIZE) {
    //the string we received is too long to hold an int
    return (struct ValidatedInt) {
      0, ERR_TOO_LONG
    };
  }else{
    char * check;
    long candidate = strtol(str, &check, 10); //10 is the base
    if(isspace(*check) || *check == 0){
      //ensure that the value fits into an int
      if(candidate < INT_MAX && candidate > INT_MIN){
        return (struct ValidatedInt) {
          (int) candidate, NO_ERR
        };
      }else{
        return (struct ValidatedInt) {
          0, ERR_TOO_LONG
        };
      }

    }else{
      //not a valid int because there was something besides digits
      return (struct ValidatedInt) {
        0, ERR_NON_DIG
      };
    }
  }
}
