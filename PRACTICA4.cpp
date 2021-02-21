/**************************************
* NOMBRE: #Tanis13#
* PRIMER APELLIDO: #Kanan#
* SEGUNDO APELLIDO: #Halfelven#
* DNI: #00001101k#
* EMAIL: #Tanis13@krynn.com#
***************************************/

#include <stdio.h>
#include <string.h>

typedef char tipoChar20[21];
typedef struct pacientes //Variables de los datos de los pacientes
{
    tipoChar20 nombrePaciente;
    tipoChar20 apellidoPaciente;
    int distancia;
    int angulo;
};                          //Guarda los pacientes
typedef struct medicamentos //Variables de los datos de los medicamentos
{
    tipoChar20 nombreFarmaco;
    int PesoFarmaco;
    int pesoFarmaco;
    int unidadesFarmaco;
}; //Guarda los medicamentos

typedef medicamentos tdMedicamentos[21];

typedef struct pedidos //Variables de los datos de los pedidos
{
    int referenciaPaciente;
    int numerosEnvios;
    int numeroRepeticiones;
    int diaEnvio;
    int mesEnvio;
    int anioEnvio;
    int numeroFarmacosPedidos;
    tdMedicamentos listaMedicamentos;
}; //Aqui se guardaránlos pedidos

typedef struct repeticionPedidos //Variables de los datos de las repeticiones de los pedidos
{
    int referenciaPedidos;
    int referenciaPaciente;
    int diaEnvio;
    int mesEnvio;
    int anioEnvio;
    int numeroFarmacosPedidos;
    tdMedicamentos listaMedicamentos;
}; //Aqui se guardarán los pedidos repetidos

typedef pacientes tdPacientes[21]; //Generación de listados
tdPacientes listaPacientes;
typedef pedidos tdPedidos[21];
tdPedidos listaPedidos;
typedef repeticionPedidos tdRepeticionPedidos[101];
tdRepeticionPedidos listaPedidosRepetidos;

int contadorPacientesEnLista = 0; //Diferentes contadores
int contadorPedidos = 0;
int contadorFarmacos = 0;
int contadorPedidosRepetidos = 0;
char SoN = 's';

/**********************************************************
 * Fechas y calendarios                                   *
 *                                                        *
 * ********************************************************/
int mesSeleccionado, anioSeleccionado;
typedef char tipoDia[7][6];
tipoDia dia = {"LU  ", "MA  ", "MI  ", "JU  ", "VI ", " SA  ", "DO"};
typedef char tipoMes[12][11];
tipoMes mes = {"ENERO     ", "FEBRERO   ", "MARZO     ", "ABRIL     ", "MAYO      ", "JUNIO     ",
               "JULIO     ", "AGOSTO    ", "SEPTIEMBRE", "OCTUBRE   ", "NOVIEMBRE ", "DICIEMBRE "};

bool anioBisiesto() //Aquí se determina si el año introducido es bisiesto o no
{
    bool bisiesto;
    if (anioSeleccionado % 4 != 0)
    {
        bisiesto = false;
    }
    else if (anioSeleccionado % 4 == 0 && anioSeleccionado % 100 != 0)
    {
        bisiesto = true;
    }
    else if (anioSeleccionado % 4 == 0 && anioSeleccionado % 100 == 0 && anioSeleccionado % 400 == 0)
    {
        bisiesto = true;
    }
    else if (anioSeleccionado % 4 == 0 && anioSeleccionado % 100 == 0 && anioSeleccionado % 400 != 0)
    {
        bisiesto = false;
    }
    return bisiesto;
}

int calcularDiasMes(int elMes) //Esta función calcula el número de días que tiene el mes seleccionado del año seleccionado
{
    int diasMes;
    if (elMes == 1 || elMes == 3 || elMes == 5 || elMes == 7 || elMes == 8 || elMes == 10 || elMes == 12)
    {
        diasMes = 31;
    }
    if (elMes == 4 || elMes == 6 || elMes == 9 || elMes == 11)
    {
        diasMes = 30;
    }
    if (elMes == 2)
    {
        if (anioBisiesto() == true)
        {
            diasMes = 29;
        }
        if (anioBisiesto() == false)
        {
            diasMes = 28;
        }
    }

    return diasMes;
}

