/**************************************
* NOMBRE: #Jose Luis#
* PRIMER APELLIDO: #Carrasco#
* SEGUNDO APELLIDO: #López#
* DNI: #75753442k#
* EMAIL: #jcarrasco216@alumno.uned.es#
***************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <graphics.h>

const float PI = 3.14159265358979323846;

typedef char tipoChar48[49];
typedef char tipoChar16[17];
typedef char tipoChar20[21];

typedef struct medicamentos //Variables de los datos de los medicamentos
{
    tipoChar20 nombreFarmaco;
    int PesoFarmaco;
    int pesoFarmaco;
    int unidadesFarmaco;
}; //Guarda los medicamentos

typedef medicamentos tdMedicamentos[21];
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

typedef repeticionPedidos tdRepeticionPedidos[100];
typedef struct pedidos //Variables de los datos de los pedidos
{
    int referenciaPedidos;
    int numerosEnvios;
    int numeroRepeticiones;
    int diaEnvio;
    int mesEnvio;
    int anioEnvio;
    int numeroFarmacosPedidos;
    tdMedicamentos listaMedicamentos;
    tdRepeticionPedidos listaRepeticionPedidos;
};

typedef pedidos tdPedidos[20];
typedef struct pacientes //Variables de los datos de los pacientes
{
    int referenciaPaciente;
    tipoChar20 identificadorPaciente;
    int distancia;
    int angulo;
    int numeroPedidosRealizados;
    int numeroPedidosRepetidosRealizados;
    tdPedidos listaPedidos;
};

typedef pacientes tdPacientes[20];
typedef struct almacenes //Variable de los datos de los almacenes

{
    int identificadorAlmacen;
    tipoChar48 direccionAlmacen;
    tipoChar48 municipioAlmacen;
    tipoChar16 provinciaAlmacen;
    tipoChar48 descripcionAlmacen;
    tdPacientes listaPacientes;
    int contadorPacientesEnAlmacen;
};
typedef struct rutaPedidos
{

    int referenciaPaciente;
    double distancia;
    double angulo;
    int pesoTotalPedido;
    double x;
    double y;
};

char SoN;
char restos;

typedef almacenes tdAlmacenes[10];
tdAlmacenes listaAlmacenes;
typedef rutaPedidos tdRutaPedidos[100];
tdRutaPedidos listaRutaPedidos;

int numeroAlmacenElegido;
int numeroPacienteElegido;

int contadorAlmacenes = 0;
int contadorPacientes = 0;
int contadorPedidos = 0;
int contadorFarmacos = 0;
int contadorPedidosRepetidos = 0;
int indiceRP;
typedef double tdDistancias[100][100];
tdDistancias distancias;
typedef int tdOrden[100][100];
tdOrden orden;
int acumuladoContadorPedidosAsignadosRuta = 0;
typedef int tdContadorRutasTrayectos[100][100];
tdContadorRutasTrayectos contadorRutasTrayectos;
int numeroDeRutas;

/*********************************************************
 * Fechas y calendarios                                  *
 *                                                       *
 * *******************************************************/
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

int diaComienzaMes(int anio, int mes) //Calcula el días de la semana en el que empieza el mes elegido
{
    int a = (14 - mes) / 12;
    int y = anio - a;
    int m = mes + 12 * a - 2;
    int d = (0 + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
    return d;
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
        }
    } while (dia > calcularDiasMes(mes));

    if (cambioAnio == true && mes != 12)
    {
        anio++;
    }
}

/**********************************************************
 * Fin Fechas y calendarios                               *
 *                                                        *
 * ********************************************************/

