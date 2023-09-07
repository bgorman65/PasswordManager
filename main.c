// Importing libraries and header
#include <stdio.h>
#include "encryption.h"

// Defining file source
#define KEY_SOURCE "C:\\Users\\barry\\CLionProjects\\PasswordManager\\key.txt"
#define FILE_SOURCE "C:\\Users\\barry\\CLionProjects\\PasswordManager\\service.txt"

// Function to check if file exists
int checkFile(const char *fileName){
    // Opening File
    FILE *input = fopen(fileName, "r");
    // Checking for existence then returining value
    if(input == NULL){
        return 0;
    }else{
        fclose(input);
        return 1;
    }
}

// Function to create service file
void createService(const char *fileName){
    // Opening file
    FILE *input = fopen(fileName, "a+");
    // Making sure there is no error opening the file
    if(input == NULL){
        printf("\nError");
    }
    fclose(input);
}

// Function to create keyfile
void createKey(const char *keyFile, const char *fileName){
    char *pin;
    // Opening file
    FILE *input = fopen(keyFile, "a");
    // Making service file
    createService(fileName);
    if(input == NULL){
        printf("\nError");
    }
    // Creating Pin and encrypting it at beginning of file
    printf("Create a Pin For The File:");
    scanf("%s", pin);
    encryptPin(pin);
    fputs(pin, input);
    fclose(input);
}

// Gathering pin from file
void getPin(const char *fileName, char *pin){
    // Opening file and gathering pin
    FILE *input = fopen(fileName, "r");
    fscanf(input, "%[^,],", pin);
    fclose(input);
}

// Function to add service
void addService(char *service, int *username, int *password, char *fileName){
    // Opening file
    FILE *input = fopen(fileName, "a");
    if(input == NULL){
        printf("\nError");
    }
    // Writing encrypted data to the file
    fprintf(input, "%s,%s,%s ", service, username, password);
    fclose(input);
}

// Function to view services
void viewServices(char *fileName){
    // Initializing needed memory to gather services
    char service[100] = {0}, username[100] = {0}, password[100] = {0};
    // Opening file
    FILE *input = fopen(fileName, "r");
    // Loop to find and gather all services in file
    while(fscanf(input, "%[^,],%[^,],%[^ ] ", service, username, password) == 3){
        // Decrypting services
        decryptService(service);
        decryptService(username);
        decryptService(password);
        printf("Service:%s Username:%s Password:%s\n", service, username, password);
    }
    fclose(input);
}

// Main function
int main() {
    printf("*****Password Manager*****\n");
    printf("*****Checking For File*****\n");
    // Checking if file exists and creating one if needed
    if(checkFile(KEY_SOURCE)){
        printf("*********File Found*********\n");
    }else{
        printf("***File Not Found***\n");
        // Creating key file and service file
        createKey(KEY_SOURCE, FILE_SOURCE);
    }
    // Gathering encrypted pin and user entered pin
    char *givenPin, *accessPin;
    printf("\nEnter Pin For Access:");
    scanf("%s", &givenPin);
    // Getting pin from the key file
    getPin(KEY_SOURCE, &accessPin);
    // Decrypting the pin
    decryptPin(&accessPin);
    // Checking if login is granted
    if(loginPass(&givenPin, &accessPin)){
        printf("\nAccess Denied");
        return 0;
    }
    // Do/Switch case to handle option once access is granted
    int action;
    char *service, *username ,*password;
    do{
       printf("\n*****Password Manager*****");
       printf("\n1: Add a Service");
       printf("\n2: View all services");
       printf("\n3: Exit Program");
       printf("\nEnter Your Action:");
       scanf("%d", &action);
        switch (action) {
            case 1:
                // Gathering Service, Username and Password
                printf("\n***Add A Service***");
                printf("\nEnter The Service:");
                scanf("%s", &service);
                printf("Enter The User Name:");
                scanf("%s", &username);
                printf("Enter The Password:");
                scanf("%s", &password);
                // Encrypting this gathered data
                encryptService(&service);
                encryptService(&username);
                encryptService(&password);
                // Adding this service
                addService(&service, &username, &password, FILE_SOURCE);
                printf("***Service Added***\n");
                break;
            case 2:
                printf("\n***Services Saved***\n");
                // Calling the view services function to print out the decrypted data
                viewServices(FILE_SOURCE);
                break;
        }
    }while(action !=3);
    return 0;
}