void sumarDias(int &dia, int &mes, int &anio, int periodoDia) //Suma los dias
{

    int resultado;
    bool cambioAnio;
    if (mes == 12)
    {
        cambioAnio = true;
    }

    resultado = dia + periodoDia;
    do
    {
        if (resultado > calcularDiasMes(mes))
        {
            dia = resultado - calcularDiasMes(mes);
            resultado = dia;
            if (mes == 12)
            {
                mes = 1;
            }
            else
            {
                mes++;
            }
        }
        else
        {
            dia = resultado;
            //resultado=dia;
        }
    } while (dia > calcularDiasMes(mes));

    if (cambioAnio == true && mes != 12)
    {
        anio++;
    }
}

int diaComienzaMes(int anio, int mes) //Calcula el días de la semana en el que empieza el mes elegido
{
    int a = (14 - mes) / 12;
    int y = anio - a;
    int m = mes + 12 * a - 2;
    int d = (0 + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
    return d;
}

/**********************************************************
 * Fin Fechas y calendarios                               *
 *                                                        *
 * ********************************************************/

void altaNuevoPaciente() //Alta de los datos del paciente

{

    do //Logica para meter mas pacientes o volver al menu principal
    {
        do
        {
            printf("\nAlta nuevo paciente:\n\n");
            printf("       Identificador (entre 1 y 20 caracteres)? ");
            scanf("%s%s", &listaPacientes[contadorPacientesEnLista].nombrePaciente, &listaPacientes[contadorPacientesEnLista].apellidoPaciente);
            if (strlen(listaPacientes[contadorPacientesEnLista].nombrePaciente) + strlen(listaPacientes[contadorPacientesEnLista].apellidoPaciente) > 20)
            {
                do
                {
                    printf("Los datos introducidos deben tener un tamaño maximo de 20 caracteres.\n");
                    printf("       Identificador (entre 1 y 20 caracteres)? ");
                    scanf("%s%s", &listaPacientes[contadorPacientesEnLista].nombrePaciente, &listaPacientes[contadorPacientesEnLista].apellidoPaciente);

                } while (strlen(listaPacientes[contadorPacientesEnLista].nombrePaciente) + strlen(listaPacientes[contadorPacientesEnLista].apellidoPaciente) > 20);
            }

            printf("       Distancia (hasta 10000 metros a plena carga)? ");
            scanf("%i", &listaPacientes[contadorPacientesEnLista].distancia);

            while (listaPacientes[contadorPacientesEnLista].distancia >= 11250 || listaPacientes[contadorPacientesEnLista].distancia < 0)
            {
                printf("       Distancia (hasta 10000 metros a plena carga)? ");
                scanf("%i", &listaPacientes[contadorPacientesEnLista].distancia);
            }

            printf("       Angulo (entre 0 y 2000 PI/1000 radianes)? ");
            scanf("%i", &listaPacientes[contadorPacientesEnLista].angulo);
            while (listaPacientes[contadorPacientesEnLista].angulo > 2000 || listaPacientes[contadorPacientesEnLista].angulo < 0)
            {
                printf("       Angulo (entre 0 y 2000 PI/1000 radianes)? ");
                scanf("%i", &listaPacientes[contadorPacientesEnLista].angulo);
            }
            printf("Datos correctos (S/N)? ");
            scanf("%s", &SoN);
        } while (SoN == 'N' || SoN == 'n');
        printf("Otro paciente (S/N)? ");

        scanf("%s", &SoN);

        contadorPacientesEnLista++;

    } while ((SoN == 'S' || SoN == 's') && contadorPacientesEnLista < 20);
}

void ubicarPacientes() //Imprime la lista de pacientes existente

{
    if (contadorPacientesEnLista == 0)
    {
        printf("\nNo existe ningun paciente en el registro.\n");
        printf("Pulse cualquier tecla para volver al menu principal. ");
        scanf("%s", &SoN);
    }
    else
    {
        printf("\nLista de pacientes y su ubicacion: ");
        printf("\n\n");
        printf("       Ref.   Identificador        Distancia       Angulo");
        printf("\n\n");
        for (int i = 0; i < contadorPacientesEnLista; i++)
        {
            printf("       %-7i", i + 1);
            printf("%s ", listaPacientes[i].nombrePaciente);
            printf("%-*s", (20 - (strlen(listaPacientes[i].nombrePaciente))), listaPacientes[i].apellidoPaciente);
            printf("%9i", listaPacientes[i].distancia);
            printf("%13i\n", listaPacientes[i].angulo);
        }
    }
}

void creacionPedidosRepetidos() //Genera las repeticiones de los pedidos introducidos
{
    int dia = listaPedidos[contadorPedidos].diaEnvio;
    int mes = listaPedidos[contadorPedidos].mesEnvio;
    int anio = listaPedidos[contadorPedidos].anioEnvio;
    int e = 1;
    if ((contadorPedidos + contadorPedidosRepetidos) < 100)
    {

        do
        {
            sumarDias(dia, mes, anio, listaPedidos[contadorPedidos].numeroRepeticiones);

            listaPedidosRepetidos[contadorPedidosRepetidos].referenciaPedidos = contadorPedidos;
            listaPedidosRepetidos[contadorPedidosRepetidos].referenciaPaciente = listaPedidos[contadorPedidos].referenciaPaciente;
            listaPedidosRepetidos[contadorPedidosRepetidos].diaEnvio = dia;
            listaPedidosRepetidos[contadorPedidosRepetidos].mesEnvio = mes;
            listaPedidosRepetidos[contadorPedidosRepetidos].anioEnvio = anio;
            listaPedidosRepetidos[contadorPedidosRepetidos].numeroFarmacosPedidos = listaPedidos[contadorPedidos].numeroFarmacosPedidos;

            for (int i = 0; i <= contadorFarmacos; i++)
            {

                strncpy(listaPedidosRepetidos[contadorPedidosRepetidos].listaMedicamentos[i].nombreFarmaco, listaPedidos[contadorPedidos].listaMedicamentos[i].nombreFarmaco, strlen(listaPedidos[contadorPedidos].listaMedicamentos[i].nombreFarmaco));
                listaPedidosRepetidos[contadorPedidosRepetidos].listaMedicamentos[i].pesoFarmaco = listaPedidos[contadorPedidos].listaMedicamentos[i].pesoFarmaco;
                listaPedidosRepetidos[contadorPedidosRepetidos].listaMedicamentos[i].unidadesFarmaco = listaPedidos[contadorPedidos].listaMedicamentos[i].unidadesFarmaco;
            }

            contadorPedidosRepetidos++;
            e++;
            if ((contadorPedidos + contadorPedidosRepetidos) >= 100)
            {
                printf("Numero maximo de pedidos alcanzado. (100 max.)\n");

                return;
            }
        } while (e < listaPedidos[contadorPedidos].numerosEnvios);
    }
    else
    {
        printf("Numero maximo de pedidos alcanzado. (100 max.)\n");
    }
}

void nuevoPedido() //Realiza los pedidos de los fármacos
{

    bool masEnvios = false;

    do
    {
        printf("\nNuevo pedido:");
        printf("\n\n");
        do
        {
            printf("      Ref. Paciente (entre 1 y 20): ");
            scanf("%i", &listaPedidos[contadorPedidos].referenciaPaciente);
            if (listaPedidos[contadorPedidos].referenciaPaciente > contadorPacientesEnLista)
            {
                printf("El paciente no existe. Prueba a introducir otro.\n");
            }
        } while (listaPedidos[contadorPedidos].referenciaPaciente > contadorPacientesEnLista);
        printf("      Numero de envios? ");
        scanf("%i", &listaPedidos[contadorPedidos].numerosEnvios);
        if (listaPedidos[contadorPedidos].numerosEnvios > 1)
        {
            do
            {

                printf("      Numero de dias entre cada envio? (Entre 1 y 15 dias) ");
                scanf("%i", &listaPedidos[contadorPedidos].numeroRepeticiones);
            } while (listaPedidos[contadorPedidos].numeroRepeticiones > 15);
            printf("      Dia del primer envio? ");
            scanf("%i", &listaPedidos[contadorPedidos].diaEnvio);
            printf("      Mes del primer envio? ");
            scanf("%i", &listaPedidos[contadorPedidos].mesEnvio);
            printf("      Anio del primer envio? ");
            scanf("%i", &listaPedidos[contadorPedidos].anioEnvio);
        }
        else
        {
            printf("      Dia del envio? ");
            scanf("%i", &listaPedidos[contadorPedidos].diaEnvio);
            printf("      Mes del envio? ");
            scanf("%i", &listaPedidos[contadorPedidos].mesEnvio);
            printf("      Anio del envio? ");
            scanf("%i", &listaPedidos[contadorPedidos].anioEnvio);
        }
        do
        {
            printf("      Nombre farmaco (Entre 1 y 20 caracteres)? ");
            scanf("%s", &listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].nombreFarmaco);
            do
            {
                printf("      Peso farmaco (menos de 3000 gramos)?");
                scanf("%i", &listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].pesoFarmaco);
            } while (listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].pesoFarmaco > 3000);
            do
            {
                printf("      Unidades de farmaco? ");
                scanf("%i", &listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].unidadesFarmaco);
                if ((listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].pesoFarmaco * listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].unidadesFarmaco) > 3000)
                {
                    printf("Peso maximo superado, prueba con menos unidades.\n");
                }
            } while ((listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].pesoFarmaco * listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].unidadesFarmaco) > 3000);
            printf("\b");

            printf("      Otro farmaco (S/N)? ");

            scanf("%s", &SoN);
            listaPedidos[contadorPedidos].numeroFarmacosPedidos = contadorFarmacos;
            contadorFarmacos++;

        } while ((SoN == 's' || SoN == 'S') && contadorFarmacos < 5);

        if (listaPedidos[contadorPedidos].numerosEnvios > 1)
        {
            creacionPedidosRepetidos();
        }
        if (contadorFarmacos >= 5)
        {
            printf("Numero maximo de farmacos por pedido alcanzado. (5 max.)\n");
        }
        contadorFarmacos = 0;

        printf("      Otro pedido (S/N)? ");
        scanf("%s", &SoN);
        contadorPedidos++;

    } while ((SoN == 's' || SoN == 'S') && (contadorPedidos + contadorPedidosRepetidos) < 100);
}

