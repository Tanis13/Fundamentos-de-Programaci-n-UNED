#include <stdio.h>

int main()
{
    int lado, espacios;

    printf("Lado? ");
    scanf("%d", &lado);
    espacios = lado;
    

    for (int i = 0; i < lado; i++)
    {
        for (int j = 0; j < espacios; j++)
        {
            printf(" ");
        }
        espacios--;

        for (int j = 0; j < i; j++)
        {

            printf("* ");
        }

        printf("\n");
        
    }

    // A PARTIR DE AQUI REDUCE
    espacios= lado;

    for (int i = 0; i < lado; i++)
    {
        for (int j = 0; j < i; j++)
        {

            printf(" ");
        }

        for (int j = 0; j < espacios; j++)
        {
            printf("* ");
        }
        espacios--;

        printf("\n");
    }
}