void altaAlmacen() //Gestiona el registro de almacenes
{
    do
    {

        printf("\nAlta nuevo almacen:\n\n");
        if (contadorAlmacenes >= 10)
        {
            printf("Registro de almacenes lleno. Que almacen desea borrar? ");
            scanf("%i", &numeroAlmacenElegido);
        }
        else
        {
            do
            {
                printf("Identificador almacen (cod. de almacen 1 a 10)? ");
                scanf("%i", &numeroAlmacenElegido);
                if ((listaAlmacenes[numeroAlmacenElegido - 1].identificadorAlmacen) != 0)
                {
                    printf("Registro de almacen ocupado. Elija otro.\n");
                }
            } while ((listaAlmacenes[numeroAlmacenElegido - 1].identificadorAlmacen) != 0);
        }

        scanf("%c", &restos);
        printf("       Direccion almacen? (entre 1 y 48 caracteres) ");
        scanf("%c", &restos);
        scanf("%[^\n]", &listaAlmacenes[numeroAlmacenElegido - 1].direccionAlmacen);
        printf("       Municipio almacen? (entre 1 y 48 caracteres) ");
        scanf("%c", &restos);
        scanf("%[^\n]", &listaAlmacenes[numeroAlmacenElegido - 1].municipioAlmacen);
        printf("       Provincia almacen? (entre 1 y 16 caracteres) ");
        scanf("%c", &restos);
        scanf("%[^\n]", &listaAlmacenes[numeroAlmacenElegido - 1].provinciaAlmacen);
        printf("       Descripcion almacen? (entre 1 y 48 caracteres) ");
        scanf("%c", &restos);
        scanf("%[^\n]", &listaAlmacenes[numeroAlmacenElegido - 1].descripcionAlmacen);
        printf("\nDatos correctos (S/N)? ");
        scanf("%c", &restos);
        scanf("%c", &SoN);
    } while (SoN == 'N' || SoN == 'n');
    listaAlmacenes[numeroAlmacenElegido - 1].identificadorAlmacen = numeroAlmacenElegido;
    contadorAlmacenes++;
}
void altaPacienteAlmacen() //Gestiona el registro de los pacientes según el almacén
{
    printf("\nAlta nuevo paciente:\n\n");

    printf("       Codigo almacen? (entre 1-10) ");
    scanf("%i", &numeroAlmacenElegido);
    numeroAlmacenElegido--;

    while (listaAlmacenes[numeroAlmacenElegido].identificadorAlmacen == 0)
    {
        printf("El almacen no existe en la base de datos, elija otro\n");
        printf("       Codigo almacen? (entre 1-10) ");
        scanf("%i", &numeroAlmacenElegido);
        numeroAlmacenElegido--;
    }

    do
    {
        do
        {

            printf("\nDatos paciente:\n");
            printf("       Identificador (entre 1 y 20 caracteres)? ");
            scanf("%c", &restos);
            scanf("%[^\n]", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].identificadorPaciente);

            if (strlen(listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].identificadorPaciente) >= 20)
            {
                do
                {
                    printf("Los datos introducidos deben tener un tamaño maximo de 20 caracteres.\n");
                    printf("       Identificador (entre 1 y 20 caracteres)? ");
                    scanf("%c", &restos);
                    scanf("%[^\n]", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].identificadorPaciente);

                } while (listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen >= 20);
            }

            printf("       Distancia (hasta 10000 metros a plena carga)? ");
            scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].distancia);

            while (listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].distancia >= 10000)
            {
                printf("       Distancia (hasta 10000 metros a plena carga)? ");
                scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].distancia);
            }
            if (listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].distancia < 0)
            {
                listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].distancia = listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].distancia * -1;
            }

            printf("       Angulo (entre 0 y 2000 PI/1000 radianes)? ");
            scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].angulo);
            while (listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].angulo > 2000 || listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].angulo < 0)
            {
                printf("       Angulo (entre 0 y 2000 PI/1000 radianes)? ");
                scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].angulo);
            }
            printf("Datos correctos (S/N)? ");
            scanf("%s", &SoN);
        } while (SoN == 'N' || SoN == 'n');
        listaAlmacenes[numeroAlmacenElegido].listaPacientes[listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen].referenciaPaciente = listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen + 1;
        printf("Otro Paciente mismo almacen (S/N)? ");

        scanf("%s", &SoN);

        listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen++;

    } while ((SoN == 'S' || SoN == 's') && listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen < 20);
}
void ubicarPacientes() //Imprime la lista de pacientes de un almacén determinado
{

    do
    {
        printf("\nLista de pacientes y su ubicacion: ");
        printf("\n\n");
        printf("Codigo almacen? ");
        scanf("%i", &numeroAlmacenElegido);
        printf("\n");
        if (numeroAlmacenElegido < 1 || numeroAlmacenElegido > 10)
        {
            printf("Los codigos de almacen deben ser entre 1 y 10\n");
        }

    } while (numeroAlmacenElegido < 1 || numeroAlmacenElegido > 10);

    if (listaAlmacenes[numeroAlmacenElegido - 1].contadorPacientesEnAlmacen == 0)
    {
        printf("\nNo existe pacientes registrados en este almacen.\n");
    }
    else
    {

        printf("       Ref.   Identificador        Distancia       Angulo");
        printf("\n\n");
        for (int i = 0; i < listaAlmacenes[numeroAlmacenElegido - 1].contadorPacientesEnAlmacen; i++)
        {
            printf("       %-7i", listaAlmacenes[numeroAlmacenElegido - 1].listaPacientes[i].referenciaPaciente);
            printf("%-21s", listaAlmacenes[numeroAlmacenElegido - 1].listaPacientes[i].identificadorPaciente);
            printf("%9i", listaAlmacenes[numeroAlmacenElegido - 1].listaPacientes[i].distancia);
            printf("%13i\n", listaAlmacenes[numeroAlmacenElegido - 1].listaPacientes[i].angulo);
        }
    }
}
void creacionPedidosRepetidos() //Genera las repeticiones de los pedidos introducidos
{

    int indice;
    int dia;
    int mes;
    int anio;
    contadorPedidosRepetidos = listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].numeroPedidosRepetidosRealizados;
    if ((contadorPedidos + contadorPedidosRepetidos) < 100)
    {
        dia = listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].diaEnvio;
        mes = listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].mesEnvio;
        anio = listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].anioEnvio;
        indice = 1;

        do
        {
            sumarDias(dia, mes, anio, listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numeroRepeticiones);

            listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaRepeticionPedidos[contadorPedidosRepetidos].diaEnvio = dia;
            listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaRepeticionPedidos[contadorPedidosRepetidos].mesEnvio = mes;
            listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaRepeticionPedidos[contadorPedidosRepetidos].anioEnvio = anio;
            listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaRepeticionPedidos[contadorPedidosRepetidos].numeroFarmacosPedidos = listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numeroFarmacosPedidos;

            for (int i = 0; i <= listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numeroFarmacosPedidos; i++)
            {

                strncpy(listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaRepeticionPedidos[contadorPedidosRepetidos].listaMedicamentos[i].nombreFarmaco, listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[i].nombreFarmaco,
                        strlen(listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[i].nombreFarmaco));
                listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaRepeticionPedidos[contadorPedidosRepetidos].listaMedicamentos[i].pesoFarmaco = listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[i].pesoFarmaco;
                listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaRepeticionPedidos[contadorPedidosRepetidos].listaMedicamentos[i].unidadesFarmaco = listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[i].unidadesFarmaco;
            }

            contadorPedidosRepetidos++;
            indice++;
            if ((contadorPedidos + contadorPedidosRepetidos) >= 100)
            {
                printf("Numero maximo de pedidos alcanzado. (100 max.)\n");
                return;
            }
        } while (indice < listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numerosEnvios);
    }
    else
    {
        printf("Numero maximo de pedidos alcanzado. (100 max.)\n");
    }
    listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].numeroPedidosRepetidosRealizados = contadorPedidosRepetidos;
}
void nuevoPedido() //Se registra el pedido de los clientes en los almacenes correspondientes
{
    bool masEnvios = false;

    printf("\nNuevo pedido:");
    printf("\n\n");

    printf("      Codigo almacen? ");
    scanf("%i", &numeroAlmacenElegido);
    numeroAlmacenElegido--;
    if ((listaAlmacenes[numeroAlmacenElegido].identificadorAlmacen) == 0 || listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen == 0)
    {
        printf("El almacen no existe o no tiene registrado ningun paciente\n");
    }
    else
    {
        do
        {
            printf("\n");
            do
            {
                printf("      Ref. Paciente (entre 1 y 20): ");
                scanf("%i", &numeroPacienteElegido);
                numeroPacienteElegido--;
                if (listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].referenciaPaciente == 0)
                {
                    printf("El paciente no existe. Prueba a introducir otro.\n");
                }
            } while (listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].referenciaPaciente == 0);

            contadorPedidos = listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].numeroPedidosRealizados;

            printf("      Numero de envios? ");
            scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numerosEnvios);
            if (listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numerosEnvios > 1)
            {
                do
                {

                    printf("      Numero de dias entre cada envio? (Entre 1 y 15 dias)? ");
                    scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numeroRepeticiones);
                } while (listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numeroRepeticiones > 15);
                printf("      Dia del primer envio? ");
                scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].diaEnvio);
                printf("      Mes del primer envio? ");
                scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].mesEnvio);
                printf("      Anio del primer envio? ");
                scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].anioEnvio);
            }
            else
            {
                printf("      Dia del envio? ");
                scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].diaEnvio);
                printf("      Mes del envio? ");
                scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].mesEnvio);
                printf("      Anio del envio? ");
                scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].anioEnvio);
            }
            do
            {
                printf("\n      Nombre farmaco (Entre 1 y 20 caracteres)? ");
                scanf("%s", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].nombreFarmaco);
                do
                {
                    printf("      Peso farmaco (menos de 3000 gramos)? ");
                    scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].pesoFarmaco);
                } while (listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].pesoFarmaco > 3000);
                do
                {
                    printf("      Unidades de farmaco? ");
                    scanf("%i", &listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].unidadesFarmaco);
                    if ((listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].pesoFarmaco * listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].unidadesFarmaco) > 3000)
                    {
                        printf("Peso maximo superado, prueba con menos unidades.\n");
                    }
                } while ((listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].pesoFarmaco * listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].listaMedicamentos[contadorFarmacos].unidadesFarmaco) > 3000);
                printf("\b");

                printf("\n      Otro farmaco (S/N)? ");

                scanf("%s", &SoN);
                listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numeroFarmacosPedidos = contadorFarmacos;
                contadorFarmacos++;

            } while ((SoN == 's' || SoN == 'S') && contadorFarmacos < 5);

            if (listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].numerosEnvios > 1)
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
            listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].listaPedidos[contadorPedidos].referenciaPedidos = contadorPedidos;
            listaAlmacenes[numeroAlmacenElegido].listaPacientes[numeroPacienteElegido].numeroPedidosRealizados = contadorPedidos;

        } while ((SoN == 's' || SoN == 'S') && (contadorPedidos + contadorPedidosRepetidos) < 100);
    }
}
void listaDiariaPedidos()
{
    int dia, mes, anio;
    int acumulado = 1;
    int pesoTotal;
    typedef char tdAMayusculas[49];
    tdAMayusculas aMayusculas;

    printf("\nLista diaria de pedidos:");
    printf("\n\n");
    printf("Codigo almacen? ");
    scanf("%i", &numeroAlmacenElegido);
    numeroAlmacenElegido = (numeroAlmacenElegido - 1);
    printf("\nDia? ");
    scanf("%i", &dia);
    printf("Mes? ");
    scanf("%i", &mes);
    printf("Anio? ");
    scanf("%i", &anio);
    pesoTotal = 0;

    for (int i = 0; i <= strlen(listaAlmacenes[numeroAlmacenElegido].descripcionAlmacen); i++)
    {
        aMayusculas[i] = toupper(listaAlmacenes[numeroAlmacenElegido].descripcionAlmacen[i]);
    }
    printf("Pedido ALMACEN - ");
    printf("%s", aMayusculas);

    for (int j = 0; j < listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen; j++)
    {
        for (int i = 0; i < listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].numeroPedidosRealizados; i++)
        {
            if (anio == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].anioEnvio)
            {
                if (mes == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].mesEnvio)
                {
                    if (dia == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].diaEnvio)
                    {

                        printf("\n      Pedido %i\n", acumulado);
                        printf("Ubicacion destino: Distancia: %i y Angulo: %i\n", listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].distancia, listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].angulo);
                        for (int k = 0; k <= listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].numeroFarmacosPedidos; k++)
                        {
                            printf("%2i Unidades         %-17s Peso: %4i gramos\n", listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaMedicamentos[k].unidadesFarmaco,
                                   listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaMedicamentos[k].nombreFarmaco,
                                   listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaMedicamentos[k].pesoFarmaco * listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaMedicamentos[k].unidadesFarmaco);

                            pesoTotal = (listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaMedicamentos[k].pesoFarmaco * listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaMedicamentos[k].unidadesFarmaco) + pesoTotal;
                        }

                        printf("                    Peso Total del envio: %6i gramos\n", pesoTotal);
                        acumulado++;
                        pesoTotal = 0;
                    }
                }
            }
        }
    }

    for (int j = 0; j < listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen; j++)
    {
        for (int i = 0; i < listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].numeroPedidosRealizados; i++)
        {
            for (int k = 0; k < listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].numeroPedidosRepetidosRealizados; k++)
            {
                if (anio == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].anioEnvio)
                {
                    if (mes == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].mesEnvio)
                    {
                        if (dia == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].diaEnvio)
                        {

                            printf("\n      Pedido %i\n", acumulado);
                            printf("Ubicacion destino: Distancia: %i y Angulo: %i\n", listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].distancia, listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].angulo);
                            for (int l = 0; l <= listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].numeroFarmacosPedidos; l++)
                            {
                                printf("%2i Unidades         %-17s Peso: %4i gramos\n", listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].listaMedicamentos[l].unidadesFarmaco,
                                       listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].listaMedicamentos[l].nombreFarmaco,
                                       listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].listaMedicamentos[l].pesoFarmaco * listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].listaMedicamentos[l].unidadesFarmaco);

                                pesoTotal = pesoTotal + (listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].listaMedicamentos[l].pesoFarmaco * listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].listaMedicamentos[l].unidadesFarmaco);
                            }

                            printf("                    Peso Total del envio: %6i gramos\n", pesoTotal);
                            acumulado++;
                            pesoTotal = 0;
                        }
                    }
                }
            }
        }
    }
}

