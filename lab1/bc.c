#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int num = 0;
    int count = 0;
    printf("请输入一个整数：");
    scanf("%d", &num);
    while (num)
    {
        if (num % 2 == 1)
            count++;
        num >>= 1;
    }
    printf("count=%d\n", count);
    return 0;
}

