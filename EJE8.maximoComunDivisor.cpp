#include<stdio.h>

int main ()
{
    int num1, num2, a, b, res;

    printf ("Primer Numero? ");
    scanf ("%d", &num1);
    printf ("Segundo nÚmero? ");
    scanf ("%d", &num2);

    if (num1<num2)
    {
        a= num2;
        b = num1;
        }else if ( num1>num2)
        {
            a = num1;
            b = num2;
        }
        

        do{

            res  = b;
            b = a%b;
            a = res;
        }while (b!=0);

        printf("El M.C.D. entre %d y %d es: %d\n", num1, num2, res);



}