void listaDiariaPedidos() //Lista los pedidos en una fecha concreta
{
    int dia, mes, anio;
    int pesoTotal;
    int nPedidos = 1;

    printf("\nLista diaria de pedidos:");
    printf("\n\n");
    printf("Dia? ");
    scanf("%i", &dia);
    printf("Mes? ");
    scanf("%i", &mes);
    printf("Anio? ");
    scanf("%i", &anio);

    for (int i = 0; i <= contadorPedidos; i++)
    {
        if (anio == listaPedidos[i].anioEnvio)
        {
            if (mes == listaPedidos[i].mesEnvio)
            {
                if (dia == listaPedidos[i].diaEnvio)
                {
                    pesoTotal = 0;
                    printf("      Pedido %i\n", nPedidos);
                    nPedidos++;
                    printf("Ubicacion destino: Distancia: %i y Angulo: %i\n", listaPacientes[listaPedidos[i].referenciaPaciente - 1].distancia, listaPacientes[listaPedidos[i].referenciaPaciente - 1].angulo);
                    for (int j = 0; j <= listaPedidos[i].numeroFarmacosPedidos; j++)
                    {
                        printf("%2i Unidades         %-17s Peso: %4i gramos\n", listaPedidos[i].listaMedicamentos[j].unidadesFarmaco,
                               listaPedidos[i].listaMedicamentos[j].nombreFarmaco,
                               (listaPedidos[i].listaMedicamentos[j].pesoFarmaco * listaPedidos[i].listaMedicamentos[j].unidadesFarmaco));

                        pesoTotal = pesoTotal + (listaPedidos[i].listaMedicamentos[j].pesoFarmaco * listaPedidos[i].listaMedicamentos[j].unidadesFarmaco);
                    }

                    printf("                    Peso Total del envio: %6i gramos\n", pesoTotal);
                }
            }
        }
    }

    for (int i = 0; i <= contadorPedidosRepetidos; i++)
    {
        if (anio == listaPedidosRepetidos[i].anioEnvio)
        {
            if (mes == listaPedidosRepetidos[i].mesEnvio)
            {
                if (dia == listaPedidosRepetidos[i].diaEnvio)
                {
                    pesoTotal = 0;
                    printf("      Pedido %i\n", listaPedidosRepetidos[i].referenciaPedidos + 1);
                    printf("Ubicacion destino: Distancia: %i y Angulo: %i\n", listaPacientes[listaPedidosRepetidos[i].referenciaPaciente - 1].distancia, listaPacientes[listaPedidosRepetidos[i].referenciaPaciente - 1].angulo);
                    for (int j = 0; j <= listaPedidosRepetidos[i].numeroFarmacosPedidos; j++)
                    {
                        printf("%2i Unidades         %-17s Peso: %4i gramos\n", listaPedidosRepetidos[i].listaMedicamentos[j].unidadesFarmaco,
                               listaPedidosRepetidos[i].listaMedicamentos[j].nombreFarmaco,
                               listaPedidosRepetidos[i].listaMedicamentos[j].pesoFarmaco * listaPedidosRepetidos[i].listaMedicamentos[j].unidadesFarmaco);

                        pesoTotal = pesoTotal + (listaPedidosRepetidos[i].listaMedicamentos[j].pesoFarmaco * listaPedidosRepetidos[i].listaMedicamentos[j].unidadesFarmaco);
                    }

                    printf("                    Peso Total del envio: %6i gramos\n", pesoTotal);
                }
            }
        }
    }
}

