#include <stdio.h>

int main()
{
    int valor1, valor2, valor3;
    int aux;

    printf("Introduce el primer valor: ");
    scanf("%d", &valor1);
    printf("Introduce el segundo valor:");
    scanf("%d", &valor2);
    printf("Introduce el último valor: ");
    scanf("%d", &valor3);

    if (valor1 > valor2)
    {
        aux = valor1;
        valor1 = valor2;
        valor2 = aux;
    }

    if (valor1 > valor3)
    {
        aux = valor1;
        valor1 = valor3;
        valor3 = aux;
    }

    if (valor2 > valor3)
    {
        aux = valor2;
        valor2 = valor3;
        valor3 = aux;
    }

    printf("%d, %d, %d", valor1, valor2, valor3);
}