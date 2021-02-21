#include <stdio.h>
#include <math.h>


float xA, yA, xB, yB, xC, yC;
float perimetro;

void leerCoordenadas (char punto, float & puntoX, float & puntoY)
{

    printf ("Introduce el valor de %c para la coordenada X ", punto);
    scanf  ("%f", & puntoX);
    printf ("Introduce el valor de %c para la coordenada Y ", punto);
    scanf ("%f", &puntoY);

}

void leerVertices ()
{
    leerCoordenadas('A', xA, yA);
    leerCoordenadas('B', xB, yB);
    leerCoordenadas('C', xC, yC);
}


float distanciaPunto (float x1, float y1, float x2, float y2)

{

    float deltaX, deltaY;

    deltaX = x1-x2;
    deltaY = y1-y2;

    return sqrt(pow(deltaX,2)+pow(deltaY,2));

}

void calcularPerimetro ()
{
    float ladoAB, ladoBC, ladoCA;

    ladoAB = distanciaPunto (xA, yA, xB, yB);
    ladoBC = distanciaPunto (xB, yB, xC, yC);
    ladoCA = distanciaPunto (xC, yC, xA, yA);

    perimetro = ladoAB + ladoBC + ladoCA;


}

void imprimirPerimetro()
{
    printf ("El perímetro del trángulo es %0.2f", perimetro);
}

int main ()
{
    leerVertices();
    calcularPerimetro();
    imprimirPerimetro();

}