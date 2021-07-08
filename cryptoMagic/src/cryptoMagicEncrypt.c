//	FILE			: cryptoMagicEncrypt.c
//	PROJECT			: CryptoMagic
//	PROGRAMMER		: KEVIN DOWNER
//	FIRST VERSION		: 2021-02-06
//	DESCRIPTION		: Holds the functions to take the input file, processes it into a encrypted version and output the new file.
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
//				Error checks:
//				- If a filename input is missing the file in the directory.


// To gain access to the shared items between the program .c files
#include "../inc/cryptoMagicHeaders.h"


/*
Name	:	int encryptProcessMain(char* outChar)
Purpose :	The overall function that handles the encrypting of an input file,
			The encrypted file is exported with a .crp extension.
Inputs	:	char* outChar : The input file to be processed
Outputs	:	FILE* decryptResult : The decrypted, processed file is output
Returns	:	int: completion status
*/
int encryptProcessMain(char* outChar)
{
	int i = 0; // The index counter:  used for keeping track of array positioning
	int convertArrayInt[ARRAYSIZE]; // Holds the ASCII numeric values of the input char file
	int ifProcessGo = 1; // Just needed as flag for if statement execution check
	// Position in code for pre-processing important for below lines
	FILE* origFile = fopen(outChar, "r"); // Opens and buffers the file to be processed for encryption
	stripExtension(outChar); // Calls the function to strip any extensions off the input file
	char* filename = outChar; // Reference to the stripped file

	size_t len = strlen(outChar); // finds the length of the file line
	outChar[len] = '\0'; // Setup for the null terminator check on end lines of file


	// The User input file requested for processing cannot be located and is missing
	if (origFile == NULL)
	{
		// Error feedback for User
		printf("ERROR: Cannot open the file.\nPlease check the name entered\nOR if it is missing in required location.\n");
		// Exit Program	
		exit(-1);
	}

	// File found, start the encryption process
	else
	{
		// Create a new encrypted file for the data to be written to
		FILE* encryptResult = fopen((strcat(outChar, ".crp")), "w");

		// Get the line of data to be processed
		while (fgets(inputFileToProcess, ARRAYSIZE, origFile))
		{
			// Index reset here for start of process of lines
			i = 0;

			// Process until the null terminator is encountered
			while (inputFileToProcess[i] != '\0')
			{
				// take the ASCII value and assign it to array for processing
				convertArrayInt[i] = inputFileToProcess[i];

				// Everything ok, start the initial match checks
				if (ifProcessGo == 1)
				{
					// newline or carriage return encountered in line (should handle the OS particulars)
					if (convertArrayInt[i] == '\n' || convertArrayInt[i] == '\r')
					{
						// ignore conversion and just write to the buffer (keep as is)
						fprintf(encryptResult, "%c", inputFileToProcess[i]);
						// step to next index point
						i++;
						// back to the while start
						continue;
					}

					// tab encountered on the line
					else if (inputFileToProcess[i] == '\t')
					{
						// ignore conversion and do special Seanbonne assignment write 'TT' (TT Racer! Heh)
						fprintf(encryptResult, "%c%c", 'T', 'T');
						// step to next index point
						i++;
						// back to the while start
						continue;
					}

					// All done! Time for the heavy lifting of performing the conversion to Hex and write out data to the file 
					else
					{
						// file print (note: all uppercase letters for hex as per requirements)
						fprintf(encryptResult, "%X", (calcMathCharToHex(convertArrayInt[i])));
					}
				}
				i++;
			}
		}

		// Original Decrypted file finished working with: flush the buffer and close usage safely
		fflush(origFile);
		fclose(origFile);

		// Encrypted file finished working with: flush the buffer and close usage safely
		fflush(encryptResult);
		fclose(encryptResult);
	}

	// Encryption task completed
	return 0;
}


/*
Name	:	int calcMathCharToHex(int input)
Purpose :	Handles the conversion of the input ASCII value to a hex value.
Inputs	:	int input : the char value to be converted
Returns	:	int outHex: calculated result of char ASCII to hex conversion
*/
int calcMathCharToHex(int input)
{
	// Subract 16 off all ASCII values to prep
	int outHex = input - 16;

	// If the ASCII value is lower than 32 (anything lower than Space value)
	if (outHex < 32)
	{
		// Make the adjustments for hex equivalent
		outHex = (outHex - 32) + 144;
		// return the new processed value!
		return outHex;
	}

	// ASCII value higher than 32, return the new processed value
	return outHex;
}

