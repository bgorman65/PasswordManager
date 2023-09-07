// This file will be intended to be a library for the encryption carried out in this project
// All the encryption function will be held in this file for security purposes

// Importing needed libraries
#include <string.h>

// Function to decrypt pin
void decryptPin(int *pin){
    for(int i = 0; i < (sizeof(pin)/sizeof(pin[0])); i++){
        pin[i] = pin[i] - 20;
    }
}

// Function to encrypt pin
void encryptPin(int *pin){
    for(int i = 0; i < (sizeof(pin)/sizeof(pin[0])); i++){
        pin[i] = pin[i] + 20;
    }
}

// Function to encrypt service
void encryptService(int *service){
    for(int i = 0; i < (sizeof(service)/sizeof(service[0])); i++){
        service[i] = service[i] + 30;
    }
}

// Function to decrypt service
void decryptService(int *service){
    for(int i = 0; i < (sizeof(service)/sizeof(service[0])); i++){
        service[i] = service[i] - 30;
    }
}

// Function to certify login
int loginPass(int *decryptedPin,int *encryptedPin){
    return strcmp(decryptedPin,encryptedPin);
}