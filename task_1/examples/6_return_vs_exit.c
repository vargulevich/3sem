/* notice: _exit() terminates immediately , without running of on_ and at_exit.
   It is important for destructors, etc in C++*/
#include <stdio.h>
#include <stdlib.h>

void f()
{
    printf("Executing f\n");
    exit(0);
}

int main()
{
    f();
    printf("Back from f\n");
}