void CalendarioMes() //Imprime en pantalla el mes elegido con los días que tienen pedidos
{
    int contador;
    bool existenPedidos;
    do
    {
        //Aquí piden los datos necesarios
        printf("\nMes (1..12)?");
        scanf("%i", &mesSeleccionado);
        printf("Anio (1610..3000)?");
        scanf("%i", &anioSeleccionado);
        printf("\n");

        if (anioSeleccionado >= 1601 && anioSeleccionado <= 3000 && mesSeleccionado >= 1 && mesSeleccionado <= 12)
        {
            //Aquí se imprime el encabezado del mes
            printf("%s", mes[mesSeleccionado - 1]);
            printf("             %i\n", anioSeleccionado);
            for (int i = 0; i < 27; i++)
            {
                printf("=");
            }
            printf("\n");
            for (int i = 0; i < 7; i++)
            {
                printf("%s", dia[i]);
                if (i == 4)
                {
                    printf("|");
                }
            }
            printf("\n");
            for (int i = 0; i < 27; i++)
            {
                printf("=");
            }
            printf("\n");

            contador = 1;
            for (int i = 0; i < (diaComienzaMes(anioSeleccionado, mesSeleccionado)); i++) //Imprime los puntos de inicio del mes
            {

                if (i == 4)
                {
                    printf(" . | ");
                }
                else
                {
                    printf(" .  ");
                }
                contador++;
            }
            existenPedidos = false;

            for (int j = 1; j <= calcularDiasMes(mesSeleccionado); j++) //Imprime los días del mes
            {
                for (int i = 0; i <= contadorPedidos; i++)
                {
                    if (anioSeleccionado == listaPedidos[i].anioEnvio)
                    {
                        if (mesSeleccionado == listaPedidos[i].mesEnvio)
                        {
                            if (j == listaPedidos[i].diaEnvio)
                            {
                                {
                                    existenPedidos = true;
                                }
                            }
                        }
                    }
                }

                for (int i = 0; i <= contadorPedidosRepetidos; i++)
                {
                    if (anioSeleccionado == listaPedidosRepetidos[i].anioEnvio)
                    {
                        if (mesSeleccionado == listaPedidosRepetidos[i].mesEnvio)
                        {
                            if (j == listaPedidosRepetidos[i].diaEnvio)
                            {
                                {
                                    existenPedidos = true;
                                }
                            }
                        }
                    }
                }

                if (existenPedidos == true)
                {
                    existenPedidos = true;
                    if (j < 10 && contador % 7 == 5)
                    {
                        printf(" %i | ", j);
                    }
                    if (j >= 10 && contador % 7 == 5)
                    {
                        printf("%i | ", j);
                    }
                    if (j < 10 && contador % 7 != 5)
                    {
                        printf(" %i  ", j);
                    }
                    if (j >= 10 && contador % 7 != 5)
                    {
                        printf("%i  ", j);
                    }
                    if (contador % 7 == 0)
                    {
                        printf("\n");
                    }
                    contador++;
                    existenPedidos = true;
                }

                else
                {
                    if (j < 10 && contador % 7 == 5)
                    {
                        printf("-- | ");
                    }
                    if (j >= 10 && contador % 7 == 5)
                    {
                        printf("-- | ");
                    }
                    if (j < 10 && contador % 7 != 5)
                    {
                        printf("--  ");
                    }
                    if (j >= 10 && contador % 7 != 5)
                    {
                        printf("--  ");
                    }
                    if (contador % 7 == 0)
                    {
                        printf("\n");
                    }
                    contador++;
                    existenPedidos = true;
                }
                existenPedidos = false;
            }

            while ((contador - 1) % 7 != 0) //imprime los puntos de final del mes
            {

                if (contador % 7 == 5)
                {
                    printf(" . | ");
                }
                else
                {
                    printf(" .  ");
                }
                contador++;
            }

            printf("\n");
            printf("\nMostrar otro mes (S/N)? ");
            scanf("%s", &SoN);
        }
    } while (SoN == 'S' || SoN == 's');
}

