#include <stdio.h>

int main()
{
    int altura;
    int espacio;

    printf("Introduce la altura del triágulo a generar: ");
    scanf("%d", &altura);
    espacio = altura;

    

    for (int i = 1; i <= altura; i++)
    {  
        for (int i = 1; i < espacio; i++)
        {

            printf(" ");
        }
        for (int j = 1; j < i; j++)
        {

            printf("%d", j);
        }

        for (int j = i; j > 0; j--)
        {

            printf("%d", j);
        }
        espacio--;
        printf("\n");
    }

}