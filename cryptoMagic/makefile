# FILE:		makefile
# PROJECT:		CryptoMagic
# PROGRAMMER:		KEVIN DOWNER
# FIRST VERSION:	2021-02-06
# DESCRIPTION:
# This makefile will compile the cryptoMagic application,
# allowing a User to encrypt and decrypt files.
# Source files found in the "cryptoMagic" directory to make are:
# src/ cryptoMagicDecrypt.c cryptoMagicEncrypt.c cryptoMagicMain.c
# inc/ cryptoMagicHeaders.h
#  
# 
# =======================================================
#                  Compile Target for cryptoMagic
# =======================================================
# FINAL BINARY Target
./bin/cryptoMagic : ./obj/cryptoMagicMain.o ./obj/cryptoMagicEncrypt.o ./obj/cryptoMagicDecrypt.o
	cc ./obj/cryptoMagicMain.o ./obj/cryptoMagicEncrypt.o ./obj/cryptoMagicDecrypt.o -o ./bin/cryptoMagic
#
# =======================================================
#                     Dependencies for cryptoMagic
# =======================================================                     
./obj/cryptoMagicMain.o : ./src/cryptoMagicMain.c ./inc/cryptoMagicHeaders.h
	cc -c ./src/cryptoMagicMain.c -o ./obj/cryptoMagicMain.o

./obj/cryptoMagicEncrypt.o : ./src/cryptoMagicEncrypt.c ./inc/cryptoMagicHeaders.h
	cc -c ./src/cryptoMagicEncrypt.c -o ./obj/cryptoMagicEncrypt.o
	
./obj/cryptoMagicDecrypt.o : ./src/cryptoMagicDecrypt.c ./inc/cryptoMagicHeaders.h
	cc -c ./src/cryptoMagicDecrypt.c -o ./obj/cryptoMagicDecrypt.o

#
# =======================================================
# Other targets for cryptoMagic
# =======================================================                     
all : ./bin/cryptoMagic

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


