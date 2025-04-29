#include <stdio.h>
#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main()
{

int r=10,a=20,a1=10,b1=20;

printf("circemferance = %f\n",cir_cirm(r));

printf("rectangle perimeter = %d\n",peri_rect(a1,b1));

printf("square perimeter = %d\n",per_squ(a));

return 0;
}

