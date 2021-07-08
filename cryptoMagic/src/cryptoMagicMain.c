//	FILE			: cryptoMagicMain.c
//	PROJECT			: CryptoMagic
//	PROGRAMMER		: KEVIN DOWNER
//	FIRST VERSION		: 2021-02-06
//	DESCRIPTION		: Runs the program and decides the course of action(-enrypt or -decrypt),
//				and the filename to process, based on argument checks.				
//
//				Options:
//
//				ex. -encrypt <filename>
//				If Encrypt is chosen, it reads the input file and processes the result as a encrypted file export.
//				appending the extension of '.crp' on the end of the file, to indicate it is encrypted.
//
//				ex. <filename>
//				Without a command, it assumes that the file input is to be encrypted (see above)
//
//				ex. -decrypt <filename>
//				If Decrypt is chosen, it reads the input file and processes the result as a decrypted file export,
//				appending the extension as 'txt' on the end of the file, to indicate it is decrypted.
//
//				Error checks:
//				- Missing command arguments (also checks one argument provided to ensure it is not a command).
//				- Matching command arguments to encrypt or decrypt.
//				- Too many arguments
//				- If a space in the filename input (reminds user that quotes are needed).


// To gain access to the shared items between the program .c files
#include "../inc/cryptoMagicHeaders.h"


// The main for cryptoMagic program
int main(int argc, char* argv[])
{
	// No User input: cannot continue
	if (argc < 2)
	{
		// Error feedback for User
		printf("ERROR: Missing a command/filename input to process.\n");
		// Exit Program	
		exit(-1);
	}

	// One User input: check if file missing or command mis-typed by User
	else if (argc == 2)
	{
		// Check the command for typo error by User
		if ((0 == strcmp(argv[1], "-encrypt")) || (0 == strcmp(argv[1], "-decrypt")))
		{
			// Error feedback for User
			printf("ERROR: The command '%s' needs a filename to process.\n", argv[1]);
			// Exit Program	
			exit(-1);
		}

		// Not a command, must be a file then
		else
		{
			// OK, just the file so go to default, non-command task and encrypt the file
			encryptProcessMain(argv[1]);
			// All is well, time to exit
			exit(0);
		}
	}

	// Two User inputs: ok, keep going on User input checks
	else if (argc == 3)
	{
		// Check for match of argument one to encrypt command
		if (0 == strcmp(argv[1], "-encrypt"))
		{
			encryptProcessMain(argv[2]);
			exit(0);
		}

		// Check for match of argument one to decrypt command
		else if (0 == strcmp(argv[1], "-decrypt"))
		{
			decryptProcessMain(argv[2]);
			exit(0);
		}

		// Might be a problem with sapces in the filename.
		// Notify User and remind them to use quotes in terminal for files with spaces in names
		else
		{
			// Error feedback for User
			printf("ERROR: The command '%s' chosen to process the file is not recognised.\nOR your file has a space in the name and needs to be surrounded by quotes.\n", argv[1]);
			// Exit Program			
			exit(-1);
		}
	}

	// Three arguments: too many commands entered or spaces in the filename.
	// Notify User and remind them to use quotes in terminal for files with spaces in names
	else if (argc > 3)
	{
		printf("ERROR: You have entered too many arguments\nOR your file has a space in the name and needs to be surrounded by quotes.\n");
		// Exit Program	
		exit(-1);
	}


	// Time to end this charade!!! (program ends)
	return 0;
}



/*
Name	:	void stripExtension(char* fname)
Purpose :	Takes the input file name and removes the dot and any slashes for fruther processing (note: got some Stoackoverflow help for this one)
Inputs	:	char* fname : The input file to be processed
Outputs	:	char* fname : The cleaned filename
Returns	:	void: none
*/
void stripExtension(char* fileExtToStrip)
{
	// Prep filename for extension check
	char* end = fileExtToStrip + strlen(fileExtToStrip);

	// Take the filename and find the last dot (the extension)
	while (end > fileExtToStrip && *end != '.' && *end != '\\' && *end != '/')
	{
		--end;
	}

	// Null terminate the new stripped version of filename
	if (end > fileExtToStrip && *end == '.')
	{
		*end = '\0';
	}
}
