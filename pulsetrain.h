/*
	Name: pulsetrain.h
	Copyright: 
	Author: prof, Z. Elter 
	Date: 14/11/14 14:31
	Description: Hahahaha
*/

class pulsetrain
{
public:	
	
	//data def
	float *amplitude_array;   // Pointer to an array of the amp_time_array_len containing the amplitude of pulses. used only for high and medium memory usages
	unsigned int *time_array; //pointer to an array representing the time where pulses occurs. 
							  //Data are ints (multiple of dt) for speed up and direct access to array elements 
	
	unsigned int amp_time_array_len; // Variable for knowing the size of the time and amplitude array if they are already allocated.
									 // Useful for avoiding memory reallocation  -> speed up loop 
	
	float *dirac_array;  // Pointer to an array where the impulse representation of pulse (before convolution) will be stored. Computed on demand:
						 // High memory usage -> dirac array are computed in order to convolute data with fft
						 // Medium memory usage -> Computation on demand. 
						 // low memory usage -> computation on demand
						 // Low mem/Speed ->  computation in order to use fft for convolution
						 
	float *final_array; // Pointer to an array where the final pulse train is stored
	
	
	unsigned int final_array_len; // Variable for knowing the size of final array if it is already allocated.
								  // Useful for avoiding memory reallocation  -> speed up loop 

	
	float PTdt; //time step used for the pulse train
	int PTlength; // total length of the pulse train
	
	unsigned int pulse_count;// Var where the total number of pulse is stored
	
	
	
	/*************** DEFINITION OF THE PROCESS SPECIFICATION ***********/
	
	// Count rate and stuff ------------------
	bool homogen_process; // Bool to say if the process is homogeneous or not. if true the count rate in count_rate is used. Else,  it's the data in inhom_count_rate which is used.

	float count_rate;
	float *inhom_count_rate;
	
	
	// amplitude distribution -----------------
	bool predef_ampdistrib; //If the amplitude distribution used is predefined .
	
	int predef_ampdistrib_sel; //data for choosing the proper predefined amplitude distribution.
	float predef_ampdistrib_param[3];//parameters for the predefined amplitude distribution.
	
	
	float **ampdistrib_data;
	int ampdistrib_data_length;
	
	// Noise generation ----------

	bool noise_added;
	int predef_noisedistrib_sel;// Constant for choosing the proper predefined noise distibution to use. CAREFUL: -1 if no distribution were selected
	float predef_noise_stdev; // A VOIR
	int predef_noise_seed; // useful for adding and substracting the generated noise without spending a lot of memory. Con: it is computing power consuming
	
	
	/******************
	****************** Constructor/ Destructor.
	*****************/	
	
	pulse_train();// Defaut constructor: init all the var
	
	~pulse_train(); // destructor. delete the allocated memory.
	
	
	/******************
	****************** function for generating pulse train and affiliate
	*****************/	
	
	/* Functions for high and medium memory usage */
	
	/*int gen_pulse_train_time();
	
	Function for generating times of the pulse train. It is used only for high and medium memory footprint.
	For low memory management, everything will be done in the lowmem function
	*/
	int gen_pulse_train_time();
	
	/*int gen_amplitude_array()();
	
	Function for generating the amplitude array of the pulse train. It is used only for high and medium memory footprint.
	For low memory management, everything will be done in the lowmem function in order not to use the amplitude array
	*/
	int gen_amplitude_array();
	
	/*int gen_dirac_array()
	
	Function for generating the array where dirac of height given by the amplitude distribution are stored. This has to be used for high memory footprint mode
	where the fft of the dirac array is multiplied with the fft of the pulse shape and then backtransformed in order to got the convolved result.
	In medium memory use, it will be used on demand.
	It is not used in low speed memory footprint for lowering as much as possible the use of large arrays
	*/
	int gen_dirac_array();
	
	/*int gen_final_array_fftconv()

	 function to compute the final data with the fft in order to speed up the computation. fft is O(nlog n)	
	It use at least 2 times the memory used for the final array. On 32 bit system this can be a problem since the maximum allocated memory is below 4GB.
	
	dirac_array HAS TO EXIST IN ORDER TO PERFORM THE COMPUTATION
	*/
	int gen_final_array_fftconv(pulseshape *ps); 
	
	/*int gen_final_array_simple_conv();
	
	Function to compute the final pulse train with a home made pseudo convolution. By itself the method use a low amount of memory.
	amplitude_array and time_array HAVE TO EXIST IN ORDER TO PERFORM THE COMPUTATION.
	*/
	int gen_final_array_simple_conv(pulseshape *ps);
	
	
	/* Functions for low memory footprint */
	
	
	int lowmem_gen_final_array(pulsehape *ps);
	
	int lowmem_gen_final_array_fftconv(pulseshape *ps);
	
	
	/* function for generating noise */
	
	int add_noise();
	int remove_noise();
	
	
	/******************
	****************** Function for saving the data
	*****************/
	
	int save_ptrain_ascii_xy(char * filename);
	int save_ptraindirac_ascii(char *filename);
	int save_ptrain_ascii_y(char *filename);
	
	int save_ptrain_binary(char *filename);
	int save_ptraindirac_binary(char *filename);
	
	
	/******************
	****************** Function for basic data processing
	*****************/	
	float get_ptrain_max();
	float get_ptrain_min();
	float get_ptrain_mean();
	
	/******************
	****************** Function for complex data processing
	*****************/	
	
	unsigned int pulse_counting_algorithm(float discri_level,int dead_time) 
};




