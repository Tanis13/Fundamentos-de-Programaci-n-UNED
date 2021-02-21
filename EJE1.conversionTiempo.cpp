#include <stdio.h>

int main()
{
    int horas, minutos, segundos;

    printf("Introduce los segundos que quieras transformar: ");
    scanf("%d", &segundos);

    horas = segundos / 3600;
    minutos = segundos % 3600;
    segundos = minutos % 60;
    minutos = minutos / 60;
    segundos = segundos % 60;

    printf("Equivale a %d horas, %d minutos y %d segundos", horas, minutos, segundos);
}