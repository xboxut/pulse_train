#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


#include "mt19937ar.h"
#include "pulseshape.h"

int main(int argc, char** argv) 
{
	
	init_genrand(0);
	pulseshape test;
	test.create_exp_pulseshape(0.001, 1000, 1.,true);
	
	test.save_pulseshape("toto.txt");
	
	for(int i=0;i<100000000;i++)
	genrand_int32();
	
	
	return 0;
}
