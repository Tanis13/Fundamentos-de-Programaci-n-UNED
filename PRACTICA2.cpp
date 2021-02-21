/**************************************
* NOMBRE: #Tanis13#
* PRIMER APELLIDO: #Kanan#
* SEGUNDO APELLIDO: #Halfelven#
* DNI: #00001101k#
* EMAIL: #Tanis13@krynn.com#
***************************************/

#include <stdio.h>

int main()
{
    int numeroLado; //declaración de variables
    int i = 0;

    printf("¿Lado del Rombo?"); //Solicitud de numero de lados
    scanf("%i", &numeroLado);
    if (numeroLado <= 20 && numeroLado > 0) //Condicional para evitar ejecutar el rombo por encima de mas de 20 y menos de 1
    {
        while (i < numeroLado) //Loop para que se ejecute la impresión de las líneas el número de veces seleccionado (parte superior del rombo)
        {
            

                for (int k = i; k + 1 < numeroLado; k++) printf(" ");  //Imprime los espacios a la izquierda del rombo

                for (int k = 1; k - 1 <= i; k++) //Imprime los símbolos de la parte superior izquierda
                {

                    if (k % 4 == 1) printf("@");
                    if (k % 4 == 2) printf(".");
                    if (k % 4 == 3) printf("o");
                    if (k % 4 == 0 && k != 0) printf(".");
                }
                for (int j = i; j > 0; j--) //Imprime los símbolos de la parte superior derecha
                {
                    if (j % 4 == 1) printf("@");
                    if (j % 4 == 2) printf(".");
                    if (j % 4 == 3) printf("o");
                    if (j % 4 == 0 && j != 0) printf(".");
                }
           

            printf("\n");
            i++;
        }

        i = numeroLado;

        while (i > 0) //Loop para que se ejecute la impresión de las líneas el número de veces seleccionado (parte inferior del rombo)
        {

            for (int k = numeroLado; k >= i; k--) printf(" "); //Imprime los espacios a la izquierda del rombo

            for (int k = 1; k <= i - 1; k++) //Imprime los símbolos de la parte inferior izquierda
            {

                if (k % 4 == 1) printf("@");
                if (k % 4 == 2) printf(".");
                if (k % 4 == 3) printf("o");
                if (k % 4 == 0 && k != 0) printf(".");
            }

            for (int j = i - 2; j > 0; j--) //Imprime los símbolos de la parte inferior derecha
            {
                if (j % 4 == 1) printf("@");
                if (j % 4 == 2) printf(".");
                if (j % 4 == 3) printf("o");
                if (j % 4 == 0 && j != 0) printf(".");
            }

            printf("\n");
            i--;
        }
    }
}