/**********************************************************
 * Comienzo de codigo relacionado con el cálculo de rutas *
 **********************************************************/
void comprobarPedidosDelDia(int dia, int mes, int anio)
{

    for (int i = 0; i < indiceRP; i++) //Borro los datos que pudiera contener de un uso anterior.
    {
        listaRutaPedidos[i].referenciaPaciente = 0;
        listaRutaPedidos[i].distancia = 0;
        listaRutaPedidos[i].angulo = 0;
        listaRutaPedidos[i].pesoTotalPedido = 0;
        listaRutaPedidos[i].x = 0;
        listaRutaPedidos[i].y = 0;
    }
    indiceRP = 0;
    numeroAlmacenElegido = numeroAlmacenElegido - 1;

    for (int j = 0; j < listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen; j++)
    {
        for (int i = 0; i < listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].numeroPedidosRealizados; i++)
        {
            if (anio == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].anioEnvio)
            {
                if (mes == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].mesEnvio)
                {
                    if (dia == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].diaEnvio)
                    {

                        listaRutaPedidos[indiceRP].referenciaPaciente = listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].referenciaPaciente;
                        listaRutaPedidos[indiceRP].distancia = listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].distancia;
                        listaRutaPedidos[indiceRP].angulo = listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].angulo;
                        for (int k = 0; k <= listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].numeroFarmacosPedidos; k++)
                        {

                            listaRutaPedidos[indiceRP].pesoTotalPedido = listaRutaPedidos[indiceRP].pesoTotalPedido + (listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaMedicamentos[k].pesoFarmaco * listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaMedicamentos[k].unidadesFarmaco);
                        }

                        indiceRP++;
                    }
                }
            }
        }
    }

    for (int j = 0; j < listaAlmacenes[numeroAlmacenElegido].contadorPacientesEnAlmacen; j++)
    {
        for (int i = 0; i < listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].numeroPedidosRealizados; i++)
        {
            for (int k = 0; k < listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].numeroPedidosRepetidosRealizados; k++)
            {
                if (anio == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].anioEnvio)
                {
                    if (mes == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].mesEnvio)
                    {
                        if (dia == listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].diaEnvio)
                        {
                            listaRutaPedidos[indiceRP].referenciaPaciente = listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].referenciaPaciente;
                            listaRutaPedidos[indiceRP].distancia = listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].distancia;
                            listaRutaPedidos[indiceRP].angulo = listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].angulo;
                            for (int l = 0; l <= listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].numeroFarmacosPedidos; l++)
                            {
                                listaRutaPedidos[indiceRP].pesoTotalPedido = listaRutaPedidos[indiceRP].pesoTotalPedido + (listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].listaMedicamentos[l].pesoFarmaco * listaAlmacenes[numeroAlmacenElegido].listaPacientes[j].listaPedidos[i].listaRepeticionPedidos[k].listaMedicamentos[l].unidadesFarmaco);
                            }

                            indiceRP++;
                        }
                    }
                }
            }
        }
    }

    if (indiceRP == 0)
    {
        printf("No existen pedidos para ese dia.\n");
    }
}
void calcularDistanciaClientes()
{

    for (int i = 0; i < indiceRP; i++) //Calcula los valores de X e Y
    {
        listaRutaPedidos[i].y = (sin((listaRutaPedidos[i].angulo * 3.1416) / 1000.0)) * (listaRutaPedidos[i].distancia);
        listaRutaPedidos[i].x = (cos((listaRutaPedidos[i].angulo * 3.1416) / 1000.0)) * (listaRutaPedidos[i].distancia);
    }

    for (int i = 0; i < indiceRP; i++) //Crea una matriz con las distancias entre cualquier punto
    {
        for (int j = 0; j < indiceRP; j++)
        {
            distancias[i][j] = sqrt(pow((listaRutaPedidos[i].x - listaRutaPedidos[j].x), 2) + pow((listaRutaPedidos[i].y - listaRutaPedidos[j].y), 2));
        }
    }
}
void calculoMejorRuta()
{
    double elMenor;
    double distanciaAcumulada;
    int pesoAcumulado;
    int contadorPedidosAsignadosRuta;
    bool elementoUsado = false;

    //Para resetear el orden
    for (int i = 0; i <= numeroDeRutas; i++)
    {
        for (int j = 0; j < acumuladoContadorPedidosAsignadosRuta; j++)
        {
            orden[i][j] = 0;
            contadorRutasTrayectos[i][j] = 0;
            pesoAcumulado = 0;
        }
    }

    //Cálculo del primer envío desde el origen

    numeroDeRutas = 0;
    elMenor = listaRutaPedidos[0].distancia;
    distanciaAcumulada = 0;
    pesoAcumulado = 0;
    acumuladoContadorPedidosAsignadosRuta = 0;

    do
    {
        contadorPedidosAsignadosRuta = 1;
        for (int i = 0; i < indiceRP; i++)
        {
            elementoUsado = false;
            for (int j = 0; j <= numeroDeRutas; j++)
            {
                for (int k = 0; k < contadorRutasTrayectos[j][0]; k++)
                {
                    if (orden[j][k] == i)
                    {
                        elementoUsado = true;
                    }
                }
            }
            if (elementoUsado == false)
            {
                if (elMenor > listaRutaPedidos[i].distancia)
                {
                    elMenor = listaRutaPedidos[i].distancia;
                    orden[numeroDeRutas][0] = i;
                    pesoAcumulado = listaRutaPedidos[i].pesoTotalPedido;
                }
            }
        }
        contadorRutasTrayectos[numeroDeRutas][0]++;

        acumuladoContadorPedidosAsignadosRuta++;
        distanciaAcumulada = elMenor;
        //Cálculo de la ruta del resto de pedidos

        elMenor = 10001.0;

        for (int i = 0; i < indiceRP; i++)
        {

            for (int j = 0; j < indiceRP; j++)
            {
                elementoUsado = false;
                for (int k = 0; k <= numeroDeRutas; k++)
                {
                    for (int l = 0; l < contadorRutasTrayectos[k][0]; l++)
                    {
                        if (orden[k][l] == j) //Comprueba que no se haya utilizado antes
                        {
                            elementoUsado = true;
                        }
                    }
                }
                if (elementoUsado == false)
                {
                    if (elMenor >= distancias[i][j] && i != j)
                    {

                        distanciaAcumulada = distanciaAcumulada + distancias[i][j];
                        pesoAcumulado = pesoAcumulado + listaRutaPedidos[j].pesoTotalPedido;
                        if (distanciaAcumulada <= 20000 && (distanciaAcumulada + listaRutaPedidos[j].distancia) <= 25000 && pesoAcumulado <= 3000)
                        {
                            elMenor = distancias[i][j];
                            orden[numeroDeRutas][contadorPedidosAsignadosRuta] = j;
                            contadorPedidosAsignadosRuta++;
                            acumuladoContadorPedidosAsignadosRuta++;
                            contadorRutasTrayectos[numeroDeRutas][0]++;
                        }
                        else
                        {
                            distanciaAcumulada = distanciaAcumulada - distancias[i][j];
                            pesoAcumulado = pesoAcumulado - listaRutaPedidos[j].pesoTotalPedido;
                        }
                    }
                }
            }
            elMenor = 10001.0; //reseteamos al valor máximo permitido
        }
        distanciaAcumulada = 0; //reseteamos el valor
        pesoAcumulado = 0;
        numeroDeRutas++;

    } while (acumuladoContadorPedidosAsignadosRuta < indiceRP);
}

