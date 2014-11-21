/*
	Name: pulsetrain.cpp
	Copyright: 
	Author: 
	Date: 16/11/14 17:31
	Description: 
*/


/* A VOIR:

	*DESTRUCTEUR: format of the amplitude array
	* GENERAL: verify the validity of OPENMP preproc code in order to be able to generate the code without the multiproc support
	* DATA SAVE FUNCTION AND LOW MEMORY GEN FUNCTION: define the various predef amplitude distribution and handle them in the various portion of code. 
	* DATA SAVE FUNCTION AND LOW MEMORY GEN FUNCTION: define the various predef noise sources and handle them in the various portion of code. 

*/


#ifdef _OPENMP
#include <omp.h>	
#endif			

#include "pulseshape.h"
#include "pulsetrain.h"

#include "general_variables.h"



//*******************************************************************
//***************************** CONSTRUCTOR **************************
//**********************************DESTRUCTOR *************************
//************************************************************************
pulsetrain::pulsetrain()
{
	
	if(verbose)
	printf("INITIALISATION OF THE PULSE TRAIN OBJECT %d \n",this);
	
	//DATA DEFINITION
	amplitude_array=NULL;   // Pointer to an array of the amp_time_array_len containing the amplitude of pulses. used only for high and medium memory usages
	time_array=NULL; //pointer to an array representing the time where pulses occurs. 
							  //Data are ints (multiple of dt) for speed up and direct access to array elements 
	
	amp_time_array_len=0; // Variable for knowing the size of the time and amplitude array if they are already allocated.
									 // Useful for avoiding memory reallocation  -> speed up loop 
	
	dirac_array=NULL;  // Pointer to an array where the impulse representation of pulse (before convolution) will be stored. Computed on demand:
						 // High memory usage -> dirac array are computed in order to convolute data with fft
						 // Medium memory usage -> Computation on demand. 
						 // low memory usage -> computation on demand
						 // Low mem/Speed ->  computation in order to use fft for convolution
						 
	final_array=NULL; // Pointer to an array where the final pulse train is stored
	
	
	final_array_len=0; 
	
	PTdt=0; //time step used for the pulse train
	PTlength=0; // total length of the pulse train
	
	pulse_count=0;// Var where the total number of pulse is stored
	
	
	
	/*************** DEFINITION OF THE PROCESS SPECIFICATION ***********/
	
	// Count rate and stuff
	homogen_process=true; // Bool to say if the process is homogeneous or not. if true the count rate in count_rate is used. Else,  it's the data in inhom_count_rate which is used.

	count_rate=0;
	inhom_count_rate=NULL;
	
	
	// amplitude distribution
	predef_ampdistrib=true; //If the amplitude distribution used is predefined .
	
	predef_ampdistrib_sel=-1; //data for choosing the proper predefined amplitude distribution.
	predef_ampdistrib_param[0]=-1.;//parameters for the predefined amplitude distribution.
	predef_ampdistrib_param[1]=-1.;//parameters for the predefined amplitude distribution.
	predef_ampdistrib_param[2]=-1.;//parameters for the predefined amplitude distribution.
	
	
	
	ampdistrib_data=NULL;
	ampdistrib_data_length=0;
	
	// Noise generation ----------
	noise_add=false;
	predef_noisedistrib_sel=-1;// Constant for choosing the proper predefined noise distibution to use.
	predef_noise_stdev=0; // A VOIR
	predef_noise_seed=0; // useful for adding and substracting the generated noise without spending a lot of memory. Con: it is computing power consuming
	
	
	
	
}
	
	
pulsetrain::~pulsetrain()
{
	if(verbose)
	printf("FREEING MEMORY ALLOCATED FOR THE PULSE TRAIN %d\n",this);
		
	if(amplitude_array!=NULL) delete [] amplitude_array;
	if(time_array!=NULL)delete [] time_array;
	
	if(dirac_array!=NULL) delete [] dirac_array;
	if(final_array!=NULL) delete [] final_array;
	//if(inhom_count_rate!=NULL)delete [] inhom_count_rate; // A Voir 
	if(inhom_count_rate!=NULL)delete [] inhom_count_rate[0];
	if(inhom_count_rate!=NULL)delete [] inhom_count_rate[1];
	if(inhom_count_rate!=NULL)delete inhom_count_rate; 
	
	if(	ampdistrib_data!=NULL)delete [] 	ampdistrib_data;
	 
}


//*******************************************************************
//**************%***********BASE *****************%********************
//************%*****DATA GENERATION FUNCTIONS *****%*********************
//************************************************************************


