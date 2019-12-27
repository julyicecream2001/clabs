#include <stdio.h>
main ()
{
    int num;
    int count = 0;
    num = getchar ();
    while (num)
    {
       num &=(num - 1);
       count++;
    }
    printf("count=%d\n");
    return count;
}