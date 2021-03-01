#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	float num1=2.55;
	float num2=2.71;
	float num3=2.49;
	float num4=2.01;
	
	printf("\n Numeros:      %2.f\t%.2f\t%.2f\t%.2f", num1, num2, num3, num4);
	printf("\n Arredondando: %d\t%d\t%d\t%d", (int)roundf(num1), (int)roundf(num2), (int)roundf(num3), (int)roundf(num4));
	return 0;
}