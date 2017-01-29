#include "readstring.c"



int main () {
    char *arg;
    int i;

    readS(&i, &arg);
    printf("%d, %s", i, arg);

    return 0;
}
