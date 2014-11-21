/*
	Name: pulsehalpe.cpp
	Copyright: 
	Author: 
	Date: 14/11/14 14:04
	Description: 
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "general_variables.h"
#include "pulseshape.h"

#include "loadascii.h"

/****** constructor destructor*****/

pulseshape::pulseshape()
{

	PSarray=NULL;

    PSlen=0;
    PSdt=0;
	
	
	
}


pulseshape::pulseshape(float *array, int arraylen,float dt)
{
	if(array!=NULL)
	{
	
	PSarray=array;
	PSlen=arraylen;
	PSdt=dt;
	
	}
	// add check and debug msg
	
}


pulseshape::~pulseshape()
{
	if(PSarray!=NULL)
	{
		delete [] PSarray;
	}
	
}	


/************ FUNCTION FOR MAKING PREDEFINED pulseshape ***********/

int pulseshape::create_exp_pulseshape(float dt, int arraylen, float par1,bool charge_norm)// Function for generating an exponentiel pulseshape 
{	
	
	if(verbose)
	{
			printf("CREATION OF EXP PULSE SHAPE\n");
			printf("--> PARAM 1: %f \n",par1,par2);
	}
	if(arraylen<1)
	{
		if(verbose)
			printf("** ERROR CREATING PSHAPE: BAD LENGTH\n");
	return -1; //error, the array length is undefined
	}
	
		//handling of the case where the memory is already allocated
	if(arraylen!=PSlen) //different amount of points -> reallocating memory  
	{
		
		delete [] PSarray;
		
		PSarray=new float[arraylen]; // alloc new memory
		PSlen=arraylen; //copy of the proper array length


	}
	
	
	PSdt=dt;
	
	
	//construction of the exp pulse shape;	
	for(int i=0;i<arraylen;i++)// create the array with exp and compute the sum of data
	PSarray[i]=exp(-float(i)*dt/par1);
	
	normalize_pulseshape(charge_norm);	
	return 1;
}

int pulseshape::create_dampexp_pulseshape(float dt, int arraylen, float par1, float par2,bool charge_norm) // function for generating a damp exp pulseshape
{
	if(verbose)
	{
			printf("CREATION OF DAMPEXP PULSE SHAPE\n");
			printf("--> PARAM 1: %f / PARAM 2: %f\n",par1,par2);
	}
	
	if(arraylen<1)
	{
		if(verbose)
			printf("** ERROR CREATING PSHAPE: BAD LENGTH\n");
	return -1; //error, the array length is undefined
	}
		
	//handling of the case where the memory is already allocated
	if(arraylen!=PSlen) //different amount of points -> reallocating memory  
	{
		
		delete [] PSarray;
		
		PSarray=new float[arraylen]; // alloc new memory
		PSlen=arraylen; //copy of the proper array length


	}
	
	
	PSdt=dt;
	
	//construction of the exp pulse shape;	
	for(int i=0;i<arraylen;i++)
	PSarray[i]=exp(-float(i)*dt/par1)-exp(-float(i)*dt/par2);
	
	normalize_pulseshape(charge_norm);
	return 1;	
}	

int pulseshape::normalize_pulseshape(bool norm_by_charge)//function for normalizing the data with charge or amplitude
{
	if(verbose)
			printf("NORMALIZING PULSESHAPE\n");
	
	float max=-10000000000;
	int max_index=0;
	if(PSarray==NULL)
	{
		if(verbose)
		{
			printf("** ERROR NORMALIZE_PULSESHAPE: NO DATA IN PSHAPE\n");
		}
	return -1;
	}
	
	if(norm_by_charge)
	{
		max=0;
		for(int i=0;i<PSlen;i++)
		 max+=PSarray[i];
		
		max=1./(max*PSdt);
		
		for(int i=0;i<PSlen;i++)
		PSarray[i]*=max;
		
	}
	else
	{
		
		for(int i=0;i<PSlen;i++)
		{
			if(PSarray[i]>max)
			{
				max=PSarray[i];
				max_index=i;
			}
			
		}
		for(int i=0;i<PSlen;i++)
		{
			PSarray[i]/=max;
		}
		
	}


return 1;	
}



int pulseshape::save_pulseshape(char* filename)
{
		if(verbose)
					printf("SAVING PULSE SHAPE TO %s\n",filename);
	
	if(PSarray==NULL)
	{
		if(verbose)
		{
			printf("** ERROR SAVE_PULSESHAPE: NO DATA IN PSHAPE\n");
		}	
	return -1;
	}
	
	FILE *f=fopen(filename,"w");
	if(f==NULL)
	{
		if(verbose)
		{
			printf("** ERROR SAVE_PULSESHAPE: UNABLE TO OPEN FILE\n");
		}
		return -1;// unable to open file
	}
	
	// save of the pulseshape
	fprintf(f,"#Save of pulse shape. Length: %d, dt: %f\n",PSlen,PSdt);
	for(int i=0;i<PSlen;i++)
	fprintf(f,"%f	%f\n",float(i)*PSdt,PSarray[i]);
	
	fclose(f);
	return 1;
}
