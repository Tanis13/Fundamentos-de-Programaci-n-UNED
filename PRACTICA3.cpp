/**************************************
* NOMBRE: #Jose Luis#
* PRIMER APELLIDO: #Carrasco#
* SEGUNDO APELLIDO: #López#
* DNI: #75753442k#
* EMAIL: #jcarrasco216@alumno.uned.es#
***************************************/

#include <stdio.h>

typedef char tipoDia[7];
tipoDia dia[7] = {"LU  ", "MA  ", "MI  ", "JU  ", "VI ", " SA  ", "DO"};
typedef char tipoMes[12];
tipoMes mes[] = {"ENERO     ", "FEBRERO   ", "MARZO     ", "ABRIL     ", "MAYO      ", "JUNIO     ",
                 "JULIO     ", "AGOSTO    ", "SEPTIEMBRE", "OCTUBRE   ", "NOVIEMBRE ", "DICIEMBRE "};

int mesSeleccionado, anio; //Declaración de variables

bool anioBisiesto() //Aquí se determina si el año introducido es bisiesto o no
{
    bool bisiesto;
    if (anio % 4 != 0) bisiesto = false;
    else if (anio % 4 == 0 && anio % 100 != 0) bisiesto = true;
    else if (anio % 4 == 0 && anio % 100 == 0 && anio % 400 == 0) bisiesto = true;
    else if (anio % 4 == 0 && anio % 100 == 0 && anio % 400 != 0) bisiesto = false;
    return bisiesto;
}

int calcularDiasMes(int elMes) //Esta función calcula el número de días que tiene el mes seleccionado del año seleccionado
{
    int diasMes;
    if (elMes == 1 || elMes == 3 || elMes == 5 || elMes == 7 || elMes == 8 || elMes == 10 || elMes == 12) diasMes = 31;
    if (elMes == 4 || elMes == 6 || elMes == 9 || elMes == 11) diasMes = 30;
    if (elMes == 2)
    {
        if (anioBisiesto() == true) diasMes = 29;
        if (anioBisiesto() == false) diasMes = 28;
    }

    return diasMes;
}

int diaComienzaMes(int anio, int mes)
{
    int a = (14 - mes) / 12;
    int y = anio - a;
    int m = mes + 12 * a - 2;
    int d = (0 + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
    return d;
}

int main()
{

    //Aquí piden los datos necesarios
    printf("¿Mes (1..12)?");
    scanf("%i", &mesSeleccionado);
    printf("¿Año (1610..3000)?");
    scanf("%i", &anio);
    printf("\n");
if (anio>=1601 && anio<=3000 && mesSeleccionado>=1 && mesSeleccionado <=12)
{
    //Aquí se imprime el encabezado del mes
    printf("%s", mes[mesSeleccionado - 1]);
    printf("             %i\n", anio);
    for (int i = 0; i < 27; i++) printf("=");
    printf("\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%s", dia[i]);
        if (i == 4)
            printf("|");
    }
    printf("\n");
    for (int i = 0; i < 27; i++) printf("=");
    printf("\n");

    int contador = 1;
    for (int i = 0; i < diaComienzaMes(anio, mesSeleccionado); i++) //imprime los puntos de inicio del mes
    {

        if (i == 4) printf(" . | ");
        else printf(" .  ");
        contador++;
    }

    for (int i = 1; i <= calcularDiasMes(mesSeleccionado); i++) //Imprime los días del mes
    {

        if (i < 10 && contador % 7 == 5) printf(" %i | ", i);
        if (i >= 10 && contador % 7 == 5) printf("%i | ", i);
        if (i < 10 && contador % 7 != 5) printf(" %i  ", i);
        if (i >= 10 && contador % 7 != 5) printf("%i  ", i);
        if (contador % 7 == 0) printf("\n");
        contador++;
    }

    while ((contador - 1) % 7 != 0) //imprime los puntos de final del mes
    {

        if (contador % 7 == 5) printf(" . | ");
        else printf(" .  ");
        contador++;
    }

    printf("\n");
}
}
