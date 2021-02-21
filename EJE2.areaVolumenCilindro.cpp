#include <stdio.h>

int main ()
{
    const float Pi = 3.1416;
    float radio, altura, area, volumen;

    printf ("Introduce el valor del rádio del cilindro: ");
    scanf ("%f", &radio);
    printf ("Introduce el valor de la altura del cilindro: ");
    scanf ("%f", &altura);

    area = 2.0 * Pi * radio * (radio + altura);
    volumen = Pi * radio * radio * altura;

    printf ("El area del cilindro con radio %.2f y altura %.2f es de %.2f\n", radio, altura, area);
    printf ("El volumen de radio %.2f y altura %.2f es de %.2f", radio, altura, volumen);




}