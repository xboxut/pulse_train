/*
	Name: pulsehalpe.h
	Copyright: 
	Author: G. de Iz, Z. Elter 
	Date: 14/11/14 14:04
	Description: 
*/




class pulseshape
{
public:

/************ VARIABLES ************************/
float *PSarray;

int PSlen;
float PSdt;
	
	
/********** CONSTRUCTOR DESTRUCTOR **************/
pulseshape();
pulseshape(float *array, int arraylen,float dt);

~pulseshape();	

/************ FUNCTION FOR MAKING PREDEFINED pulseshape ***********/

//int create_exp_pulseshape(float dt, int arraylen, float par1,bool charge_norm);/
// function for generating an exponential pulse shape of the form f(t)=exp(-t/par1);
//
// PARAMETERS ARE:
// *dt 				the time step of the pulse shape
// *arraylen		the total length of the array. Its duration is defined as dt*arraylen
// *par1			the parameter for the exponential function.
// *charge_norm		a boolean to say how to normalize the pule. If true, the pulse is normalized in order to get a integral of 1.
//					if false, it's normalized on the maximum value.
int create_exp_pulseshape(float dt, int arraylen, float par1,bool charge_norm);// Function for generating an exponentiel pulseshape 


//int create_dampexp_pulseshape(float dt, int arraylen, float par1,float par2,bool charge_norm);/
// function for generating a damp exponential pulse shape of the form f(t)=exp(-t/par1)-exp(-t/par2);
//
// PARAMETERS ARE:
// *dt 				the time step of the pulse shape
// *arraylen		the total length of the array. Its duration is defined as dt*arraylen
// *par1			the parameter for the 1st exponential function.
// *par2			the parameter for the 2nd exponential function.
// *charge_norm		a boolean to say how to normalize the pulse. If true, the pulse is normalized in order to get a integral of 1.
//					if false, it's normalized on the maximum value.
int create_dampexp_pulseshape(float dt, int arraylen, float par1, float par2,bool charge_norm); // function for generating a damp exp pulseshape


//int create_pulse_shape_ffile(char* filename); 
// function for loading the pulse shape from a file
//
// PARAMETER IS:
// *filename		a pointer to a string containing the path of the pulseshape file.
int create_pulse_shape_ffile(char* filename); // generating a pulse shape from a data file.


//int normalize_pulseshape(bool norm_by_charge);
// function for normalising the pulse shape with its area or its maximum amplitude
//
//
// PARAMETER IS:
// *norm_by_charge	 a boolean to say how to normalize the pulse. If true, the pulse is normalized in order to get a integral of 1.
//					if false, it's normalized on the maximum value.	
int normalize_pulseshape(bool norm_by_charge);//function for normalizing the data with charge or amplitude	
	
int save_pulseshape(char* filename);

};
