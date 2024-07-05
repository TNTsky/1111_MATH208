#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char *Name[12] = {"January", "February", "March", "April", "May",
                        "June", "July", "August","September",
                        "October", "November", "December"};

void convert(char *a)
{
    char *year = strtok(a, "/");
    char *month = strtok(NULL, "/");
    char *day = strtok(NULL, "/");

    int num = atoi(month);
    printf("%s%s%s",Name[num-1],day,year);
}

int main()
{
    char data[50];
    while (1) 
    {
        scanf("%c",&data);
        convert(data);
    }
}