//	FILE			: cryptoMagicDecrypt.c
//	PROJECT			: CryptoMagic
//	PROGRAMMER		: KEVIN DOWNER
//	FIRST VERSION		: 2021-02-06
//	DESCRIPTION		: Holds the functions to take the input file, processes it into a decrypted version and output the new file.
//
//				Options:
//
//				ex. -decrypt <filename>
//				If Decrypt is chosen, it reads the input file and processes the result as a decrypted file export,
//				appending the extension as 'txt' on the end of the file, to indicate it is decrypted.
//
//				Error checks:
//				- If a filename input is missing the file in the directory.


// To gain access to the shared items between the program .c files
#include "../inc/cryptoMagicHeaders.h"


/*
Name	:	int decryptProcessMain(char* outChar)
Purpose :	The overall function that handles the decrypting of an input file,
			The decrypted file is exported with a .txt extension.
Inputs	:	char* outChar : The input file to be processed
Outputs	:	FILE* decryptResult : The decrypted, processed file is output
Returns	:	int: completion status
*/
int decryptProcessMain(char* outChar)
{
	int i = 0; // The index counter:  used for keeping track of array positioning
	int hexFaceValue = 0; // For 
	int hexPairResult = 0;

	// Position in code for pre-processing important for below lines
	FILE* origFile = fopen(outChar, "r");
	stripExtension(outChar);

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

	// File found, start the decryption process
	else
	{
		// Create a new decrypted file for the data to be written to
		FILE* decryptResult = fopen((strcat(outChar, ".txt")), "w");

		// Get the line of data to be processed
		while (fgets(inputFileToProcess, ARRAYSIZE, origFile))
		{
			// Index reset here for start of process of lines
			i = 0;

			// Process until the null terminator is encountered
			while (inputFileToProcess[i] != '\0')
			{
				// newline or carriage return encountered in line (should handle the OS particulars)
				if (inputFileToProcess[i] == '\n' || inputFileToProcess[i] == '\r')
				{
					// ignore conversion and just write to the buffer (keep as is)
					fprintf(decryptResult, "%c", inputFileToProcess[i]);
					// step to next index point
					i++;
					// back to the while start
					continue;
				}

				// Special Seanbonne 'TT' encountered on the line
				else if (inputFileToProcess[i] == 'T' && inputFileToProcess[i++] == 'T')
				{
					// Reaplce custom with tab and write to the buffer
					fprintf(decryptResult, "%c", '\t');
					// step to next index point
					i++;
					// back to the while start
					continue;
				}

				// Initial checks made, time to start the hex to char conversion
				else
				{
					// Check for the value in input file index encountered (also tracks the pairing of values requirements
					for (int hexCountPair = 1; hexCountPair <= 2; hexCountPair++)
					{
						// For converting the hex to 'face' values (note: should be uppercase letters but you never know...)
						switch (toupper(inputFileToProcess[i]))
						{
						// Hex values 1-9 range
						case '0':
							hexFaceValue = 0;
							break;
						case '1':
							hexFaceValue = 1;
							break;
						case '2':
							hexFaceValue = 2;
							break;
						case '3':
							hexFaceValue = 3;
							break;
						case '4':
							hexFaceValue = 4;
							break;
						case '5':
							hexFaceValue = 5;
							break;
						case '6':
							hexFaceValue = 6;
							break;
						case '7':
							hexFaceValue = 7;
							break;
						case '8':
							hexFaceValue = 8;
							break;
						case '9':
							hexFaceValue = 9;
							break;
						// hex values 11-15 range ('face' values)
						case 'A':
						case 'a':
							hexFaceValue = 10;
							break;
						case 'B':
						case 'b':
							hexFaceValue = 11;
							break;
						case 'C':
						case 'c':
							hexFaceValue = 12;
							break;
						case 'D':
						case 'd':
							hexFaceValue = 13;
							break;
						case 'E':
						case 'e':
							hexFaceValue = 14;
							break;
						case 'F':
						case 'f':
							hexFaceValue = 15;
							break;
						// Something rotten here.  Should never make it this far unless hex values messed up
						default:
							//  Error User never wants to see
							printf("Error in reading the Hex value.  Check the file.\n");
							break;
						}

						// Iteration match for first part of numbers pair to make the hex value
						if (hexCountPair == 1)
						{
							// Multiply value by 16 and assign to pair hold result
							hexPairResult = hexFaceValue * 16;
						}

						// Iteration match for second part of numbers pair to make the hex value
						if (hexCountPair == 2)
						{
							// Add hex face value to pair hold result to complete hex value
							hexPairResult += hexFaceValue;
						}

						// step to next index point
						i++;
					}
				}

				// All done! Time for the heavy lifting of performing the conversion to Char and write out data to the file
				fprintf(decryptResult, "%c", calcMathHexToChar(hexPairResult));
			}
		}

		// Original Encrypted file finished working with: flush the buffer and close usage safely
		fflush(origFile);
		fclose(origFile);

		// Decrypted file finished working with: flush the buffer and close usage safely
		fflush(decryptResult);
		fclose(decryptResult);
	}

	// Decryption task completed
	return 0;
}


/*
Name	:	int calcMathHexToChar(int input)
Purpose :	Handles the conversion of the input hex value to a char value.
Inputs	:	int input : the hex value to be converted
Returns	:	int outChar: calculated result of hex to char ASCII conversion
*/
int calcMathHexToChar(int input)
{
	// Add 16 to all ASCII values to prep
	int outChar = input + 16;

	// If the ASCII value is greater than 127 (outside the common ASCII table values)
	if (outChar > 127)
	{
		// Make the adjustments for char equivalent
		outChar = (outChar - 144) + 32;
		// return the new processed value!
		return outChar;
	}

	// ASCII value less than 127, return the new processed value
	return outChar;
}