void pantallaInicio() //Imprime el menu de inicio de la aplicación
{

    char opcionElegida;

    do
    {
        do
        {
            printf("\nFarmaDron: Distribucion de Farmacos con Dron\n");
            printf("     Alta nuevo paciente                (Pulsar A)\n");
            printf("     Ubicar pacientes                   (Pulsar U)\n");
            printf("     Nuevo pedido                       (Pulsar N)\n");
            printf("     Lista diaria de pedidos            (Pulsar L)\n");
            printf("     Calendario mensual de pedidos      (Pulsar C)\n");
            printf("     Salir                              (Pulsar S)\n");
            printf("Teclear una opcion valida (A|U|N|L|C|S)?");

            scanf("%s", &opcionElegida);
        } while (opcionElegida != 'A' && opcionElegida != 'a' && opcionElegida != 'U' && opcionElegida != 'u' && opcionElegida != 'N' && opcionElegida != 'n' && opcionElegida != 'L' && opcionElegida != 'l' && opcionElegida != 'C' && opcionElegida != 'c' && opcionElegida != 'S' && opcionElegida != 's');

        if ((opcionElegida == 'A' || opcionElegida == 'a') && contadorPacientesEnLista < 20)
        {
            altaNuevoPaciente();
            pantallaInicio();
        }
        if ((opcionElegida == 'A' || opcionElegida == 'a') && contadorPacientesEnLista >= 20)
        {
            printf("Se ha alcanzado el maximo numero de pacientes. (20 max.)\n");
            pantallaInicio();
        }
        if (opcionElegida == 'U' || opcionElegida == 'u')
        {
            ubicarPacientes();
            pantallaInicio();
        }
        if ((opcionElegida == 'N' || opcionElegida == 'n') && (contadorPedidos + contadorPedidosRepetidos) < 100)
        {
            nuevoPedido();
            pantallaInicio();
        }
        if ((opcionElegida == 'N' || opcionElegida == 'n') && (contadorPedidos + contadorPedidosRepetidos) >= 100)
        {
            printf("Numero maximo de pedidos alcanzado. (100 max.)\n");
            pantallaInicio();
        }
        if (opcionElegida == 'L' || opcionElegida == 'l')
        {
            listaDiariaPedidos();
            pantallaInicio();
        }
        if (opcionElegida == 'C' || opcionElegida == 'c')
        {
            CalendarioMes();
            pantallaInicio();
        }

    } while (!opcionElegida == 'S' || !opcionElegida == 's');
}

int main()
{

    pantallaInicio();
}
