#include <stdio.h>

 enum tipoDia
{
    Lunes,
    Martes,
    Miercoles,
    Jueves,
    Viernes,
    Sabado,
    Domingo
};
 enum tipoMes
{
    Enero,
    Febrero,
    Marzo,
    Abril,
    Mayo,
    Junio,
    Julio,
    Agosto,
    Septiembre,
    Octubre,
    Noviembre,
    Diciembre
};
 struct tipoFecha
{
    int dia;
    tipoMes mes;
    int anio;
};

tipoDia sumarDia(tipoDia dia, int n)
{ //Función para sumar días de las semana ciclicamente
    const int diasSemana = 7;
    int aux;

    aux = (int(dia) + n) % diasSemana;
    return tipoDia(aux);
}

tipoDia diaDeLaSemana(tipoFecha fecha)
{ //Función para calcular el día de la semana que corresponde a una fecha

    const int origen = 89;
    tipoDia treintaUnoDiciembre88 = Sabado;
    bool bisiesto;
    int increBisis, increAnnos, increDias;
    tipoMes m = fecha.mes;
    int a = fecha.anio;

    if (m == Enero)
    {
        increDias = 0;
    }
    else if (m == Febrero)
    {
        increDias = 3;
    }
    else if (m == Marzo)
    {
        increDias = 3;
    }
    else if (m == Abril)
    {
        increDias = 6;
    }
    else if (m == Mayo)
    {
        increDias = 1;
    }
    else if (m == Junio)
    {
        increDias = 4;
    }
    else if (m == Julio)
    {
        increDias = 6;
    }
    else if (m == Agosto)
    {
        increDias = 2;
    }
    else if (m == Septiembre)
    {
        increDias = 5;
    }
    else if (m == Octubre)
    {
        increDias = 0;
    }
    else if (m == Noviembre)
    {
        increDias = 3;
    }
    else
    {
        increDias = 5;
    }

    bisiesto = (a % 4) == 0;
    if (a < origen)
    {
        a = a + 100;
    }

    increAnnos = a - origen;
    increBisis = increAnnos / 4;
    increDias = increDias + fecha.dia + increAnnos + increBisis;

    if (bisiesto && (m > Febrero))
    {
        increDias++;
    }
    return sumarDia(treintaUnoDiciembre88, increDias);
}

void escribirDia(tipoDia s)
{ //procedimiento para escribir el día

    if (s == Lunes)
        printf("Lunes");
    else if (s == Martes)
        printf("Martes");
    else if (s == Miercoles)
        printf("Miércoles");
    else if (s == Jueves)
        printf("Jueves");
    else if (s == Viernes)
        printf("Viernes");
    else if (s == Sabado)
        printf("Sábado");
    else if (s == Domingo)
        printf("Domingo");
}

void leerFecha(tipoFecha &fecha)
{ // procedimiento  para leer una fecha

    int mes;
    scanf("%d/%d/%d", &fecha.dia, &mes, &fecha.anio);
    fecha.mes = tipoMes(mes - 1);
    if (fecha.anio >= 100)
    {
        fecha.anio = fecha.anio % 100;
    }
}

void escribirFecha(tipoFecha fecha)
{ //procedimeinto para escribir la fecha
    printf("%02d/%02d/%02d", fecha.dia, int(fecha.mes + 1), fecha.anio);
}

int main()
{
    tipoFecha fecha;
    char tecla;
    tipoDia hoy;
    tipoMes pasado;

    hoy = Miercoles;
    pasado = Noviembre;
    tecla ='s';
    while (tecla != 'n'){
        printf("¿Dia Mes Año (DD/MM/AA)?");
        leerFecha (fecha);
        printf ("fecha: ");
        escribirFecha ( fecha);
        printf (" Día de la semana : ");
        escribirDia (diaDeLaSemana (fecha));
        tecla = ' ';
        printf ( "\n\n¿Otra Fecha(S/N)? ");
        while ((tecla!= 's')&& (tecla!= 'n')){
            scanf ("%c", &tecla);
        }
    }
}