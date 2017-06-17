/******************************************************************
*
*   file:     cmds.c
*   author:   betty o'neil
*   date:     ?
*
*   semantic actions for commands called by tutor (cs341, hw2)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio.h>
#include "slex.h"

/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);

/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <hexaddress>"},
              {"s",   stop,        "Stop"},
	      {"h",   help,        "Help: <cmd>"},
	      {"ms",  mem_set,     "Memory set: MS <hexaddress> <new_value>"},
              {NULL,  NULL,         NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

int stop(Cmd *cp, char *arguments) { return 1;	}		
/* all done flag */

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/

int mem_display(Cmd *cp, char *arguments) {
	int address = 0; 
	int i;
	unsigned char *paddress;
	printf("%08s\t",arguments+1);
	sscanf(arguments, "%x", &address);
	paddress = address;
	for (i=0; i<=16; i++)	printf("%02x ",*(paddress+i));
	for (i=0; i<=16; i++)
		(*(paddress+i) >= 0X20 && *(paddress+i) <= 0X7F) ? printf("%c", *(paddress+i)) : printf("."); 
	printf("\n");
	return 0;			
}

int mem_set(Cmd *cp, char *arguments) {
	int address, hex;
	unsigned char *paddress;
	sscanf(arguments, "%x %x", &address , &hex);
	paddress = (unsigned char *)address;
	*paddress = hex;
	return 0;
}

int help(Cmd *cp, char *arguments) {
	char function[2];
	int pos = 0;
	sscanf(arguments, "%s", function);
	while (pos < (sizeof(cmds)/sizeof(Cmd))) {
		if ((strcmp(cmds[pos].cmdtoken, function)) == 0) {
			printf("%s\n", cmds[pos].help);
			break;
		}	else	pos++;
	}
		/*(strcmp(cmds[pos].cmdtoken, function)) == 0 ? printf("%s\n", cmds[pos++].help) : pos++;
	/*	if ((strcmp(cmds[pos].cmdtoken, function)) == 0)
			printf("%s\n", cmds[pos++].help); */
	return 0;
}