//*******************************************************************
//**************%*********FUNCTION ***************%********************
//************%*****FOR SAVING DATA TO FILE ******%*********************
//************************************************************************
	
	
	/*int pulsetrain::save_ptrain_ascii_xy(char * filename)
	
	function for saving the pulse train in a ascii file.
	As the pulse train could be quite long, the file format is as follow:
	
	# pulse_train dt
	# pulse train length (number of data in the file)
	# pulse train duration
	# exact pulse count
	# count rate type and rate if homogeneous
	# amplitude distrubution type and  (name) if predefined
	# with or without noise
	
	data written with 4 digit float
	
	*/
	int pulsetrain::save_ptrain_ascii_xy(char * filename)
	{
		
	 	if(verbose)
			printf("SAVING THE PTRAIN TO THE FILE: %s\n", filename);

		if(final_array==NULL)// error, the PT array was not computed
		{
			if(verbose)
			{
				printf("** ERROR SAVE_PTRAIN_ASCII_XY: NO DATA IN THE PTRAIN\n");
			}
			return -1;
		}
	
		//opening the file
		FILE *fich=fopen(filename,"w");
		
		if(fich==NULL)// If the code is unable to open the file 
		{
			if(verbose)
			{
				printf("** ERROR SAVE_PTRAIN_ASCII_XY: UNABLE TO OPEN FILE\n");
			}
			return -2;
				
		}
		
		
		// Save of general pulse train properties
		
		fprintf(fich,"#Pulse train time step: %f\n", this->PTdt);
		fprintf(fich,"#Total number of data in Pulse train: %f\n",this->PTlength);
		fprintf(fich,"#Pulse train duration: %f\n",float(this->PTlength)*this->PTdt);
		fprintf(fich,"#Exact number of pulses in the PT %d",this->pulse_count);
		if(this->homogen_process)
		fprintf(fich,"# homogeneous proc; count rate was defined: %f\n",this->count_rate);
		else
		fprintf(fich,"# non homogeneous proc; count rate was user defined.\n");
		
		if(this->predef_ampdistrib) // TO DEFINE WITH ZSOLT
			switch(this->predef_ampdistrib_sel) // the used parameter for the predef amplitude distribution will be written in the switch
			{									// In order to put only useful and defined param in the code
				
				
			case default:
				
			}
			
		else
		fprintf(fich,"# non homogeneous proc; count rate was user defined.\n");
			
		
		
	}
	
	int pulsetrain::save_ptraindirac_ascii(char *filename)
	{
		
		
	}
	
	int pulsetrain::save_ptrain_ascii_y(char *filename)
	{
		
		
	}
	
	int pulsetrain::save_ptrain_binary(char *filename)
	{
		
	}
	
	int pulsetrain::save_ptraindirac_binary(char *filename)
	{
		
	}
	

//*******************************************************************
//**************%***********BASIC DATA ***********%********************
//************%*********PROCESSING FUNCTIONS ******%*********************
//************************************************************************

	
float pulsetrain::get_ptrain_max()
{
	
	float maxv=-100000000.;

	if(verbose)
			printf("CALCULATING THE PULSE TRAIN MAX VALUE\n");
	
	if(final_array==NULL)// error, the PT array was not computed
	{
		
		return -1.0;
	}
	
	#ifdef _OPENMP
	#pragma omp parallel for reduction (max:maxv)
	#endif			
	for(int i=0;i<PTlength ;i++)
	 {
	 if(maxv<final_array[i])
			maxv=final_array[i];
	 }	
	
	
}	


float pulsetrain::get_ptrain_min()
{
	float minv=100000000000.;

	if(verbose)
			printf("CALCULATING THE PULSE TRAIN MIN VALUE\n");

	if(final_array==NULL)// error, the PT array was not computed
	{
		if(verbose)
		{
			printf("** ERROR GET_PTRAIN_MIN: NO DATA IN THE PTRAIN\n");
		}
		return -1.0;
	}
	
	#ifdef _OPENMP
	#pragma omp parallel for reduction (min:minv)
	#endif			
	for(int i=0;i<PTlength ;i++)
	 {
	 if(minv>final_array[i])
			minv=final_array[i];
	 }
	 
}

float pulsetrain::get_ptrain_mean()
{

	float sum=0;
	
	if(verbose)
		printf("CALCULATING THE PULSE TRAIN MEAN VALUE\n");


	
	if(final_array==NULL)// error, the PT array was not computed
	{
		if(verbose)
		{
			printf("** ERROR GET_PTRAIN_MEAN: NO DATA IN THE PTRAIN\n");
		}			
		return -1.0;
	}

#ifdef _OPENMP
#pragma omp parallel for reduction (+:sum)
#endif	
	for(int i=0;i<PTlength ;i++)
	sum+=final_array[i];
	
	
	 return sum/float(PTlength);
}
	


//*******************************************************************
//*************%*********MORE COMPLEX DATA *******%********************
//************%*********PROCESSING FUNCTIONS ******%*********************
//************************************************************************


unsigned int pulsetrain::pulse_counting_algorithm(float discri_level,int dead_time) 
{
	
}


