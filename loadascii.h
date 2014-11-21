/*
	Name: loadascii.h
	Copyright: 
	Author: 
	Date: 17/11/14 11:19
	Description: function for loading ascii datafiles whatever the token used to separate numbers
				 The maximum number of data point loadable is defined by the constant MAX_TAB_LENGTH
*/



#define MAX_TAB_LENGTH 10000


/*double ** universal_loader(int *size,const char *path);
*
 function for loading a datafile with the xy format into a 2* size array whatever the used token.

PARAMETERS ARE:

*size 
*path

*/
double ** universal_loader(int *size,const char *path);
