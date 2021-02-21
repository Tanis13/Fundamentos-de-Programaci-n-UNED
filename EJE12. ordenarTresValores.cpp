#include <stdio.h>

void ordenarDatos(int &a, int &b)
{
    int aux;
    if (a < b)
    {
        aux = a;
        a = b;
        b = aux;
    }
}

void pedirDatos(char orden, int &numero)
{
    printf("Introduce el valor %c ", orden);
    scanf("%d", &numero);
}

int main()
{
    char salir = ' ';
    int numeroA, numeroB, numeroC;
    while (salir != 'n')
    {
        pedirDatos('A', numeroA);
        pedirDatos('B', numeroB);
        pedirDatos('c', numeroC);

        ordenarDatos(numeroA, numeroB);
        ordenarDatos(numeroA, numeroC);
        ordenarDatos(numeroB, numeroC);

        printf("El orden de mayor a menor es %d, %d y %d\n", numeroA, numeroB, numeroC);

        while (salir != 's' && salir != 'n')
        {
            printf("Pulse 's' para continuar o 'n' para salir ");
            scanf("%c", &salir);
        }
    }
}