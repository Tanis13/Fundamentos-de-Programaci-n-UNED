# include <stdio.h>
# include <math.h>

float Discriminante (float a, float b, float c)
{
    return pow(b,2.0)-4*a*c;
}

void leerValor (int grado, float & valor)
{

    printf ("Indique cual es el valor de grado %i que desea asignar: ", grado);
    scanf ("%f", &valor);

}

int main ()
{
    float a, b, c;
    float resultado1, resultado2;

    leerValor (2,a);
    leerValor (1,b);
    leerValor (0,c);


    if (a == 0 && b == 0 && c == 0)
    {
        printf("La raiz no tiene soluciones");

    }
    else if (a == 0 && b == 0)
    {
        printf ("La solución es imposible");
    }
    else if  (a== 0)
    {
        resultado1 = (-b+sqrt(Discriminante(a,b,c))/2);
        printf ("Tiene una solución única.\nLa solución es %2.2f", resultado1);

        
    }
    else 
    {
        resultado1 = (-b+sqrt(Discriminante(a,b,c))/2);
        resultado2 = (-b-sqrt(Discriminante(a,b,c))/2);
        printf ("Tiene dos resultados\nEl primer resultado es %2.2f y el segundo es %2.2f", resultado1, resultado2);
    }


}



