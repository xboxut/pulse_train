/*
	Name: general_variables
	Copyright: G. de Izarra
	Author: G. de Izarra
	Date: 16/11/14 17:12
	Description: Header for defining some global variable dedicated to the whole simulation code
*/


/**************************** GENERAL VARIABLES FOR HANDLING THE SCRIPT*******************************/


extern bool verbose;// definition of a bool used in the whole code for printing message in the console
extern bool debug;// definition of the bool used to set the debug log
extern FILE *dbglog; // pointer to the file used for debug log

extern char * pulse_train_save_format;// the format for saving data


// var for checking that all options have been correctly defined and allowing the computation of pulse train

extern bool have_dt; // if a proper dt or freq have been set in the script
extern bool have_basename;// if a proper filename have been set for data save

extern char * base_name; // a pointer to the stored base savename
extern int file_numbering; //a integer to store the number of pulsetrain already generated. Usefull for composing filenames.


extern bool have_pulshape;// is a pulse shape was defined in the script and then generated

extern bool have_ptampdistri;// if a amplitude distribution have been defined.

extern bool have_ptlength;// If the length of the pulsetrain have been defined.

extern bool have_ptcount;//If the counting rate of the pulsetrain have been defined

