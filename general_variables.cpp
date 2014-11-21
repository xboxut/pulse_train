/*
	Name: general_variables.cpp
	Copyright: 
	Author: 
	Date: 16/11/14 17:36
	Description: 
*/


/**************************** GENERAL VARIABLES FOR HANDLING THE SCRIPT*******************************/
#include <stdio.h>

 bool verbose=false;// definition of a bool used in the whole code for printing message in the console
 bool debug=false;// definition of the bool used to set the debug log
FILE *dbglog=NULL;
 
 char * pulse_train_save_format=NULL;// the format for saving data

// var for checking that all options have been correctly defined

 bool have_dt=false; // if a proper dt or freq have been set in the script
 bool have_basename=false;// if a proper filename have been set for data save


char * base_name; // a pointer to the stored base savename
int file_numbering=0; //a integer to store the number of pulsetrain already generated. Usefull for composing filenames.


 bool have_pulshape=false;// if a pulse shape was defined in the script and then generated

bool have_ptampdistri=false;// if a amplitude distribution have been defined.

bool have_ptlength=false;// If the length of the pulsetrain have been defined.

bool have_ptcount=false;//If the counting rate of the pulsetrain have been defined


