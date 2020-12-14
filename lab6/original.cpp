#include <cstdio>
#include <string>
#include "windows.h"

void new_func1();

int func1()
{
    for(int i = 0; i < 100000000; i++)
    {
        Sleep(10000000);
    }
    return 1;
}

int func2(int a)
{
    for(int i = 0; i < 10; i++)
    {
        Sleep(1);
        if(i>a) return 1;
    }
    return 0;
}

int main()
{
    printf("\n Inside main()\n");
    char typeOfShape[10];
    scanf("%s", typeOfShape);

    for(int i = 0; i < 10 ;i++)
    {
        for(int j=1000000; j > 0; j--)
        {
            if(func1() || func2(i)){
                printf("\n Inside if()\n");
            }
        }
    }

    return 0;
}