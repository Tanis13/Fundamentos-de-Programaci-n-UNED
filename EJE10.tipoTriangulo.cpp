#include <stdio.h>

int main ()
{
    float ladoA, ladoB, ladoC;
    printf ("Introduce el primer lado: ");
    scanf ("%f", &ladoA);
    printf("Introduce el segundo valor ");
    scanf ("%f", &ladoB);
    printf ("Introduce el tercer lado: ");
    scanf ("%f", &ladoC);

    if (ladoA > ladoB+ladoC || ladoB > ladoA+ladoC || ladoC > ladoA+ ladoB ) printf ("No forman un triángulo, uno des sus lados es mayor que la suma de los otros dos\n");

    else if (ladoA == ladoB && ladoB == ladoC) printf ("Es un triángulo equilátero. Sus tres lado son iguales");

    else if (ladoA == ladoB && ladoB != ladoC || ladoA == ladoC && ladoC != ladoB || ladoC == ladoB && ladoB != ladoA ) printf ("Es un triángulo isosceles. Tiene dos de sus lados iguales y otro distinto");

    else if (ladoA != ladoB && ladoB != ladoC) printf ("Es un triángulo escaleno. Sus tres lados son diferentes");
     
    if ((ladoA * ladoA) == ((ladoB*ladoB)+(ladoC*ladoC)) || (ladoB * ladoB) == ((ladoA*ladoA)+(ladoC*ladoC)) || (ladoC * ladoC) == ((ladoB*ladoB)+(ladoA*ladoA))) 
    printf ("Es un triángulo rectángulo. Sus lados cumplen el teorema de pitágora");
}