void representarRutasDiarias()
{
    int dia, mes, anio;
    int indice = 0;
    double distanciaAcumulada;
    double anguloEntreClientes;
    int pesoTotalRuta = 0;

    printf("Programar rutas diarias del dron:\n\n");
    printf("Codigo Almacen? ");
    scanf("%i", &numeroAlmacenElegido);
    printf("\nDia? ");
    scanf("%i", &dia);
    printf("Mes? ");
    scanf("%i", &mes);
    printf("Anio? ");
    scanf("%i", &anio);
    printf("\n");
    comprobarPedidosDelDia(dia, mes, anio);
    calcularDistanciaClientes();
    calculoMejorRuta();

    do
    {

        pesoTotalRuta = 0;
        distanciaAcumulada = 0;

        for (int j = 0; j < contadorRutasTrayectos[indice][0]; j++) //suma el peso total de la ruta
        {
            pesoTotalRuta = pesoTotalRuta + listaRutaPedidos[orden[indice][j]].pesoTotalPedido;
        }

        printf("      Ruta %i\n", (indice + 1));
        printf("Origen a Cliente %i", listaRutaPedidos[orden[indice][0]].referenciaPaciente);
        printf("    -- Distancia recorrida: %-4f", listaRutaPedidos[orden[indice][0]].distancia);
        printf(" Angulo: %-4f", listaRutaPedidos[orden[indice][0]].angulo);
        printf(" Peso: %5i gramos\n", pesoTotalRuta);
        distanciaAcumulada = distanciaAcumulada + listaRutaPedidos[orden[indice][0]].distancia;

        for (int j = 0; j <= contadorRutasTrayectos[indice][0] - 1; j++) //Escribe las rutas
        {
            if (j != contadorRutasTrayectos[indice][0] - 1)
            {
                printf("Cliente %i a Cliente %i", listaRutaPedidos[orden[indice][j]].referenciaPaciente, listaRutaPedidos[orden[indice][j + 1]].referenciaPaciente);
                printf(" -- Distancia recorrida: %-4f", distancias[orden[indice][j]][orden[indice][j + 1]]);
                distanciaAcumulada = distanciaAcumulada + distancias[orden[indice][j]][orden[indice][j + 1]];
                if ((listaRutaPedidos[orden[indice][j]].x - listaRutaPedidos[orden[indice][j + 1]].x) < 0)
                {
                    if (distancias[orden[indice][j]][orden[indice][j + 1]] == 0)
                    {
                        anguloEntreClientes = 0;
                    }
                    else
                    {
                        anguloEntreClientes = acos((((listaRutaPedidos[orden[indice][j]].x - listaRutaPedidos[orden[indice][j + 1]].x) / (distancias[orden[indice][j]][orden[indice][j + 1]])) * -1));
                    }
                }
                else
                {
                    if (distancias[orden[indice][j]][orden[indice][j + 1]] == 0)
                    {
                        anguloEntreClientes = 0;
                    }
                    else
                    {
                        anguloEntreClientes = acos(((listaRutaPedidos[orden[indice][j]].x - listaRutaPedidos[orden[indice][j + 1]].x) / (distancias[orden[indice][j]][orden[indice][j + 1]])));
                    }
                }
                printf(" Angulo: %-4f", ((anguloEntreClientes * 1000) / PI));
                pesoTotalRuta = pesoTotalRuta - listaRutaPedidos[orden[indice][j]].pesoTotalPedido;
                printf(" Peso: %5i gramos\n", pesoTotalRuta);
            }

            if (j == (contadorRutasTrayectos[indice][0] - 2))
            {
                printf("Cliente %i a Origen", listaRutaPedidos[orden[indice][j + 1]].referenciaPaciente);
                printf("    -- Distancia recorrida: %-4f", listaRutaPedidos[orden[indice][j + 1]].distancia);
                printf(" Angulo: %-4f", listaRutaPedidos[orden[indice][j + 1]].angulo);
                printf(" Peso: %5i gramos\n", 0);
                distanciaAcumulada = distanciaAcumulada + listaRutaPedidos[orden[indice][j + 1]].distancia;
                printf("Distancia total de la ruta: %f metros", distanciaAcumulada);
                printf("\n\n");
            }
        }

        if ((contadorRutasTrayectos[indice][0] == 1))
        {
            printf("Cliente %i a Origen", listaRutaPedidos[orden[indice][0]].referenciaPaciente);
            printf("    -- Distancia recorrida: %-4f", listaRutaPedidos[orden[indice][0]].distancia);
            printf(" Angulo: %-4f", listaRutaPedidos[orden[indice][0]].angulo);
            printf(" Peso: %5i gramos\n", 0);
            distanciaAcumulada = distanciaAcumulada + listaRutaPedidos[orden[indice][0]].distancia;
            printf("Distancia total de la ruta: %f metros", distanciaAcumulada);
            printf("\n\n");
        }

        indice++;

    } while (indice < (numeroDeRutas));
}

/**********************************************************
 * Fin de codigo relacionado con el cálculo de rutas      *
 **********************************************************/

/*********************************************************************
 * Inicio de codigo relacionado con la representación gráfica de rutas*
 **********************************************************************/

void programarRutasDiarias()
{
    int dia, mes, anio;
    int indice = 0;
    tipoChar16 converIntToChar;
    int rndNumR, rndNumG, rndNumB;
    rndNumB = rand() % 250;

    printf("Visualizacion de rutas diarias del dron:\n\n");
    printf("Codigo Almacen? ");
    scanf("%i", &numeroAlmacenElegido);
    printf("\nDia? ");
    scanf("%i", &dia);
    printf("Mes? ");
    scanf("%i", &mes);
    printf("Anio? ");
    scanf("%i", &anio);
    printf("\n");
    comprobarPedidosDelDia(dia, mes, anio);
    calcularDistanciaClientes();
    calculoMejorRuta();

    initwindow(1000, 1000, "RUTAS");

    moveto(50, 50);
    setcolor(WHITE);
    outtext("- RUTAS PLANIFICADAS PARA EL DRON");
    moveto(50, 70);
    outtext("- CADA RUTA APARECE EN UN COLOR DIFERENTE");
    moveto(50, 90);
    outtext("- EN CADA CIRCULO APARECE EL NUMERO DEL CLIENTE");

    setcolor(YELLOW);
    circle(500, 500, 10);
    moveto(506, 506);
    setcolor(LIGHTBLUE);
    outtext("ALMACEN");

    do
    {

        setcolor(RED);

        circle(((((listaRutaPedidos[orden[indice][0]].x) * 1000) / 20000) + 500), ((((listaRutaPedidos[orden[indice][0]].y) * 1000) / 20000) + 500), 10);

        rndNumR = rand() % 250;
        rndNumG = rand() % 250;
        rndNumB = rand() % 250;
        setcolor(COLOR(rndNumR, rndNumG, rndNumB));
        line(500, 500, ((((listaRutaPedidos[orden[indice][0]].x) * 1000) / 20000) + 500), ((((listaRutaPedidos[orden[indice][0]].y) * 1000) / 20000) + 500));

        sprintf(converIntToChar, "%d", listaRutaPedidos[orden[indice][0]].referenciaPaciente);
        outtextxy(((((listaRutaPedidos[orden[indice][0]].x) * 1000) / 20000) + 506), ((((listaRutaPedidos[orden[indice][0]].y) * 1000) / 20000) + 506), converIntToChar);

        for (int j = 0; j <= contadorRutasTrayectos[indice][0] - 1; j++) //Escribe las rutas
        {
            if (j != contadorRutasTrayectos[indice][0] - 1)
            {
                setcolor(RED);
                circle(((((listaRutaPedidos[orden[indice][j + 1]].x) * 1000) / 20000) + 500), ((((listaRutaPedidos[orden[indice][j + 1]].y) * 1000) / 20000) + 500), 10);
                setcolor(COLOR(rndNumR, rndNumG, rndNumB));
                line(((((listaRutaPedidos[orden[indice][j]].x) * 1000) / 20000) + 500), ((((listaRutaPedidos[orden[indice][j]].y) * 1000) / 20000) + 500), ((((listaRutaPedidos[orden[indice][j + 1]].x) * 1000) / 20000) + 500), ((((listaRutaPedidos[orden[indice][j + 1]].y) * 1000) / 20000) + 500));

                sprintf(converIntToChar, "%d", listaRutaPedidos[orden[indice][j + 1]].referenciaPaciente);
                outtextxy(((((listaRutaPedidos[orden[indice][j + 1]].x) * 1000) / 20000) + 506), ((((listaRutaPedidos[orden[indice][j + 1]].y) * 1000) / 20000) + 506), converIntToChar);
            }

            if (j == (contadorRutasTrayectos[indice][0] - 2))
            {
                setcolor(RED);
                circle(((((listaRutaPedidos[orden[indice][j + 1]].x) * 1000) / 20000) + 500), ((((listaRutaPedidos[orden[indice][j + 1]].y) * 1000) / 20000) + 500), 10);
                setcolor(COLOR(rndNumR, rndNumG, rndNumB));
                line(((((listaRutaPedidos[orden[indice][j + 1]].x) * 1000) / 20000) + 500), ((((listaRutaPedidos[orden[indice][j + 1]].y) * 1000) / 20000) + 500), 500, 500);
                sprintf(converIntToChar, "%d", listaRutaPedidos[orden[indice][j + 1]].referenciaPaciente);
                outtextxy(((((listaRutaPedidos[orden[indice][j + 1]].x) * 1000) / 20000) + 506), ((((listaRutaPedidos[orden[indice][j + 1]].y) * 1000) / 20000) + 506), converIntToChar);
            }
        }

        indice++;

    } while (indice < (numeroDeRutas));

    getch();
    closegraph();
}

