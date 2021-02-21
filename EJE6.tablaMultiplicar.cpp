#include <stdio.h>

int main ()
{
int tabla;

printf ("Introduce un número para mostrar la tabla de multiplicar: ");
scanf ("%d", &tabla);

printf ("Tabla de multiplicar del %d\n", tabla);
printf ("===========================\n");

for(int i = 0; i<= 10; i++){
printf("%6d X %2d = %3d\n",tabla, i, tabla*i);

}

}