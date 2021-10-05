#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int 
modulo(int a, int b)
{
    int res = a - ((a / b) * b);
    return res + (res < 0) * b;
}

int*
eucExt(int a, int b)
{
    int* res = (int*)malloc(sizeof(int) * 3);
    if (modulo(a, b) == 0) {
        res[0] = b;
        res[1] = 0;
        res[2] = 1;
        return res;
    } else {
        res = eucExt(b, modulo(a, b));
        int tempX = res[1];
        res[1] = res[2];
        res[2] = tempX - ((a / b) * res[2]);
        return res;
    }
}

int*
extMcdint(int a, int b)
{
    int* array = (int*)malloc(sizeof(int) * 3);
    int q = a / b;
    int res = a - (q * b);

    int s1 = 0;
    int s2 = 0;
    int s = s1 - (q * s2);

    int t1 = 0;
    int t2 = 1;
    int t = t1 - (q * t2);

    while (res > 0)
    {
        a = b;
        b = res;
        q = a / b;
        res = a - (q * b);

        s1 = s2;
        s2 = s;
        s = s1 - (q * s2);

        t1 = t2;
        t2 = t;
        t = t1 - (q * t2);
    }

    array[0] = b;
    array[1] = t2;
    array[2] = t;
    return array;
}

int
main(int argc, char *argv[])
{
    if (argc == 2 && (!strcmp(argv[1], "-h") || (!strcmp(argv[1], "--help")))) {
        printf("Usage: gcd [-h] [--help] [num1 num2]\n");
    } else if (argc > 2) {
        int* results = eucExt(atoi(argv[1]), atoi(argv[2]));
        printf("Results: a:\t%s\tb:\t%s\t\nGCD:\t%i\nX:\t%i\nY:\t%i\n", argv[1], argv[2], results[0], results[1], results[2]);
    }
    return 0;
}
