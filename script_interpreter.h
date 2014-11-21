/*
	Name: script_interpreter.h
	Copyright: CEA
	Author: G. de Izarra
	Date: 18/11/14 13:58
	Description: Definition of functions used for interpreting scripts. 
				 Global data for the communication between script and C code are store in the files 'general_variables'
			    
*/




/**********FUNCTIONS TO BIND TO LUA*****************/

/* Function defined here will be bind tu lua thanks to some initialisation function define in the next section
For ease of use, the function name will be the same in C and in lua.
Each time those function are called by lua, the script interpreter call the proper binded C function.

Thoose function have abaility to return data in lua. This is done by pushing the returns param into the LUA stack.
More explanations in the C file corresponding to this header.
*/ 



int register_genprop(lua_State *L);

int register_pulshapeprop(lua_State *L);

/*********** FUNCTION FOR LUA INITIALISING AND BINDING *****************/