/*********************************************************************
 * Fin de codigo relacionado con la representación gráfica de rutas   *
 *********************************************************************/

void iniciarGestion() //Añade los registros por defecto
{
    printf("\n");
    //Datos de almacenes por defecto
    printf("ListadoGestion FarmaDron\n\n\n");
    listaAlmacenes[0].identificadorAlmacen = 1;
    printf("      Almacen %i", listaAlmacenes[0].identificadorAlmacen);
    printf(" - %s", strncpy(listaAlmacenes[0].direccionAlmacen, "Calle Valverde, 25", 49));
    printf(" - %s", strncpy(listaAlmacenes[0].municipioAlmacen, "Cadiz", 49));
    printf(" - %s\n", strncpy(listaAlmacenes[0].provinciaAlmacen, "Cadiz", 49));
    printf("      Descripcion: %s", strncpy(listaAlmacenes[0].descripcionAlmacen, "Poligono Fadricas", 49));

    printf("\n\n      Clientes\n\n");

    printf("       Ref.   Identificador        Distancia       Angulo\n\n");
    listaAlmacenes[0].listaPacientes[0].referenciaPaciente = 1;
    printf("       %-7i", listaAlmacenes[0].listaPacientes[0].referenciaPaciente);
    printf("%-s          ", strncpy(listaAlmacenes[0].listaPacientes[0].identificadorPaciente, "Juan Sanchez", 21));
    listaAlmacenes[0].listaPacientes[0].distancia = 3850;
    printf("%-9i", listaAlmacenes[0].listaPacientes[0].distancia);
    listaAlmacenes[0].listaPacientes[0].angulo = 175;
    printf("%9i\n", listaAlmacenes[0].listaPacientes[0].angulo);

    listaAlmacenes[0].listaPacientes[1].referenciaPaciente = 2;
    printf("       %-7i", listaAlmacenes[0].listaPacientes[1].referenciaPaciente);
    printf("%-s           ", strncpy(listaAlmacenes[0].listaPacientes[1].identificadorPaciente, "Pablo Lopez", 21));
    listaAlmacenes[0].listaPacientes[1].distancia = 7500;
    printf("%-8i", listaAlmacenes[0].listaPacientes[1].distancia);
    listaAlmacenes[0].listaPacientes[1].angulo = 325;
    printf("%10i\n", listaAlmacenes[0].listaPacientes[1].angulo);

    listaAlmacenes[0].listaPacientes[2].referenciaPaciente = 3;
    printf("       %-7i", listaAlmacenes[0].listaPacientes[2].referenciaPaciente);
    printf("%-s       ", strncpy(listaAlmacenes[0].listaPacientes[2].identificadorPaciente, "Lucia Hernandez", 21));
    listaAlmacenes[0].listaPacientes[2].distancia = 9564;
    printf("%-9i", listaAlmacenes[0].listaPacientes[2].distancia);
    listaAlmacenes[0].listaPacientes[2].angulo = 1026;
    printf("%10i\n", listaAlmacenes[0].listaPacientes[2].angulo);

    listaAlmacenes[0].listaPacientes[3].referenciaPaciente = 4;
    printf("       %-7i", listaAlmacenes[0].listaPacientes[3].referenciaPaciente);
    printf("%-s           ", strncpy(listaAlmacenes[0].listaPacientes[3].identificadorPaciente, "Pedro Ortiz", 21));
    listaAlmacenes[0].listaPacientes[3].distancia = 1800;
    printf("%-9i", listaAlmacenes[0].listaPacientes[3].distancia);
    listaAlmacenes[0].listaPacientes[3].angulo = 1600;
    printf("%10i\n", listaAlmacenes[0].listaPacientes[3].angulo);

    listaAlmacenes[0].contadorPacientesEnAlmacen = 4;

    printf("\n      Pedidos\n\n");

    printf("   Cliente   Fecha       Farmaco            Peso    Unidades\n\n");

    listaAlmacenes[0].listaPacientes[0].listaPedidos[0].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[0].listaPacientes[0].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[0].listaPacientes[0].listaPedidos[0].diaEnvio = 24;
    printf("%i", listaAlmacenes[0].listaPacientes[0].listaPedidos[0].diaEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[0].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[0].listaPacientes[0].listaPedidos[0].mesEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[0].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[0].listaPacientes[0].listaPedidos[0].anioEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[0].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Antalgin", 21));
    listaAlmacenes[0].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 150;
    printf(" %-10i", listaAlmacenes[0].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 4;
    printf("%-i\n", listaAlmacenes[0].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[0].listaPacientes[0].listaPedidos[1].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[0].listaPacientes[0].listaPedidos[1].referenciaPedidos);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[1].numerosEnvios = 1;
    listaAlmacenes[0].listaPacientes[0].listaPedidos[1].diaEnvio = 27;
    printf("%i", listaAlmacenes[0].listaPacientes[0].listaPedidos[1].diaEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[1].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[0].listaPacientes[0].listaPedidos[1].mesEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[1].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[0].listaPacientes[0].listaPedidos[1].anioEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[1].numeroFarmacosPedidos = 0;
    printf("%s            ", strncpy(listaAlmacenes[0].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].nombreFarmaco, "Nolotil", 21));
    listaAlmacenes[0].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].pesoFarmaco = 350;
    printf(" %-10i", listaAlmacenes[0].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco = 2;
    printf("%-i\n", listaAlmacenes[0].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[0].listaPacientes[2].listaPedidos[0].referenciaPedidos = 3;
    printf("    %-9i", listaAlmacenes[0].listaPacientes[2].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[0].listaPacientes[2].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[0].listaPacientes[2].listaPedidos[0].diaEnvio = 27;
    printf("%i", listaAlmacenes[0].listaPacientes[2].listaPedidos[0].diaEnvio);
    listaAlmacenes[0].listaPacientes[2].listaPedidos[0].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[0].listaPacientes[2].listaPedidos[0].mesEnvio);
    listaAlmacenes[0].listaPacientes[2].listaPedidos[0].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[0].listaPacientes[2].listaPedidos[0].anioEnvio);
    listaAlmacenes[0].listaPacientes[2].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[0].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Enamtyum", 21));
    listaAlmacenes[0].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 200;
    printf(" %-10i", listaAlmacenes[0].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[0].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 4;
    printf("%-i\n", listaAlmacenes[0].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[0].listaPacientes[3].listaPedidos[0].referenciaPedidos = 4;
    printf("    %-9i", listaAlmacenes[0].listaPacientes[3].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[0].listaPacientes[3].listaPedidos[0].diaEnvio = 27;
    printf("%i", listaAlmacenes[0].listaPacientes[3].listaPedidos[0].diaEnvio);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[0].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[0].listaPacientes[3].listaPedidos[0].mesEnvio);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[0].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[0].listaPacientes[3].listaPedidos[0].anioEnvio);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s              ", strncpy(listaAlmacenes[0].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Suero", 21));
    listaAlmacenes[0].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 150;
    printf(" %-10i", listaAlmacenes[0].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 2;
    printf("%-i\n", listaAlmacenes[0].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[0].listaPacientes[3].listaPedidos[1].referenciaPedidos = 4;
    printf("    %-9i", listaAlmacenes[0].listaPacientes[3].listaPedidos[1].referenciaPedidos);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[1].numerosEnvios = 1;
    listaAlmacenes[0].listaPacientes[3].listaPedidos[1].diaEnvio = 2;
    printf("%i", listaAlmacenes[0].listaPacientes[3].listaPedidos[1].diaEnvio);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[1].mesEnvio = 6;
    printf("/%i/", listaAlmacenes[0].listaPacientes[3].listaPedidos[1].mesEnvio);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[1].anioEnvio = 2021;
    printf("%-7i", listaAlmacenes[0].listaPacientes[3].listaPedidos[1].anioEnvio);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[1].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[0].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].nombreFarmaco, "Betadine", 21));
    listaAlmacenes[0].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].pesoFarmaco = 50;
    printf(" %-10i", listaAlmacenes[0].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[0].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco = 5;
    printf("%-i\n", listaAlmacenes[0].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[0].listaPacientes[1].listaPedidos[0].referenciaPedidos = 2;
    printf("    %-9i", listaAlmacenes[0].listaPacientes[1].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[0].listaPacientes[1].listaPedidos[0].diaEnvio = 2;
    printf("%i", listaAlmacenes[0].listaPacientes[1].listaPedidos[0].diaEnvio);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[0].mesEnvio = 6;
    printf("/%i/", listaAlmacenes[0].listaPacientes[1].listaPedidos[0].mesEnvio);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[0].anioEnvio = 2021;
    printf("%-7i", listaAlmacenes[0].listaPacientes[1].listaPedidos[0].anioEnvio);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[0].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Apiretal", 21));
    listaAlmacenes[0].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 100;
    printf(" %-10i", listaAlmacenes[0].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 3;
    printf("%-i\n", listaAlmacenes[0].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[0].listaPacientes[0].listaPedidos[2].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[0].listaPacientes[0].listaPedidos[2].referenciaPedidos);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[2].numerosEnvios = 1;
    listaAlmacenes[0].listaPacientes[0].listaPedidos[2].diaEnvio = 24;
    printf("%i", listaAlmacenes[0].listaPacientes[0].listaPedidos[2].diaEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[2].mesEnvio = 7;
    printf("/%i/", listaAlmacenes[0].listaPacientes[0].listaPedidos[2].mesEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[2].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[0].listaPacientes[0].listaPedidos[2].anioEnvio);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[2].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[0].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].nombreFarmaco, "Erictyum", 21));
    listaAlmacenes[0].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].pesoFarmaco = 250;
    printf(" %-10i", listaAlmacenes[0].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[0].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].unidadesFarmaco = 5;
    printf("%-i\n", listaAlmacenes[0].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[0].listaPacientes[1].listaPedidos[3].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[0].listaPacientes[1].listaPedidos[3].referenciaPedidos);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[3].numerosEnvios = 1;
    listaAlmacenes[0].listaPacientes[1].listaPedidos[3].diaEnvio = 24;
    printf("%i", listaAlmacenes[0].listaPacientes[1].listaPedidos[3].diaEnvio);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[3].mesEnvio = 8;
    printf("/%i/", listaAlmacenes[0].listaPacientes[1].listaPedidos[3].mesEnvio);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[3].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[0].listaPacientes[1].listaPedidos[3].anioEnvio);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[3].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[0].listaPacientes[1].listaPedidos[3].listaMedicamentos[0].nombreFarmaco, "Danilgin", 21));
    listaAlmacenes[0].listaPacientes[1].listaPedidos[3].listaMedicamentos[0].pesoFarmaco = 350;
    printf(" %-10i", listaAlmacenes[0].listaPacientes[1].listaPedidos[3].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[0].listaPacientes[1].listaPedidos[3].listaMedicamentos[0].unidadesFarmaco = 3;
    printf("%-i\n", listaAlmacenes[0].listaPacientes[1].listaPedidos[3].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[0].listaPacientes[0].numeroPedidosRealizados = 4;
    listaAlmacenes[0].listaPacientes[2].numeroPedidosRealizados = 1;
    listaAlmacenes[0].listaPacientes[3].numeroPedidosRealizados = 2;
    listaAlmacenes[0].listaPacientes[1].numeroPedidosRealizados = 1;

    listaAlmacenes[1].identificadorAlmacen = 2;
    printf("\n      Almacen %i", listaAlmacenes[1].identificadorAlmacen);
    printf(" - %s", strncpy(listaAlmacenes[1].direccionAlmacen, "Calle Guadalquivir, 25", 49));
    printf(" - %s", strncpy(listaAlmacenes[1].municipioAlmacen, "Bornos", 49));
    printf(" - %s\n", strncpy(listaAlmacenes[1].provinciaAlmacen, "Cadiz", 49));
    printf("      Descripcion: %s", strncpy(listaAlmacenes[1].descripcionAlmacen, "Barriada de la Paz", 49));

    listaAlmacenes[4].identificadorAlmacen = 5;
    printf("\n\n      Almacen %i", listaAlmacenes[4].identificadorAlmacen);
    printf(" - %s", strncpy(listaAlmacenes[4].direccionAlmacen, "Avenida Ana de Viya, 86", 49));
    printf(" - %s", strncpy(listaAlmacenes[4].municipioAlmacen, "Alcala de los Gazules", 49));
    printf(" - %s\n", strncpy(listaAlmacenes[4].provinciaAlmacen, "Cadiz", 49));
    printf("      Descripcion: %s", strncpy(listaAlmacenes[4].descripcionAlmacen, "Zona Franca", 49));

    printf("\n\n      Clientes\n\n");

    printf("       Ref.   Identificador        Distancia       Angulo\n\n");
    listaAlmacenes[4].listaPacientes[0].referenciaPaciente = 1;
    printf("       %-7i", listaAlmacenes[4].listaPacientes[0].referenciaPaciente);
    printf("%-s   ", strncpy(listaAlmacenes[4].listaPacientes[0].identificadorPaciente, "Jose Luis Gutierrez", 21));
    listaAlmacenes[4].listaPacientes[0].distancia = 8400;
    printf("%-9i", listaAlmacenes[4].listaPacientes[0].distancia);
    listaAlmacenes[4].listaPacientes[0].angulo = 900;
    printf("%10i\n", listaAlmacenes[4].listaPacientes[0].angulo);

    listaAlmacenes[4].listaPacientes[1].referenciaPaciente = 2;
    printf("       %-7i", listaAlmacenes[4].listaPacientes[1].referenciaPaciente);
    printf("%-s       ", strncpy(listaAlmacenes[4].listaPacientes[1].identificadorPaciente, "Antonio Ramirez", 21));
    listaAlmacenes[4].listaPacientes[1].distancia = 2430;
    printf("%-9i", listaAlmacenes[4].listaPacientes[1].distancia);
    listaAlmacenes[4].listaPacientes[1].angulo = 450;
    printf("%10i\n", listaAlmacenes[4].listaPacientes[1].angulo);

    listaAlmacenes[4].listaPacientes[2].referenciaPaciente = 3;
    printf("       %-7i", listaAlmacenes[4].listaPacientes[2].referenciaPaciente);
    printf("%-s          ", strncpy(listaAlmacenes[4].listaPacientes[2].identificadorPaciente, "Jorge Garcia", 21));
    listaAlmacenes[4].listaPacientes[2].distancia = 3050;
    printf("%-9i", listaAlmacenes[4].listaPacientes[2].distancia);
    listaAlmacenes[4].listaPacientes[2].angulo = 1340;
    printf("%10i\n", listaAlmacenes[4].listaPacientes[2].angulo);

    listaAlmacenes[4].contadorPacientesEnAlmacen = 3;

    printf("\n      Pedidos\n\n");

    printf("   Cliente   Fecha       Farmaco           Peso    Unidades\n\n");

    listaAlmacenes[4].listaPacientes[0].listaPedidos[0].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[4].listaPacientes[0].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[4].listaPacientes[0].listaPedidos[0].diaEnvio = 4;
    printf("%i", listaAlmacenes[4].listaPacientes[0].listaPedidos[0].diaEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[0].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[4].listaPacientes[0].listaPedidos[0].mesEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[0].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[4].listaPacientes[0].listaPedidos[0].anioEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[4].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Ventolin", 21));
    listaAlmacenes[4].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 40;
    printf(" %-10i", listaAlmacenes[4].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 9;
    printf("%-i\n", listaAlmacenes[4].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[4].listaPacientes[0].listaPedidos[1].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[4].listaPacientes[0].listaPedidos[1].referenciaPedidos);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[1].numerosEnvios = 1;
    listaAlmacenes[4].listaPacientes[0].listaPedidos[1].diaEnvio = 7;
    printf("%i", listaAlmacenes[4].listaPacientes[0].listaPedidos[1].diaEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[1].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[4].listaPacientes[0].listaPedidos[1].mesEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[1].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[4].listaPacientes[0].listaPedidos[1].anioEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[1].numeroFarmacosPedidos = 0;
    printf("%s              ", strncpy(listaAlmacenes[4].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].nombreFarmaco, "Adiro", 21));
    listaAlmacenes[4].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].pesoFarmaco = 90;
    printf(" %-10i", listaAlmacenes[4].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco = 2;
    printf("%-i\n", listaAlmacenes[4].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[4].listaPacientes[1].listaPedidos[0].referenciaPedidos = 2;
    printf("    %-9i", listaAlmacenes[4].listaPacientes[1].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[4].listaPacientes[1].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[4].listaPacientes[1].listaPedidos[0].diaEnvio = 8;
    printf("%i", listaAlmacenes[4].listaPacientes[1].listaPedidos[0].diaEnvio);
    listaAlmacenes[4].listaPacientes[1].listaPedidos[0].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[4].listaPacientes[1].listaPedidos[0].mesEnvio);
    listaAlmacenes[4].listaPacientes[1].listaPedidos[0].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[4].listaPacientes[1].listaPedidos[0].anioEnvio);
    listaAlmacenes[4].listaPacientes[1].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s        ", strncpy(listaAlmacenes[4].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Paracetamol", 21));
    listaAlmacenes[4].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 190;
    printf(" %-10i", listaAlmacenes[4].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[4].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 3;
    printf("%-i\n", listaAlmacenes[4].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[4].listaPacientes[2].listaPedidos[0].referenciaPedidos = 3;
    printf("    %-9i", listaAlmacenes[4].listaPacientes[2].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[4].listaPacientes[2].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[4].listaPacientes[2].listaPedidos[0].diaEnvio = 8;
    printf("%i", listaAlmacenes[4].listaPacientes[2].listaPedidos[0].diaEnvio);
    listaAlmacenes[4].listaPacientes[2].listaPedidos[0].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[4].listaPacientes[2].listaPedidos[0].mesEnvio);
    listaAlmacenes[4].listaPacientes[2].listaPedidos[0].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[4].listaPacientes[2].listaPedidos[0].anioEnvio);
    listaAlmacenes[4].listaPacientes[2].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s            ", strncpy(listaAlmacenes[4].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Sintrom", 21));
    listaAlmacenes[4].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 390;
    printf(" %-10i", listaAlmacenes[4].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[4].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 3;
    printf("%-i\n", listaAlmacenes[4].listaPacientes[2].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[4].listaPacientes[0].listaPedidos[2].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[4].listaPacientes[0].listaPedidos[2].referenciaPedidos);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[2].numerosEnvios = 1;
    listaAlmacenes[4].listaPacientes[0].listaPedidos[2].diaEnvio = 1;
    printf("%i", listaAlmacenes[4].listaPacientes[0].listaPedidos[2].diaEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[2].mesEnvio = 6;
    printf("/%i/", listaAlmacenes[4].listaPacientes[0].listaPedidos[2].mesEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[2].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[4].listaPacientes[0].listaPedidos[2].anioEnvio);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[2].numeroFarmacosPedidos = 0;
    printf("%s            ", strncpy(listaAlmacenes[4].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].nombreFarmaco, "Eutirox", 21));
    listaAlmacenes[4].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].pesoFarmaco = 140;
    printf(" %-10i", listaAlmacenes[4].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[4].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].unidadesFarmaco = 1;
    printf("%-i\n", listaAlmacenes[4].listaPacientes[0].listaPedidos[2].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[4].listaPacientes[0].numeroPedidosRealizados = 3;
    listaAlmacenes[4].listaPacientes[1].numeroPedidosRealizados = 1;
    listaAlmacenes[4].listaPacientes[2].numeroPedidosRealizados = 1;

    listaAlmacenes[6].identificadorAlmacen = 7;
    printf("\n      Almacen %i", listaAlmacenes[6].identificadorAlmacen);
    printf(" - %s", strncpy(listaAlmacenes[6].direccionAlmacen, "Avenida Juan de Dios, 137", 49));
    printf(" - %s", strncpy(listaAlmacenes[6].municipioAlmacen, "Grazalema", 49));
    printf(" - %s\n", strncpy(listaAlmacenes[6].provinciaAlmacen, "Cadiz", 49));
    printf("      Descripcion: %s", strncpy(listaAlmacenes[6].descripcionAlmacen, "Plaza del reloj", 49));

    listaAlmacenes[8].identificadorAlmacen = 9;
    printf("\n\n      Almacen %i", listaAlmacenes[8].identificadorAlmacen);
    printf(" - %s", strncpy(listaAlmacenes[8].direccionAlmacen, "Calle Valero, 4", 49));
    printf(" - %s", strncpy(listaAlmacenes[8].municipioAlmacen, "Algeciras", 49));
    printf(" - %s\n", strncpy(listaAlmacenes[8].provinciaAlmacen, "Cadiz", 49));
    printf("      Descripcion: %s", strncpy(listaAlmacenes[8].descripcionAlmacen, "El Zabal", 49));

    contadorAlmacenes = 5;

    printf("\n\n      Clientes\n\n");

    printf("       Ref.   Identificador        Distancia       Angulo\n\n");
    listaAlmacenes[8].listaPacientes[0].referenciaPaciente = 1;
    printf("       %-7i", listaAlmacenes[8].listaPacientes[0].referenciaPaciente);
    printf("%-s     ", strncpy(listaAlmacenes[8].listaPacientes[0].identificadorPaciente, "Cristina Martinez", 21));
    listaAlmacenes[8].listaPacientes[0].distancia = 5000;
    printf("%-9i", listaAlmacenes[8].listaPacientes[0].distancia);
    listaAlmacenes[8].listaPacientes[0].angulo = 1520;
    printf("%10i\n", listaAlmacenes[8].listaPacientes[0].angulo);

    listaAlmacenes[8].listaPacientes[1].referenciaPaciente = 2;
    printf("       %-7i", listaAlmacenes[8].listaPacientes[1].referenciaPaciente);
    printf("%-s         ", strncpy(listaAlmacenes[8].listaPacientes[1].identificadorPaciente, "Alberto Ruiz ", 21));
    listaAlmacenes[8].listaPacientes[1].distancia = 3000;
    printf("%-9i", listaAlmacenes[8].listaPacientes[1].distancia);
    listaAlmacenes[8].listaPacientes[1].angulo = 1420;
    printf("%10i\n", listaAlmacenes[8].listaPacientes[1].angulo);

    listaAlmacenes[8].listaPacientes[2].referenciaPaciente = 3;
    printf("       %-7i", listaAlmacenes[8].listaPacientes[2].referenciaPaciente);
    printf("%-s          ", strncpy(listaAlmacenes[8].listaPacientes[2].identificadorPaciente, "Ivan Navarro", 21));
    listaAlmacenes[8].listaPacientes[2].distancia = 3500;
    printf("%-9i", listaAlmacenes[8].listaPacientes[2].distancia);
    listaAlmacenes[8].listaPacientes[2].angulo = 1540;
    printf("%10i\n", listaAlmacenes[8].listaPacientes[2].angulo);

    listaAlmacenes[8].listaPacientes[3].referenciaPaciente = 4;
    printf("       %-7i", listaAlmacenes[8].listaPacientes[3].referenciaPaciente);
    printf("%-s          ", strncpy(listaAlmacenes[8].listaPacientes[3].identificadorPaciente, "Elena Torres", 21));
    listaAlmacenes[8].listaPacientes[3].distancia = 7500;
    printf("%-9i", listaAlmacenes[8].listaPacientes[3].distancia);
    listaAlmacenes[8].listaPacientes[3].angulo = 550;
    printf("%10i\n", listaAlmacenes[8].listaPacientes[3].angulo);

    listaAlmacenes[8].listaPacientes[4].referenciaPaciente = 5;
    printf("       %-7i", listaAlmacenes[8].listaPacientes[4].referenciaPaciente);
    printf("%-s          ", strncpy(listaAlmacenes[8].listaPacientes[4].identificadorPaciente, "Julia Castro", 21));
    listaAlmacenes[8].listaPacientes[4].distancia = 4020;
    printf("%-9i", listaAlmacenes[8].listaPacientes[4].distancia);
    listaAlmacenes[8].listaPacientes[4].angulo = 350;
    printf("%10i\n", listaAlmacenes[8].listaPacientes[4].angulo);

    listaAlmacenes[8].contadorPacientesEnAlmacen = 5;

    //Inicialización de pedidos

    printf("\n      Pedidos\n\n");

    printf("   Cliente   Fecha       Farmaco            Peso    Unidades\n\n");

    listaAlmacenes[8].listaPacientes[3].listaPedidos[0].referenciaPedidos = 4;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[3].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[3].listaPedidos[0].diaEnvio = 14;
    printf("%i", listaAlmacenes[8].listaPacientes[3].listaPedidos[0].diaEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[0].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[8].listaPacientes[3].listaPedidos[0].mesEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[0].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[8].listaPacientes[3].listaPedidos[0].anioEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s            ", strncpy(listaAlmacenes[8].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Orfidal", 21));
    listaAlmacenes[8].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 390;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 3;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[3].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[0].listaPedidos[0].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[0].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[0].listaPedidos[0].diaEnvio = 8;
    printf("%i", listaAlmacenes[8].listaPacientes[0].listaPedidos[0].diaEnvio);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[0].mesEnvio = 6;
    printf("/%i/", listaAlmacenes[8].listaPacientes[0].listaPedidos[0].mesEnvio);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[0].anioEnvio = 2021;
    printf("%-7i", listaAlmacenes[8].listaPacientes[0].listaPedidos[0].anioEnvio);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s              ", strncpy(listaAlmacenes[8].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Adiro", 21));
    listaAlmacenes[8].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 90;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 9;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[0].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[4].listaPedidos[0].referenciaPedidos = 5;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[4].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[4].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[4].listaPedidos[0].diaEnvio = 8;
    printf("%i", listaAlmacenes[8].listaPacientes[4].listaPedidos[0].diaEnvio);
    listaAlmacenes[8].listaPacientes[4].listaPedidos[0].mesEnvio = 6;
    printf("/%i/", listaAlmacenes[8].listaPacientes[4].listaPedidos[0].mesEnvio);
    listaAlmacenes[8].listaPacientes[4].listaPedidos[0].anioEnvio = 2021;
    printf("%-7i", listaAlmacenes[8].listaPacientes[4].listaPedidos[0].anioEnvio);
    listaAlmacenes[8].listaPacientes[4].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[8].listaPacientes[4].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Ventolin", 21));
    listaAlmacenes[8].listaPacientes[4].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 40;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[4].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[4].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 2;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[4].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[1].listaPedidos[0].referenciaPedidos = 2;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[1].listaPedidos[0].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[0].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[1].listaPedidos[0].diaEnvio = 14;
    printf("%i", listaAlmacenes[8].listaPacientes[1].listaPedidos[0].diaEnvio);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[0].mesEnvio = 7;
    printf("/%i/", listaAlmacenes[8].listaPacientes[1].listaPedidos[0].mesEnvio);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[0].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[8].listaPacientes[1].listaPedidos[0].anioEnvio);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[0].numeroFarmacosPedidos = 0;
    printf("%s            ", strncpy(listaAlmacenes[8].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].nombreFarmaco, "Sintrom", 21));
    listaAlmacenes[8].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].pesoFarmaco = 390;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco = 1;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[1].listaPedidos[0].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[3].listaPedidos[1].referenciaPedidos = 4;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[3].listaPedidos[1].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[1].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[3].listaPedidos[1].diaEnvio = 14;
    printf("%i", listaAlmacenes[8].listaPacientes[3].listaPedidos[1].diaEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[1].mesEnvio = 7;
    printf("/%i/", listaAlmacenes[8].listaPacientes[3].listaPedidos[1].mesEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[1].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[8].listaPacientes[3].listaPedidos[1].anioEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[1].numeroFarmacosPedidos = 0;
    printf("%s        ", strncpy(listaAlmacenes[8].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].nombreFarmaco, "Paracetamol", 21));
    listaAlmacenes[8].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].pesoFarmaco = 190;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco = 3;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[3].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[0].listaPedidos[1].referenciaPedidos = 1;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[0].listaPedidos[1].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[1].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[0].listaPedidos[1].diaEnvio = 1;
    printf("%i", listaAlmacenes[8].listaPacientes[0].listaPedidos[1].diaEnvio);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[1].mesEnvio = 8;
    printf("/%i/", listaAlmacenes[8].listaPacientes[0].listaPedidos[1].mesEnvio);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[1].anioEnvio = 2021;
    printf("%-6i ", listaAlmacenes[8].listaPacientes[0].listaPedidos[1].anioEnvio);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[1].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[8].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].nombreFarmaco, "Enantyum", 21));
    listaAlmacenes[8].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].pesoFarmaco = 200;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco = 4;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[0].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[1].listaPedidos[1].referenciaPedidos = 2;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[1].listaPedidos[1].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[1].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[1].listaPedidos[1].diaEnvio = 2;
    printf("%i", listaAlmacenes[8].listaPacientes[1].listaPedidos[1].diaEnvio);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[1].mesEnvio = 8;
    printf("/%i/", listaAlmacenes[8].listaPacientes[1].listaPedidos[1].mesEnvio);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[1].anioEnvio = 2021;
    printf("%-6i ", listaAlmacenes[8].listaPacientes[1].listaPedidos[1].anioEnvio);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[1].numeroFarmacosPedidos = 0;
    printf("%s            ", strncpy(listaAlmacenes[8].listaPacientes[1].listaPedidos[1].listaMedicamentos[0].nombreFarmaco, "Nolotil", 21));
    listaAlmacenes[8].listaPacientes[1].listaPedidos[1].listaMedicamentos[0].pesoFarmaco = 350;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[1].listaPedidos[1].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[1].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco = 7;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[1].listaPedidos[1].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[3].listaPedidos[2].referenciaPedidos = 4;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[3].listaPedidos[2].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[2].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[3].listaPedidos[2].diaEnvio = 14;
    printf("%i", listaAlmacenes[8].listaPacientes[3].listaPedidos[2].diaEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[2].mesEnvio = 9;
    printf("/%i/", listaAlmacenes[8].listaPacientes[3].listaPedidos[2].mesEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[2].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[8].listaPacientes[3].listaPedidos[2].anioEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[2].numeroFarmacosPedidos = 0;
    printf("%s            ", strncpy(listaAlmacenes[8].listaPacientes[3].listaPedidos[2].listaMedicamentos[0].nombreFarmaco, "Clexane", 21));
    listaAlmacenes[8].listaPacientes[3].listaPedidos[2].listaMedicamentos[0].pesoFarmaco = 390;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[3].listaPedidos[2].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[2].listaMedicamentos[0].unidadesFarmaco = 4;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[3].listaPedidos[2].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[3].listaPedidos[3].referenciaPedidos = 4;
    printf("    %-9i", listaAlmacenes[8].listaPacientes[3].listaPedidos[3].referenciaPedidos);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[3].numerosEnvios = 1;
    listaAlmacenes[8].listaPacientes[3].listaPedidos[3].diaEnvio = 14;
    printf("%i", listaAlmacenes[8].listaPacientes[3].listaPedidos[3].diaEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[3].mesEnvio = 5;
    printf("/%i/", listaAlmacenes[8].listaPacientes[3].listaPedidos[3].mesEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[3].anioEnvio = 2021;
    printf("%-6i", listaAlmacenes[8].listaPacientes[3].listaPedidos[3].anioEnvio);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[3].numeroFarmacosPedidos = 0;
    printf("%s           ", strncpy(listaAlmacenes[8].listaPacientes[3].listaPedidos[3].listaMedicamentos[0].nombreFarmaco, "Aspirina", 21));
    listaAlmacenes[8].listaPacientes[3].listaPedidos[3].listaMedicamentos[0].pesoFarmaco = 390;
    printf(" %-10i", listaAlmacenes[8].listaPacientes[3].listaPedidos[3].listaMedicamentos[0].pesoFarmaco);
    listaAlmacenes[8].listaPacientes[3].listaPedidos[3].listaMedicamentos[0].unidadesFarmaco = 6;
    printf("%-i\n", listaAlmacenes[8].listaPacientes[3].listaPedidos[3].listaMedicamentos[0].unidadesFarmaco);

    listaAlmacenes[8].listaPacientes[0].numeroPedidosRealizados = 2;
    listaAlmacenes[8].listaPacientes[1].numeroPedidosRealizados = 2;
    listaAlmacenes[8].listaPacientes[3].numeroPedidosRealizados = 4;
    listaAlmacenes[8].listaPacientes[5].numeroPedidosRealizados = 1;
}
void pantallaInicio() //Imprime el menú de inicio de la aplicación
{
    char opcionElegida;
    do
    {
        do
        {
            printf("\nGESTION DE FarmaDrones:  Distribucion de Farmacos\n");
            printf("    Iniciar gestion                    (Pulsar I)\n");
            printf("    Alta almacen                       (Pulsar M)\n");
            printf("    Alta paciente almacen              (Pulsar A)\n");
            printf("    Ubicar pacientes                   (Pulsar U)\n");
            printf("    Nuevo pedido                       (Pulsar N)\n");
            printf("    Lista diaria de pedidos            (Pulsar L)\n");
            printf("    Programar rutas diarias del dron   (Pulsar P)\n");
            printf("    Representar rutas diarias del dron (Pulsar R)\n");
            printf("    Salir                              (Pulsar S)\n");
            printf("Teclear una opcion valida (I|M|A|U|N|L|C|P|R|S)? ");
            scanf("%c", &opcionElegida);

        } while (opcionElegida != 'I' && opcionElegida != 'i' && opcionElegida != 'M' && opcionElegida != 'm' && opcionElegida != 'A' && opcionElegida != 'a' && opcionElegida != 'U' && opcionElegida != 'u' && opcionElegida != 'N' && opcionElegida != 'n' && opcionElegida != 'L' && opcionElegida != 'l' && opcionElegida != 'P' && opcionElegida != 'p' && opcionElegida != 'R' && opcionElegida != 'r' && opcionElegida != 'S' && opcionElegida != 's');

        if (opcionElegida == 'I' || opcionElegida == 'i')
        {
            iniciarGestion();
        }
        if (opcionElegida == 'M' || opcionElegida == 'm')
        {
            altaAlmacen();
        }
        if (opcionElegida == 'A' || opcionElegida == 'a')
        {
            altaPacienteAlmacen();
        }
        if (opcionElegida == 'U' || opcionElegida == 'u')
        {
            ubicarPacientes();
        }
        if (opcionElegida == 'N' || opcionElegida == 'n')
        {
            nuevoPedido();
        }
        if (opcionElegida == 'L' || opcionElegida == 'l')
        {
            listaDiariaPedidos();
        }
        if (opcionElegida == 'P' || opcionElegida == 'p')
        {
            representarRutasDiarias();
        }
        if (opcionElegida == 'R' || opcionElegida == 'r')
        {
            programarRutasDiarias();
        }
        if (opcionElegida == 'S' || opcionElegida == 's')
        {
            return;
        }
        scanf("%c", &restos);
        pantallaInicio();

    } while (!opcionElegida == 'S' || !opcionElegida == 's');
}

int main()
{

    pantallaInicio();
}
