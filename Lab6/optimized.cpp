#include <cstdio>
#include <string>
#include "Windows.h"

void new_func1();

int func1()
{
    for(int i = 0; i < 10; i++)
    {
    }
    return 1;
}

int func2(int a)
{
    for(int i = 0; i < 10; i++)
    {
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
        for(int j=10; j > 0; j--)
        {
            if(func2(i) || func1()){
                printf("\n Inside if()\n");
            }
        }
    }

    return 0;
}