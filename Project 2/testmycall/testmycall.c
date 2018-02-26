#include<stdio.h>
#include "testmycall.h"

int main(void) {

   printf("%d\n", syscall(__NR_mycall, 3848995, 5154146));
}
