#include <stdio.h>
int main()
{
    unsigned int a = 1, b = 0;
    while (a>0)     
    {        
        a++;
    }     
     printf("%u,%lu\n", a-1, (sizeof(a-1))*8 );
     return 0;
}