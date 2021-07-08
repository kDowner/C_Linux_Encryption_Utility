//	FILE			: cryptoMagicHeaders.h
//	PROJECT			: CryptoMagic
//	PROGRAMMER		: KEVIN DOWNER
//	FIRST VERSION	: 2021-02-06
//	DESCRIPTION		: Holds the pre-processors, prototype functions, defines, includes
//					and input char array template for the input file.


// Preprocessor directives
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

// Defines
#define ARRAYSIZE 512

// The Input File to Process
char inputFileToProcess[ARRAYSIZE];

// Main
void encrypt(char* argv); // Sends the argument (input filename) to the main encrypt function to convert input file
void decrypt(char* argv); // Sends the argument (input filename) to the main decrypt function to convert input file
void stripExtension(char* fname); // Strips the extension off the input file (if any)

// Encrypt
int encryptProcessMain(char* outChar); // Main encrypt function to convert input file
int calcMathCharToHex(int input); // Calculates the conversion from Char ASCII to Char Hex for the encrypt process.

// Decrypt
int decryptProcessMain(char* outChar); // Main decrypt function to convert input file
int calcMathHexToChar(int input); // Calculates the conversion from Hex to Char ASCII for the decrypt process.