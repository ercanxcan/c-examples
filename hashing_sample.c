/**
@file

Set the selected users from the e-mail address from which the e-mail service provider's application
It will be designed to evaluate a system that allows the hashing method

@author

Name:               Ercan Can
Date:               08/12/2015
E-Mail:             ercanxcan@gmail.com
Compiler used:      GCC
IDE:                Clion
Operating System:   Ubuntu 14.04
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

// The object will be stored in hash array
typedef struct {
    char email[200];
    int hashFlag;
} HASHOBJECT;

HASHOBJECT *hashTable = NULL;  //Definition hash array

int hasTableSize = 0;          //The size of the hash array
int hashTableRecentSize = 0;   //The number of records in the hash array
/**
 Given the string allows the conversion of small characters.
 @param email char[]
 */
void stringToLower(char *email) {
    int c = 0;

    while (email[c] != '\0') {
        if (email[c] >= 'A' && email[c] <= 'Z') {
            email[c] = email[c] + 32;
        }
        c++;
    }
}

/**
It generates hash index for the given email.
 @param email char[]
 @return integer value of the index
 */
int getHashIndex(char *email) {
    int i;
    int index = 0;
    for (i = 0; i < strlen(email); i++) {
        if(email[i] != '@') {  // @ character not use, cause by negative
            index += (email[i] - 'a') * 26 * i;
        }
    }
    index = index % hasTableSize;

    return index;

}

/**
 To provide insert given record of email to hash table.
 @param email char[]
 */
void insertInHashTable(char *email) {
    int hashIndex = getHashIndex(email);

    printf("The generated first hash value index : %d \n", hashIndex);

    if (hasTableSize == hashTableRecentSize) {
        printf("The hash table is full !!! \n");
        return;
    }

    //İf email inserted before show message
    if (strcmp(email,hashTable[hashIndex].email) == 0){
        printf("Please enter a different email address %s !!! \n", email);
        return;
    }
    //İf used hash key before, create new hash key
    while (hashTable[hashIndex].hashFlag == 1) {
        int tmpIndex = hashIndex;
        hashIndex = (hashIndex + 1) % hasTableSize;

        printf("\t In %d index, find %s email address.\n", tmpIndex, hashTable[tmpIndex].email);

        printf("\t New hash index %d \n", hashIndex);
    }

    strcpy(hashTable[hashIndex].email, email);
    hashTable[hashIndex].hashFlag = 1;

    // Show occupancy of hash array
    hashTableRecentSize++;

    printf("%s e-mail address has been added to the hash array. \n", email);
    printf("%d available for enter new email in hash array. \n\n", hasTableSize - hashTableRecentSize);
    return;
}

/**
 * Display items in hash array
 */
void displayHashTable() {
    int i;
    if (hashTableRecentSize == 0) {
        printf("Record not found in hash array!!\n");
        return;
    }
    printf("HashIndex \tEmail \n");
    printf("--------------------------------------\n");
    for (i = 0; i < hasTableSize; i++) {
        if (hashTable[i].hashFlag == 1) {
            printf("%d\t\t\t", i);
            printf("%s \n", hashTable[i].email);
        }
    }
    printf("\n");
    return;
}

/**
 * Main function
 */
int main() {

    int ch;          //Screen menu selection character
    char email[200]; //Email to be entered

    printf("Enter hash array dimension:");
    scanf("%d", &hasTableSize);

    //dynamicly open place with calloc function
    hashTable = (HASHOBJECT *) calloc(hasTableSize, sizeof(HASHOBJECT));

    while (TRUE) {
        printf("\n");
        printf("1. New Recod\n2. Show Series\n3. Exit \n\n");
        printf("Seçiminizi giriniz:");
        scanf("%d", &ch);
        printf("\n");

        switch (ch) {
            case 1:
                getchar();
                printf("Enter your email address");
                fgets(email, 200, stdin);

                //Email characters converted to lowercase characters.
                stringToLower(email);

                // String to the end of the input string termination character is introduced.
                email[strlen(email) - 1] = '\0';
                insertInHashTable(email);
                break;

            case 2:
                displayHashTable();
                break;

            case 3:
                exit(0);

            default:
                printf("You entered an incorrect choice !!!\n");
                break;

        }
    }
    return 0;
}


/*
Email address to be entered for the test
 
faraday@hotmail.com
pascal@hotmail.com
einstein@gmail.com
tesla@gmail.com
newton@gmail.com
galileo@yahoo.com
maxwell@gmail.com
 */