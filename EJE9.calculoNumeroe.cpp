#include <stdio.h>

int main ()
{
    float n;
    float e = 0;
    float intermedio;

    printf ("Error?: ");
    scanf ("%f",&n);

    for (int i =0; i<=n; i++)
    {
        intermedio =1;

        for (int j =i; j>=1; j--)
        {

            intermedio *= j;
            
        }
    e +=  (1/intermedio);
    
    }

    printf("Valor de e: %f",e);
}