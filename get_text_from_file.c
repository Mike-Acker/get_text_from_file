#include<stdio.h>
#include <string.h>
#include <malloc.h>
#define FILE_NAME parm_list[1]
#define LINE_NR parm_list[2]
#define POSITION parm_list[3]
#define LENGTH parm_list[4]
#define RESPONSE_FILE_NAME parm_list[5]
#define MAX_LINE_LENGTH 1024

int main(int nof_args, char **parm_list);
/*
	get selected text from source file
	C / w.albert / 21 FEB 2021
	For use with bash script where a program is executed and some text is needed from the results thereof.
	Comand line:
			get_test_from_file <source file name> <line number> <position> <length> <message file name>
	Example:
			get_test_from_file source.txt 2 7 40 message.txt
	Explanation:
			get_test_from_file 	-- executes the program
			source.txt		-- name of input file to be scanned
			2			-- line number to extract result from
			7			-- position within line 2 where result starts
			40			-- number of character to extract from line 2 starting on column 7
			message.txt		-- name of file to which result is to be written
*/

int main(int nof_args, char **parm_list)
	
	{

/* initialization */

	int retc = 0, ln=0, pos=0, len=0, line_ctr=0, run_switch=1;
	FILE *source;
	char *source_data, *result_data, *null_result="NULL RESULT";

	if (nof_args == 6) ; else { puts("Command Line must have: source file name, line number to find," 
						"\nstart position on that line, length of text to get, output file name\n");
					return(1); }

	printf("Input file name: %s; line nr: %s; position: %s; length: %s; Output message file: %s.\n", FILE_NAME, LINE_NR, POSITION, LENGTH, RESPONSE_FILE_NAME);
	
	sscanf(LINE_NR, "%d", &ln);
	sscanf(POSITION, "%d", &pos);
	sscanf(LENGTH, "%d", &len);

/* checking search argument */

	if ( ln > 0 && pos > 0 && len > 0 && pos + len < MAX_LINE_LENGTH ) ;
	else {	printf("Filename %s line number %d position %d length %d\n", FILE_NAME, ln,pos,len);
		puts("Invalid search arguments");   return(3); }

/* open the source text */

	source = fopen (FILE_NAME,"rt");
	if ( NULL == source ) { printf ("%s -- file not found\n", FILE_NAME);
					return(2); }

	source_data = malloc (MAX_LINE_LENGTH);

/* reading the input: */
	
	do 
	{
		fgets(source_data, MAX_LINE_LENGTH, source);
		if ( feof(source) ) {printf("File ended at line %d -- no output\n",line_ctr); retc=5; break; }
		line_ctr++;
		printf("%d %s", line_ctr, source_data);
		if (line_ctr==ln) run_switch=0; /* stop execution; return result */
	}	
	while ( run_switch );

/* writing the result */

	/* what to do about retc ( 5 ) ??    -- you return the null result string */

	fclose(source);	
	if (strlen(source_data) < pos+len) {printf("%d insufficient source data ( line too short ) \n", strlen(source_data) ); retc=4; }
	else source_data[pos+len-1] = 0x00;  /* end the line at the requested length */
	if (0==retc) result_data = &source_data[pos-1];
	else result_data = null_result;

	printf("Result: %s  Length: %d\n", result_data, strlen(result_data) );

	source=fopen(RESPONSE_FILE_NAME,"w");
	fputs (result_data, source);
	fclose(source);

/* return */	

	return(retc);
	}


