#include <stdio.h>


int main() 
{

    char *filename = "test.txt";

    FILE *file;
    int ch;

    file = fopen("test.txt", "r");

    while((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    fclose(file);
    
    return 0;
}